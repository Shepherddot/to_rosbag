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

### Extrinsics
Put the origin at the ins coordinate system
```
%YAML:1.0
---
omni_left: !!opencv-matrix
   rows: 4
   cols: 4
   dt: d
   data: [ 9.2945501676624998e-01, 1.9452515037356446e-01,
       3.1348578545157674e-01, 2.1085993016645854e-01,
       2.7843788495427330e-01, 1.8760385143958944e-01,
       -9.4195389438508259e-01, -7.0636219458906890e-01,
       -2.4204486367250336e-01, 9.6279009176308761e-01,
       1.2020616944476942e-01, -9.8949731754567094e-01, 0., 0., 0., 1. ]
omni_rear: !!opencv-matrix
   rows: 4
   cols: 4
   dt: d
   data: [ 8.4814575680816247e-03, 2.0820633986006221e-01,
       -9.7804815061406736e-01, -3.3129531961149783e-01,
       -9.9958983262991008e-01, -2.4989980219217046e-02,
       -1.3988116083001935e-02, -4.2831162730437855e-02,
       -2.7353818388466854e-02, 9.7776562678932399e-01,
       2.0790898895634932e-01, -1.0558195328341429e+00, 0., 0., 0., 1. ]
omni_right: !!opencv-matrix
   rows: 4
   cols: 4
   dt: d
   data: [ -9.3490338727129918e-01, 2.0522322594948311e-01,
       2.8954979537125974e-01, 1.9612638155572229e-01,
       2.4897892027506693e-01, -2.0214209051558060e-01,
       9.4717900763300955e-01, 6.1619184168129382e-01,
       2.5291333244278125e-01, 9.5761265800577144e-01,
       1.3788706792084948e-01, -9.7496152458817620e-01, 0., 0., 0., 1. ]
stereo_left: !!opencv-matrix
   rows: 4
   cols: 4
   dt: d
   data: [ 4.9959797166620242e-03, -3.9989334186634161e-02,
       9.9918761668566547e-01, 1.7589974561875348e+00,
       9.9990687776194997e-01, -1.2489676075351923e-02,
       -5.4994359603220272e-03, -1.1258797097607950e-01,
       1.2699448453362175e-02, 9.9912204516907865e-01,
       3.9923212121996419e-02, -1.1268543774229534e+00, 0., 0., 0., 1. ]
```
![](extrinsic_visualize.gif)
