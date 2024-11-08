#pragma once
#ifndef GAZEBO_PLUGINS__GAZEBO_ROS_TEMPLATE_HPP_
#define GAZEBO_PLUGINS__GAZEBO_ROS_TEMPLATE_HPP_

#include <string>
#include <vector>

#include "gazebo/gazebo.hh"
#include <gazebo/physics/physics.hh>
#include "gazebo/physics/PhysicsTypes.hh"
#include <gazebo/transport/TransportTypes.hh>
#include <gazebo/common/Time.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/Events.hh>
#include "gazebo/msgs/msgs.hh"
#include "gazebo/transport/transport.hh"

#include <gazebo_ros/node.hpp>
#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>

namespace gazebo {

class PickupPlugin : public ModelPlugin {
	public:
		PickupPlugin();
		virtual ~PickupPlugin();
		void Load( physics::ModelPtr _model, sdf::ElementPtr);

	private:
	   	bool attach();

	   	bool detach();

		physics::ModelPtr findNearbyObject();

		  /// Node for ROS communication.
  		gazebo_ros::Node::SharedPtr ros_node_;

		rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr dockStatusPub;
		rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr dockControlSub;

		rclcpp::TimerBase::SharedPtr initial_attaching_timer;
		
		physics::ModelPtr model;
		physics::WorldPtr world;
		physics::PhysicsEnginePtr physics;
		physics::JointPtr joint;
		physics::LinkPtr sensor_link;

		std::string pickup_object_allowable_prefix = "";

		double allowable_offset_height = 0.15;
		double allowable_offset_horizontal = 0.2;

		int jointCounter;

   	};

}


#endif  // GAZEBO_PLUGINS__GAZEBO_ROS_TEMPLATE_HPP_
