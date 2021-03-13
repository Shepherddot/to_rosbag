### oxford robotcar dataset to ros1 bag

this is a simple package to convert oxford robotcar dataset to ros1 bag.

### now support
- [x] three channel omni image
- [x] left and right stereo image
- [x] rtk pose

### dir tree example
```
2014-11-18-13-20-12
├── mono_left
├── mono_left.timestamps
├── mono_rear
├── mono_rear.timestamps
├── mono_right
├── mono_right.timestamps
├── rtk.csv
├── stereo
│   ├── left
│   └── right
└── stereo.timestamps

```

### Usage
```
to_rosbag_node /home/2014-11-18-13-20-12.bag /home/test_data/2014-11-18-13-20-12
```