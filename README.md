# 3D-mapping-Robot-using-ROS
# Generation of Indoor 3D mapping using ROS

## --Project by R.Ashiwin--
#### SASTRA Deemed University
#### May 2018-Aug 2018

## Introduction

Let’s say that a building was attacked by terrorist and the police officers or officials wants to execute an operation to catch the terrorist. For that they should know the map of the building to execute the operation of recuing people so this project aims in developing a robot which helps in generation of 3D map of the building and also delivers the trajectory path of the robot.

## Installation of Ubuntu and ROS

* To get into the project of making an mapping  robot using Raspberry Pi and ROS (Robot Operating System ),first we should make sure that ROS is          installed in our Computer.

* ROS is only compatible with Ubuntu operating system and hence Ubuntu OS should be installed in Computer. It will be convenient if we use laptop.

* Try to dual boot the system if we want to maintain two operating systems. Having virtual machine for Ubuntu may cause network errors and so dual     boot is better

* I had used Ubuntu 16.04 

* Installation of ROS : ROS Kinetic is compatible with Ubuntu 16.04 and hence I used ROS   Kinetic
   We can install ROS using the instructions given in the link : http://wiki.ros.org/kinetic/Installation/Ubuntu

* Followed by this link : http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment
   ( This link will guide us through the making the catkin package )


## Configuring with Raspberry Pi 3


Now our next step is Interfacing with Raspberry Pi .The need of Raspberry Pi here acts as the mini CPU or mini computer.Instead of giving commands from laptop to laptop. Here we use Raspberry Pi (Master) and our laptop (slave ).We introduce the concept of networking here. Thereby we will give commands from our laptop to operate the Raspberry Pi. We use Raspberry Pi 3 here.

**For configuration of Raspberry Pi 3,**

We need,
* Monitor screen 
* HDMI cable
* Keyboard
* Mouse
* SD card minimum 16 GB or 32 GB

**For configuring Raspberry Pi 3 with Ubuntu mate 16.04 with ROS preinstalled (ISO Image from Ubiquity robots ):**

* Use this link to download the pre-installed Ubuntu 16.04.2 mate with ros , (https://downloads.ubiquityrobotics.com/pi.html)

* Extract the image and write the image to the SD card using "Etcher" : Download link -(https://etcher.io/)

* For Detailed installation refer  (https://www.youtube.com/watch?v=ghImsclr2sU)

* In order to make the pi permanently connected to your  hotspot when it is just powered, use the following tutorial :     (https://www.youtube.com/watch?v=GyP-qY4_K-A)


## Enabling the Network Communication

Follow the steps given below to ensure that SSH is installed in both master and slave.

**Establishing SSH between two ROS systems:**

**Install SSH in Master and Workstation ( slave ):**

*  Check for SSH service in master and workstation :
```
sudo service ssh status
```

*  If SSH service is not found use the following command: 
```
sudo apt-get install openssh-server 
```

* Now that ssh is installed, configure and start ssh using the following commands: 
```
sudo iptables -A INPUT -p tcp –dport ssh -j ACCEPT 
sudo ufw allow ssh 
sudo /etc/init.d/ssh restart 
```

* Find the master’s ip address using the command by using the following command after  wlan0 under inet adddr:. 
```
ifconfig 
```

* On the workstation, open the terminal and start the master. 
```
ssh <name_of_host>@<ip_of_host> 
```

* If there is IO permission error in the host for ROS use the following command to resolve it. 
```
sudo rosdep fix-permissions
```

## Interfacing Arduino with Raspberry Pi 3

We are going to control our robot automation using Arduino and hence the next steps will guide us through the installation of Arduino in the SD card of Raspberry Pi 3.

In this section we are going to give a communication interface between ROS and Arduino :

* Use this link to install Arduino in the Ubuntu OS  https://www.arduino.cc/en/Guide/Linux

    We should use the “ARM linux arduino” zip file ( only that works),since we use Raspberry Pi 3 here. Download the corresponding file from the     Arduino downloads section.

* In order to install the ros serial , the below two commands are used in terminal.
```
sudo apt-get install ros-kinetic-rosserial-arduino
sudo apt-get install ros-kinetic-rosserial
```

* Then we have to install arduino libraries, follow the below command in terminal.
```
cd ~/Arduino/libraries/
rosrun rosserial_arduino make_libraries.py . 
```

* We have to add our user to the OS , so type the below command in terminal and then logout and log in again.
```
sudo adduser $USER dialout
```

* Open arduino -> Sketch -> Include library ->  manage libraries
   Type “rosserial ” in search link and then install the latest version of “Rosserial Arduino Library”

   At the same time follow this link for the catkin package after the installation of Arduino (http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup)

## Making the Robot automate through commands

* Now we will dump our code into arduino to make it automate when we give commands in the terminal window ( the arduino code I had attached in    the code section or in the repository)

* Run “roscore” in one terminal window

* Now open another terminal and run the below command
```
rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0
```

* Followed by the below command in another terminal window
```
rostopic pub backward std_msgs/Empty –once
or
rostopic pub forward std_msgs/Empty –once
or
rostopic pub left std_msgs/Empty –once
or
rostopic pub right std_msgs/Empty –once
or
rostopic pub stop std_msgs/Empty –once
```

Thus from the above steps we found a way to interface between Raspberry Pi 3 ,arduino and laptop. And succeded in automating the robot by giving commands.

## Introduction to Kinect

Kinect is a line of motion sensing input devices that was produced by Microsoft for Xbox 360 and Xbox One video game consoles and Microsoft Windows PCs. The Kinect camera has 3D depth sensor which senses the depth of the object. We use this camera to generate the 3D map of the environment.

*Installation of the dependency files*

**Install Freenect for kinect interfacing and testing**

```
sudo apt-get install libfreenect-dev
sudo apt-get install ros-kinetic-freenect-launch
roslaunch freenect_launch freenect.launch depth_registration:=true
```

**Install and testing RTABMAP_ROS**

```
sudo apt-get install ros-kinetic-rtabmap-ros
roslaunch rtabmap_ros rgbd_mapping.launch rgbd_odometry:=true
```

**Install and testing depthimage to laserscan**

```
sudo apt-get install ros-kinetic-depthimage-to-laserscan
rosrun depthimage_to_laserscan depthimage_to_laserscan image:=/camera/depth/image_raw
```

**Creating a 3D scan from the Kinect**

Connect Kinect camera to raspberry pi. Follow up the below commands in each terminal window to get the map of environment.
We can also identify path of the robot which is described using the green trajectory.

```
roscore
roslaunch freenect_launch freenect.launch depth_registration:=true
roslaunch rtabmap_ros rgbd_mapping.launch rgbd_odometry:=true
```

**To Reset Odometry**

If there is a loss in point clouds then one can reset the odometry using the below command.
```
rosservice_call_/rtabmap/reset_odom
```

## Drawbacks In this Project

* Since Kinect camera needs AC power supply , extension boxes are used to connect the Kinect camera. In order to avoid this, we can use AC to DC    convertor.

* There is some technical issue with respect to RTAB mapping  in Raspberry Pi , so  Kinect camera is connected to laptop.

* Since the simultaneous process of mapping and automation of the robot takes place , the processing speed is slow and hence faced a difficulty in giving     accurate control , leading to approximate mapping.

## A Robot is done to create the 3D map of the environment automated through commands in terminal.
## This video shows the [Final Robot](https://www.youtube.com/watch?v=TRdsF5pJyjE).















