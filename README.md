# ROS trial project

## how to install

clone the repo

expecting ros melodic installed 

ros environment

```
source /opt/ros/melodic/setup.bash
```

remove build and or devel folders (if there is any)

requres teleop_twist_keyboard

also requires ros, gazebo, rviz, amcl ros lib


## launch

after successfull build 

``` 
source devel/setup.bash

roslaunch my_robot world.launch

roslaunch my_robot amcl.launch
```

## other
in rviz add "map", camera


## robot
created a simplistic robot with .xacro
sensors include lidar and camera

## world
simple house (actually similar  floorplan as my house in the countryside)

## localization
used amcl library to localize a robot
in maps folder "map.pgm" image of the house floor plan

## known issues

robot can be stucked to corners

robot can make funny routes to target locations