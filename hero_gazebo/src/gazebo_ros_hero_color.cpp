/*
 *   GNU GENERAL PUBLIC LICENSE
 *                      Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
 *
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

/*
 @mainpage
   Desc: GazeboRosModelColor plugin for change the color of models in Gazebo
   Author: Paulo Rezeck
   Date: 14 Sept 2018
*/
#include <hero_gazebo/gazebo_ros_hero_color.h>

namespace gazebo
{
    // Register this plugin with the simulator
    GZ_REGISTER_VISUAL_PLUGIN(ModelVisualPlugin)

    ModelVisualPlugin::ModelVisualPlugin() {}

    ModelVisualPlugin::~ModelVisualPlugin()
    {
        this->rosnode_->shutdown();
        this->callback_queue_thread_.join();
        delete this->rosnode_;
    }

    void ModelVisualPlugin::Load(rendering::VisualPtr _visual, sdf::ElementPtr _sdf)
    {
        if (!_visual || !_sdf)
        {
            gzerr << "[Model Color] No visual or SDF element specified. Plugin won't load." << std::endl;
            return;
        }

        this->model_ = _visual;
        this->sdf_ = _sdf;

        this->robot_namespace_ = "";
        if (this->sdf_->HasElement("robotNamespace"))
        {
            this->robot_namespace_ = this->sdf_->Get<std::string>("robotNamespace") + "/";
        }

        this->service_name_ = "/model_color";
        if (this->sdf_->HasElement("serviceName"))
        {
            this->service_name_ = this->sdf_->Get<std::string>("serviceName");
        }

        this->topic_name_ = "/model_color";
        if (this->sdf_->HasElement("topicName"))
        {
            this->topic_name_ = this->sdf_->Get<std::string>("topicName");
        }

        if (this->sdf_->HasElement("color"))
        {
            ignition::math::Color default_color = this->sdf_->Get<ignition::math::Color>("color");
            this->model_->SetAmbient(default_color);
            this->model_->SetDiffuse(default_color);
        }

        // Initialize the ROS node for the gazebo client if necessary
        if (!ros::isInitialized())
        {
            int argc = 0;
            char **argv = NULL;
            ros::init(argc, argv, "gazebo_client", ros::init_options::NoSigintHandler);
        }

        std::string gazebo_source = (ros::this_node::getName() == "/gazebo_client") ? "gzclient" : "gzserver";
        //ROS_INFO(gazebo_source.c_str());

        this->rosnode_ = new ros::NodeHandle(this->robot_namespace_);

        // advertise services on the custom queue
        ros::AdvertiseServiceOptions aso = ros::AdvertiseServiceOptions::create<gazebo_msgs::SetLightProperties>(
            this->service_name_, boost::bind(&ModelVisualPlugin::ServiceCallback, this, _1, _2), ros::VoidPtr(), &this->model_queue_);

        this->srv_ = rosnode_->advertiseService(aso);

        ros::SubscribeOptions so = ros::SubscribeOptions::create<std_msgs::ColorRGBA>(this->topic_name_, 10, boost::bind(&ModelVisualPlugin::TopicCallback, this, _1), ros::VoidPtr(), &this->model_queue_);
        this->sub_ = rosnode_->subscribe(so);

        this->callback_queue_thread_ = boost::thread(boost::bind(&ModelVisualPlugin::VisualQueueThread, this));

        //ROS_INFO("\x1b[6;37;42mHello Simulated Colored World!\x1b[0m");
    }

    // Callback when using service
    bool ModelVisualPlugin::ServiceCallback(gazebo_msgs::SetLightProperties::Request &req, gazebo_msgs::SetLightProperties::Response &res)
    {
        ignition::math::Color c(req.diffuse.r, req.diffuse.g, req.diffuse.b, req.diffuse.a);
        this->model_->SetAmbient(c);
        this->model_->SetDiffuse(c);
        res.success = true;
        res.status_message = "Changing the color of the model";
        return true;
    }

    void ModelVisualPlugin::TopicCallback(const std_msgs::ColorRGBAConstPtr &msg)
    {
        ignition::math::Color c(msg->r, msg->g, msg->b, msg->a);
        this->model_->SetAmbient(c);
        this->model_->SetDiffuse(c);
    }

    void ModelVisualPlugin::VisualQueueThread()
    {
        static const double timeout = 0.01;
        while (this->rosnode_->ok())
        {
            model_queue_.callAvailable(ros::WallDuration(timeout));
        }
    }
}