#!/usr/bin/env python
import rospy
import csv
import os
from ros_tutorials.srv import edit_field, edit_fieldResponse
from ros_tutorials.msg import file_entry, population_msg

rows = []
sequence = 0

def read_population_file(file_name):
    #function to read the csv file and create an object 'rows' for it

    dir_path = os.path.dirname(os.path.realpath(__file__))
    with open(dir_path + '/' + file_name, mode='r') as file:
        csv_file = csv.reader(file)
        for line in csv_file:
            rows.append(line)
    # print(rows)


def edit_population(req):
    #callback function for the service server
    #this function edits the population entry corresponding to the requested state_name

    global sequence
    for line in rows:
        if line[0] == req.state_name:
            line[1] = req.population
    return edit_fieldResponse(True)


def edit_population_server():
    #this function creates the node, initializes the service server and publishes the messages

    global sequence
    res = rospy.Service('/edit_population', edit_field, edit_population)
    file_pub = rospy.Publisher('/population', population_msg, queue_size=1)
    rospy.init_node('server_node')
    while not rospy.is_shutdown():
        temp_population_msg = population_msg()
        temp_population_msg.header.seq = sequence
        temp_population_msg.header.stamp = rospy.Time.now()
        temp_population_msg.header.frame_id = 'base_frame'
        # temp_population_msg.entry_list = []
        for line in rows:
            temp_field_entry = file_entry()
            temp_field_entry.state_name = line[0]
            temp_field_entry.population = float(line[1])
            temp_population_msg.entry_list.append(temp_field_entry)
        file_pub.publish(temp_population_msg)
        sequence += 1
    
if __name__ == '__main__':
    # filename = sys.argv[2]
    filename = "../resource/india_population.csv"
    read_population_file(filename)
    edit_population_server()
