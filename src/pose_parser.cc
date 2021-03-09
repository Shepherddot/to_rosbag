//
// Created by liu on 2021/3/9.
//

#include "../include/to_rosbag/pose_parser.h"

#include "../include/to_rosbag/time_parser.h"
#include "../include/to_rosbag/common.h"

#include "../thirdparty/fast-cpp-csv-parser/csv.h"

PoseParser::PoseParser(std::string dataset_path_) {
  std::string pose_path = dataset_path_ + "/rtk.csv";

  io::CSVReader<7> in(dataset_path_);
  in.read_header(io::ignore_extra_column, "timestamp", "northing", "easting", "down", "roll", "pitch", "yaw");
  uint64_t timestamp;
  float north;
  float east;
  float down;
  float roll;
  float pitch;
  float yaw;

  std::vector<uint64_t> raw_time;
  while (in.read_row(timestamp, north, east, down, roll, pitch, yaw)) {
    raw_time.push_back(timestamp);

    cv::Point3f euler;
    euler.x = roll;
    euler.y = pitch;
    euler.z = yaw;

    cv::Mat r;
    Common::rpyToRotMat(euler, r);

    cv::Mat t = (cv::Mat_<float>(3, 1) << north, east, down);

    cv::Mat transform = cv::Mat::eye(4, 4, CV_32FC1);
    r.copyTo(transform.rowRange(0, 3).colRange(0, 3));
    t.copyTo(transform.col(3).rowRange(0, 3));

    pose_list_.push_back(transform);
  }

  std::shared_ptr<TimeParser> tp_ptr = std::make_shared<TimeParser>(raw_time);
  time_list_ = tp_ptr->getTimeList();
}

std::vector<ros::Time> PoseParser::getTimeList() {
  return time_list_;
}

std::vector<cv::Mat> PoseParser::getPoseList() {
  return pose_list_;
}

