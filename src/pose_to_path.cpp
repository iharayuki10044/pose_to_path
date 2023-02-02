#include "pose_to_path/pose_to_path.h"

PoseToPath::PoseToPath()
:nh("~")
{
    // path_pub_ = nh_.advertise<nav_msgs::Path>("path", 1);
    marker_id_ = 0;

    // subscriber
    pose_sub = nh.subscribe("/pose", 1, &PoseToPath::poseCallback, this);

    // publisher
    marker_pub = nh.advertise<visualization_msgs::MarkerArray>("pose_marker", 1);
}

void PoseToPath::poseCallback(const geometry_msgs::PoseStampedConstPtr& msg){
    pose_data = *msg;
    marker_id_++;

    visualization_msgs::Marker marker;
    marker.header.frame_id = "map";
    marker.id = marker_id_;
    marker.pose = pose_data.pose;
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;
    marker.color.a = 1.0;
    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.05;
    marker.type = visualization_msgs::Marker::ARROW;
    marker.action = visualization_msgs::Marker::ADD;
    marker.lifetime = ros::Duration();

    pose_array.markers.push_back(marker);

    if(pose_array.markers.size() > 100){
        pose_array.markers.erase(pose_array.markers.begin());
    }

    marker_pub.publish(pose_array);
}

void PoseToPath::process(){
    ros::Rate loop_rate(10);
    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main(int argc, char** argv){
    ros::init(argc, argv, "pose_to_path");
    PoseToPath pose_to_path;
    pose_to_path.process();
    ros::spin();
}