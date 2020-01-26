#pragma once
#include <cmath>
#include <vector>

namespace physics
{
	double frame_time = 0.10;
	const double GRAVITATIONAL_CONST = 0.01;

	enum phy_vector_type {
		PHY_VECTOR_FORCE,
		PHY_VECTOR_ACCELERATION,
		PHY_VECTOR_VELOCITY,
	};

	struct phy_vector {
		phy_vector_type type;
		double x;
		double y;
	};

	struct phy_space_body {
		double mass;
		double x;
		double y;
		double radius;
		phy_vector velocity;
		phy_vector net_force;
		phy_vector acceleration;
		phy_vector propulsion;

		void calc_net_force(std::vector<physics::phy_vector> forces)
		{
			net_force = propulsion;
			for (int i = 0; i < forces.size(); i++)
			{
				net_force.x += forces[i].x;
				net_force.y += forces[i].y;
			}
		}

		void calc_acceleration()
		{
			acceleration.x = net_force.x / mass;
			acceleration.y = net_force.y / mass;
		}

		void calc_velocity()
		{
			velocity.x += acceleration.x * frame_time;
			velocity.y += acceleration.y * frame_time;
		}

		void displace()
		{
			x += velocity.x * frame_time;
			y += velocity.y * frame_time;
		}
	};

	phy_vector calc_gravity(phy_space_body* a, phy_space_body* b) 
	{
		double deltaX = a->x - b->x;
		double deltaY = a->y - b->y;
		double distance_sq = deltaX * deltaX + deltaY * deltaY;
		double gravity = GRAVITATIONAL_CONST * a->mass * b->mass / distance_sq;
		double angle = atan((a->y - b->y) / (a->x - b->x));
		phy_vector return_val;
		return_val.type = PHY_VECTOR_FORCE;

		if (deltaX < 0) {
			return_val.x = cos(angle) * gravity;
			return_val.y = sin(angle) * gravity;
		}
		else {
			return_val.x = -cos(angle) * gravity;
			return_val.y = -sin(angle) * gravity;
		}

		return return_val;
	}

	void phy_loop(std::vector<phy_space_body*> bodies) {

		std::vector<std::vector<phy_vector>> forces;
		for (int i = 0; i < bodies.size(); i++)
		{
			forces.push_back(std::vector<phy_vector>{});
		}
		for (int i = 0; i < bodies.size(); i++)
		{
			for (int j = i + 1; j < bodies.size(); j++)
			{
				if (j >= bodies.size())
				{
					break;
				}
				phy_vector gravity = calc_gravity(bodies[i], bodies[j]);
				forces[i].push_back(gravity);
				forces[j].push_back(gravity);
				forces[j].back().x = -gravity.x;
				forces[j].back().y = -gravity.y;
			}
			bodies[i]->calc_net_force(forces[i]);
			bodies[i]->calc_acceleration();
			bodies[i]->calc_velocity();
			bodies[i]->displace();
		}
	}
}