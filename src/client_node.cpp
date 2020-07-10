#include "ros_tutorials/client_node.h"

using namespace std;

client_node::client_node(ros::NodeHandle* nh)
{
	nh_ = nh;
	file_sub = nh_->subscribe("/population",1, &client_node::population_callback,this);
	client = nh_->serviceClient<ros_tutorials::edit_field>("/population_service");
}

void client_node::make_service_request(string state_name, float population)
{
	ros_tutorials::edit_field srv;
	srv.request.state_name = state_name;
	srv.request.population = population;

	if (client.call(srv))
      ROS_INFO("response: %d", srv.response.status);
    else
      ROS_ERROR("Failed to call service");
}

void client_node::population_callback(const ros_tutorials::population_msg& msg)
{
	cout<<"---------------------------------------------\n";
	for(int i=0; i<msg.entry_list.size(); i++)
	{
		cout<<"State: "<<msg.entry_list[i].state_name<<" Population: "<<msg.entry_list[i].population<<endl;
	}
	cout<<"---------------------------------------------\n";
}

int  main(int argc, char *argv[])
{
	ros::init(argc,argv,"client_node");

	ros::NodeHandle* nh;
	nh = new ros::NodeHandle();

	client_node obj(nh);

	ros::spinOnce();

	obj.make_service_request("rajasthan",75.2);
	
	ros::spin();

	return 0;
}