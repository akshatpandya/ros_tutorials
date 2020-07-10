#include "ros_tutorials/population_node.h"
#include <fstream>
#include <string>

using namespace std;


bool population_node::edit_population(ros_tutorials::edit_field::Request& req, ros_tutorials::edit_field::Response& res)
{
	for(int i=0; i<file_obj.size(); i++)
	{
		if(file_obj[i].state_name == req.state_name)
		{
			file_obj[i].population = req.population;
			res.status = true;
			return true;
		}
	}
	return false;
}

population_node::population_node(ros::NodeHandle* nh, char* filename)
{
	// nh_ = new ros::NodeHandle();
	nh_ = nh;
	filename_ = filename;
	// ROS_INFO("%s",filename_);
	file_pub = nh_->advertise<ros_tutorials::population_msg>("/population",1);
	edit_population_service = nh_->advertiseService("/population_service", &population_node::edit_population, this);
	sequence = 0;
	get_file_in_obj();
}

void population_node::get_file_in_obj()
{	
	string line;
	file_entry temp;
	// ifstream f(filename_);
	// f.open(filename_,ios::in);

	std::ifstream filein(filename_);

    
	
	if(!filein.is_open())
		ROS_INFO(	"Unable to open the file\n");
	else
	{
		ROS_INFO("File is open!\n");

		for (std::string line; std::getline(filein, line); )
	    {
	    	// ROS_INFO("%s",line);
	        // std::cout << line << std::endl;
	        std::stringstream s(line);
			std::vector<string> row;
			string word;
			while(getline(s,word,','))
			{
				row.push_back(word);
				// cout<<word<<endl;
			}

			temp.state_name = row[0];
			temp.population = stof(row[1]);

			file_obj.push_back(temp);
		}
		// cout<<file_obj.size();
		filein.close();
	}
}



void population_node::publish_population()
{
	ros_tutorials::population_msg temp_msg;
	ros_tutorials::file_entry temp;

	temp_msg.header.seq = sequence;
	temp_msg.header.stamp = ros::Time::now();
	temp_msg.header.frame_id = "base";

	for(int i=0; i<file_obj.size(); i++)
	{
		temp.state_name = file_obj[i].state_name;
		temp.population = file_obj[i].population;
		temp_msg.entry_list.push_back(temp);
	}

	sequence += 1;

	file_pub.publish(temp_msg);
}



int main(int argc, char *argv[])
{
	ros::init(argc,argv,"population_node");

	ros::NodeHandle* nh;
	nh = new ros::NodeHandle();

	population_node obj(nh, argv[1]);
	ROS_INFO("%s",argv[1]);
	// obj.get_file_in_obj();
	while(ros::ok())
	{
		obj.publish_population();
		ros::spinOnce();
	}

	return 0;
}