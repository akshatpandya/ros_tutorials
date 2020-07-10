#!/usr/bin/env python
import rospy
from ros_tutorials.msg import file_entry, population_msg
from ros_tutorials.srv import edit_field, edit_fieldResponse

def make_service_request(state_name, population):
    #function to create a service request
    rospy.wait_for_service('/edit_population')
    try:
        client_handle = rospy.ServiceProxy('/edit_population', edit_field)
        res = client_handle(state_name, population)
        return res
    except rospy.ServiceException as e:
        print("Service called failed with: %s"%e)

def subscriber_callback(msg):
    #callback function for the subscriber
    #this function prints the incoming messages
    print("-----------------------------")
    for line in msg.entry_list:
        print(line)
    print("-----------------------------")

def main():
    rospy.init_node('client_node', anonymous=True)
    rospy.Subscriber("/population", population_msg, subscriber_callback)

    #example service request
    res = make_service_request('rajasthan', 100.12)
    print(res)
    rospy.spin()

if __name__ == '__main__':
    main()