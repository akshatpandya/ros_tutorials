#ifndef POPULATION_NODE_H_
#define POPULATION_NODE_H_

#include <iostream>
#include <vector>
#include <ros/ros.h>
#include "ros_tutorials/edit_field.h"
#include "ros_tutorials/population_msg.h"
#include "ros_tutorials/file_entry.h"

using namespace std;


class population_node
{
	private:
		struct file_entry
		{
			string state_name;
			float population;
		};

		ros::NodeHandle* nh_;
		ros::Publisher file_pub;
		ros::ServiceServer edit_population_service;

		std::vector<file_entry> file_obj;
		char* filename_;
		int sequence;

	public:
		population_node(ros::NodeHandle* nh, char* filename);
		void get_file_in_obj();
		bool edit_population(ros_tutorials::edit_field::Request &req, ros_tutorials::edit_field::Response &res);
		void publish_population();
};


#endif
