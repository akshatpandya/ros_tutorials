# ros_tutorials
A repository containing ros tutorials in both roscpp and rospy. The problem statement for the tutorial is as follows:
- Create a node containing a publisher and a service server. The server has access to a file containing two columns (state names and populations). The service takes in a state name and a population count and edits the corresponding field in the file. The publisher just publishes the contents of the file on `/population`.
- Create a node containing a subscriber and a service client. The client sends a service request to the above server. The subscriber subscribes to `/population` and prints the incoming messages.

## Building the code
Create a catkin workspace.
```
mkdir catkin_ws/src
cd catkin_ws
catkin build
```
Clone this repository in the src folder.
```
cd src
git clone https://github.com/akshatpandya/ros_tutorials.git
```
Build the code
```
cd ..
catkin build ros_tutorials
source devel/setup.bash
```
To run the C++ version
```
roslaunch ros_tutorials population_roscpp.launch
```
To run the Python version
```
roslaunch ros_tutorials population_rospy.launch
```
