# ROS trial project

## how to install

clone the repo

[mapper](https://github.com/tervoju/urobo_mapper)


### Environment
Distributor ID:	Ubuntu
Description:	Ubuntu 18.04.4 LTS
Release:	18.04
Codename:	bionic

use ros environment melodic
```
source /opt/ros/melodic/setup.bash
```
remove build and or devel folders (if there is any)

requires ros, gazebo, rviz, rtab ros lib, teleop

[rtab](http://wiki.ros.org/rtabmap_ros)
[teleop](https://github.com/ros-teleop/teleop_twist_keyboard)

## Build and launch

```
catkin_make
```

after successfull build run in separate terminals

``` 
source devel/setup.bash

roslaunch my_robot world.launch

rosrun teleop_twist_keyboard teleop_twist_keyboard.py

roslaunch my_robot mapping.launch
```


## Robot
created a simplistic "my_robot" robot with .xacro
sensors include lidar and camera

## World
simple house (actually similar  floorplan as my house in the countryside)


## known issues

robot can easily be stucked to corners
camera orientation different what was recommended in the project intro
created map in /images folder as mapping.png
tested several times the mapping and was expecting "better" results
