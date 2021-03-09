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
  TimeParser(std::vector<uint64_t> time_list);

  std::vector<ros::Time> getTimeList();

 private:
  std::vector<ros::Time> time_list_;
};

#endif //TO_ROSBAG_INCLUDE_TO_ROSBAG_TIME_PARSER_H_
