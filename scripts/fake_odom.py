#! /usr/bin/python


import rospy
from geometry_msgs.msg import TwistStamped 


if __name__ == '__main__':
    rospy.init_node('fake_odom')
    fake_odom_pub = rospy.Publisher('/front_esr/as_rx/vehicle_motion', TwistStamped, queue_size=10)
    car_motion_msg = TwistStamped()
    
    while not rospy.is_shutdown(): 
    
        car_motion_msg.twist.linear.x = 0.0 
        car_motion_msg.twist.linear.y = 0.0
        car_motion_msg.twist.linear.z = 0.0
        
        car_motion_msg.twist.angular.x = 0.0 
        car_motion_msg.twist.angular.y = 0.0
        car_motion_msg.twist.angular.z = 0.0
        
        
        car_motion_msg.header.stamp = rospy.Time.now()
        
        
        fake_odom_pub.publish(car_motion_msg)
        rospy.sleep(0.1)
        rospy.spin()