#include "ros_tutorials/population_node.h"

void main(int argc, char const *argv[])
{
	ros::init(argc,argv,"population_node");

	ros::NodeHandle* nh;
	nh = new ros::NodeHandle();

	population_node obj(nh, argv[1]);
	while(ros::ok())
	{
		obj.publish_population();
		ros::spinOnce();
	}

	return 0;
}