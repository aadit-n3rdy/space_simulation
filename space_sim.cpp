#define GLEW_STATIC 1


#include "physics.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <GLFW/glfw3.h>


#define WIDTH 2560
#define HEIGHT 1440

const double PI = atan (1) * (double) 4.0;

void error_callback (int error, const char *description)
{
	std::cerr << "Error: " << description << std::endl;
}

void draw_circle (double x, double y, double r, double resolution)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < resolution; i++)
	{		
		double angle1 = 2 * PI * i / resolution;
		glVertex2f ((x + r * cos (angle1))/WIDTH, (y + r * sin (angle1))/HEIGHT);
	}
	glEnd ();
}

int main ()
{
	GLFWwindow *window;
	
	if (!glfwInit ())
		return -1;
	
	window = glfwCreateWindow (WIDTH, HEIGHT, "Space simulation", NULL, NULL);
	if (!window)
		{
			glfwTerminate ();
			return -1;
		}
	
	glfwMakeContextCurrent (window);
	int r = 100;
	std::vector<physics::phy_space_body *> bodies;
	bodies.push_back ((physics::phy_space_body *) std::malloc (sizeof (physics::phy_space_body)));
	bodies.push_back ((physics::phy_space_body *) std::malloc (sizeof (physics::phy_space_body)));
	double velocity = 150;
	bodies[1]->mass = 1000000000;
	bodies[1]->radius = 50;
	bodies[1]->x = r;
	bodies[1]->y = 0;
	bodies[1]->velocity  ={ physics::phy_vector_type::PHY_VECTOR_VELOCITY, 0, velocity };
	bodies[1]->net_force = { physics::phy_vector_type::PHY_VECTOR_FORCE, 0, 0 };
	bodies[1]->acceleration = { physics::phy_vector_type::PHY_VECTOR_ACCELERATION, 0, 0 };
	bodies[1]->propulsion = { physics::phy_vector_type::PHY_VECTOR_FORCE, 0, 0 };
	
	bodies[0]->mass = 1000000000;
	bodies[0]->radius = 50;
	bodies[0]->x = -r;
	bodies[0]->y = 0;
	bodies[0]->velocity = { physics::phy_vector_type::PHY_VECTOR_VELOCITY, 0, -velocity};
	bodies[0]->net_force = { physics::phy_vector_type::PHY_VECTOR_FORCE, 0, 0 };
	bodies[0]->acceleration = { physics::phy_vector_type::PHY_VECTOR_ACCELERATION, 0, 0 };
	bodies[0]->propulsion = { physics::phy_vector_type::PHY_VECTOR_FORCE, 0, 0 };

	double current_frame = glfwGetTime();
	double last_frame = current_frame;
	while (!glfwWindowShouldClose (window))
	{
		current_frame = glfwGetTime();
		physics::frame_time = current_frame - last_frame;
		last_frame = current_frame;
		physics::phy_loop(bodies);
		glClear (GL_COLOR_BUFFER_BIT);
		for (int i = 0; i < bodies.size (); i++)
		{
			draw_circle (bodies[i]->x, bodies[i]->y, bodies[i]->radius, 2 * bodies[i]->radius);
		}		
		glfwSwapBuffers (window);
		glfwPollEvents ();
	}
	
	glfwTerminate ();
	return 0;
}
