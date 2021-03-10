//
// Created by liu on 2021/3/9.
//

#ifndef TO_ROSBAG_INCLUDE_TO_ROSBAG_TIME_PARSER_H_
#define TO_ROSBAG_INCLUDE_TO_ROSBAG_TIME_PARSER_H_

#include <string>
#include <vector>

#include <ros/time.h>

class TimeParser{
 public:
  TimeParser();

  void timestampToRos(std::string timestamp, ros::Time* time);
};

#endif //TO_ROSBAG_INCLUDE_TO_ROSBAG_TIME_PARSER_H_
