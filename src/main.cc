//
// Created by liu on 2021/3/9.
//

#include <memory>

#include "../include/to_rosbag/to_rosbag.h"

int main(){
  std::string bag_path = "/media/liu/Elements/robocar/rosbag_data/2014-11-18-13-20-12.bag";
  std::string data_path = "/media/liu/Elements/robocar/2014-11-18-13-20-12";
  std::shared_ptr<ToRosBag> bag_converter = std::make_shared<ToRosBag>(bag_path, data_path);
  return 0;
}

