# tf_dynreconf
This package implements a `dynamic_reconfigure` interface to reconfigure a transform between two frames. 

## Prerequisites
This codebase was developed and tested on Ubuntu 18.04 with ROS melodic.

## Running `tf_dynreconf`
```bash
$ rosrun tf_dynreconf node
```
__OR__
```bash
$ roslaunch tf_dynreconf node.launch
```

If you want to reconfigure the parameters, add the argument `reconfigure:=true` to the launch file, to launch `rqt_reconfigure`
```bash
$ roslaunch tf_dynreconf node.launch reconfigure:=true
```