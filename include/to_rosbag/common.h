//
// Created by liu on 2021/3/9.
//

#ifndef TO_ROSBAG_INCLUDE_TO_ROSBAG_COMMON_H_
#define TO_ROSBAG_INCLUDE_TO_ROSBAG_COMMON_H_

#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>

class Common {
 public:
  static void imageToRos(const cv::Mat &image, sensor_msgs::Image *image_msg);
  static void rpyToRotMat(cv::Point3f euler, cv::Mat &rot);
};

#endif //TO_ROSBAG_INCLUDE_TO_ROSBAG_COMMON_H_
