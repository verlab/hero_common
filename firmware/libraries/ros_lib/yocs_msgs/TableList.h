#ifndef _ROS_yocs_msgs_TableList_h
#define _ROS_yocs_msgs_TableList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "yocs_msgs/Table.h"

namespace yocs_msgs
{

  class TableList : public ros::Msg
  {
    public:
      uint8_t tables_length;
      yocs_msgs::Table st_tables;
      yocs_msgs::Table * tables;

    TableList():
      tables_length(0), tables(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = tables_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < tables_length; i++){
      offset += this->tables[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t tables_lengthT = *(inbuffer + offset++);
      if(tables_lengthT > tables_length)
        this->tables = (yocs_msgs::Table*)realloc(this->tables, tables_lengthT * sizeof(yocs_msgs::Table));
      offset += 3;
      tables_length = tables_lengthT;
      for( uint8_t i = 0; i < tables_length; i++){
      offset += this->st_tables.deserialize(inbuffer + offset);
        memcpy( &(this->tables[i]), &(this->st_tables), sizeof(yocs_msgs::Table));
      }
     return offset;
    }

    const char * getType(){ return "yocs_msgs/TableList"; };
    const char * getMD5(){ return "88fff7e2df98bd37f03f85cffc55624b"; };

  };

}
#endif