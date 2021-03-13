//
// Created by liu on 2021/3/9.
//

#include <memory>

#include "../include/to_rosbag/to_rosbag.h"

int main(int argc, char **argv) {
  if (argc != 3){
    std::cout << "-- Usage: to_rosbag_node bag_path dataset_path" << std::endl;
    exit(0);
  }

  std::string bag_path(argv[1]);
  std::string data_path(argv[2]);

  std::shared_ptr<ToRosBag> bag_converter = std::make_shared<ToRosBag>(bag_path, data_path);
  return 0;
}

