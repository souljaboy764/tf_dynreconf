#include <ros/ros.h>

#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

#include <geometry_msgs/TransformStamped.h>

#include <dynamic_reconfigure/server.h>
#include <tf_dynreconf/TFConfig.h>



geometry_msgs::TransformStamped transformStamped;

void callback(tf_dynreconf::TFConfig &config, uint32_t level) 
{
	ROS_INFO_STREAM("Reconfigure Request: "<< config.x <<" "<< config.y <<" "<< config.z <<" "<< config.roll <<" "<< config.pitch <<" "<< config.yaw <<" "<<  config.source_frame <<" "<< config.target_frame);
	
	tf2::Quaternion q;
	q.setRPY(config.roll, config.pitch, config.yaw);
	
	transformStamped.transform.translation.x = config.x;
	transformStamped.transform.translation.y = config.y;
	transformStamped.transform.translation.z = config.z;
	transformStamped.transform.rotation.x = q.x();
	transformStamped.transform.rotation.y = q.y();
	transformStamped.transform.rotation.z = q.z();
	transformStamped.transform.rotation.w = q.w();
	transformStamped.header.frame_id = config.source_frame;
	transformStamped.child_frame_id = config.target_frame;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "tf_dynreconf");
	static tf2_ros::TransformBroadcaster br;
	ros::Rate loop_rate(10);

	dynamic_reconfigure::Server<tf_dynreconf::TFConfig> server;
	dynamic_reconfigure::Server<tf_dynreconf::TFConfig>::CallbackType f;

	f = boost::bind(&callback, _1, _2);
	server.setCallback(f);

	ROS_INFO("Spinning node");
	while(ros::ok())
	{	
		transformStamped.header.stamp = ros::Time::now();
		br.sendTransform(transformStamped);
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}