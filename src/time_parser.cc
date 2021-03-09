//
// Created by liu on 2021/3/9.
//

#include "../include/to_rosbag/time_parser.h"

TimeParser::TimeParser(std::vector<uint64_t> time_list) {
  for (int i = 0; i < time_list.size(); i++) {
    ros::Time t;
    t.fromNSec(time_list[i]);
    time_list_.push_back(t);
  }
}

std::vector<ros::Time> TimeParser::getTimeList() {
  return time_list_;
}