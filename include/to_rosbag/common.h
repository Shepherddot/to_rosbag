//
// Created by liu on 2021/3/9.
//

#ifndef TO_ROSBAG_INCLUDE_TO_ROSBAG_COMMON_H_
#define TO_ROSBAG_INCLUDE_TO_ROSBAG_COMMON_H_

#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>

void imageToRos(const cv::Mat &image, sensor_msgs::Image *image_msg) {
  cv_bridge::CvImage image_cv_bridge;
  image_cv_bridge.image = image;

  if (image.type() == CV_8U) {
    image_cv_bridge.encoding = "mono8";
  } else if (image.type() == CV_8UC3) {
    image_cv_bridge.encoding = "bgr8";
  }

  image_cv_bridge.toImageMsg(*image_msg);
}

void timestampToRos(uint64_t timestamp_ns, ros::Time *time) {
  time->fromNSec(timestamp_ns);
}

void rpyToRotMat(cv::Point3f euler, cv::Mat &rot) {
  float r = euler.x / 180.0 * M_PI;
  float p = euler.y / 180.0 * M_PI;
  float y = euler.z / 180.0 * M_PI;

  cv::Mat Rz = (cv::Mat_<float>(3, 3) << cos(y), -sin(y), 0, sin(y), cos(y), 0, 0, 0, 1);
  cv::Mat Ry = (cv::Mat_<float>(3, 3) << cos(p), 0., sin(p), 0., 1., 0., -sin(p), 0., cos(p));
  cv::Mat Rx = (cv::Mat_<float>(3, 3) << 1., 0., 0., 0., cos(r), -sin(r), 0., sin(r), cos(r));

  rot = Rz * Ry * Rx;
}

#endif //TO_ROSBAG_INCLUDE_TO_ROSBAG_COMMON_H_
