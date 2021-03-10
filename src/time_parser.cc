//
// Created by liu on 2021/3/9.
//

#include "../include/to_rosbag/time_parser.h"

#include <string>

TimeParser::TimeParser() {
}

void TimeParser::timestampToRos(std::string timestamp, ros::Time *time) {
  std::string secs = timestamp.substr(0, 10);
  std::string nsecs = timestamp.substr(10, 16);
  *time = ros::Time(stod(secs), stod(nsecs) * 1000);

  // time->fromNSec(timestamp_ns);
}