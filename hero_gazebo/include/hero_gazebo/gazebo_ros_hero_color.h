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

#ifndef GAZEBO_ROS_MODEL_COLOR_H
#define GAZEBO_ROS_MODEL_COLOR_H

// GAZEBO
#include <gazebo/common/Plugin.hh>
#include <gazebo/rendering/rendering.hh>
#include <ignition/math/Color.hh>
//#include <gazebo/common/Color.hh> // depreciated

// THREAD
#include <string>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

// ROS
#include <ros/ros.h>
#include <gazebo_msgs/SetLightProperties.h>
#include <ros/callback_queue.h>
#include <ros/advertise_options.h>
#include <std_msgs/ColorRGBA.h>

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

namespace gazebo {
    class ModelVisualPlugin : public VisualPlugin {
        // Constructor
        public: ModelVisualPlugin();

        // Destructor
        public: ~ModelVisualPlugin();

        // Load the controller
        public: void Load(rendering::VisualPtr _visual, sdf::ElementPtr _sdf);

        private: rendering::VisualPtr model_;
        private: sdf::ElementPtr sdf_;

        private: ros::CallbackQueue model_queue_;
        private: void VisualQueueThread();
        private: boost::thread callback_queue_thread_;

        // Pointer to ros node
        private: ros::NodeHandle* rosnode_;

        private: ros::ServiceServer srv_;
        private: std::string service_name_;
        private: std::string robot_namespace_;

        private: ros::Subscriber sub_;
        private: std::string topic_name_;

        // Callback when using service
        private:  bool ServiceCallback(gazebo_msgs::SetLightProperties::Request &req,
                                        gazebo_msgs::SetLightProperties::Response &res);
        // Callback when using topic
        private: void TopicCallback(const std_msgs::ColorRGBAConstPtr &msg);
    };
}
#endif