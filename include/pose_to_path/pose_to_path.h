#ifndef __POSE_TO_PATH_H__
#define __POSE_TO_PATH_H__

#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

class PoseToPath{
    public:
        PoseToPath(void);
        void process();
        void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg);
        void publishMarker(void);
    private:
        ros::NodeHandle nh;
        ros::Subscriber pose_sub;
        ros::Publisher marker_pub;
        int marker_id_;
        geometry_msgs::PoseStamped pose_data;
        visualization_msgs::MarkerArray pose_array;
};
#endif