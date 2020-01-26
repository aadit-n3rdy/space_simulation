#define GLEW_STATIC 1


#include "physics.h"
#include <iostream>
#include <fstream>
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
	std::string file_name;
	std::cin >> file_name;
	std::ifstream file(file_name);
	if (!file.is_open()) {
		std::cerr << "Could not open file";
		return -1;
	}
	int body_count;
	file >> body_count;	
	if (!glfwInit ())
		return -1;
	
	window = glfwCreateWindow (WIDTH, HEIGHT, "Space simulation", NULL, NULL);
	if (!window)
		{
			glfwTerminate ();
			return -1;
		}
	
	glfwMakeContextCurrent (window);
	std::vector<physics::phy_space_body *> bodies;
	for (int i = 0; i < body_count; i++) {
		bodies.push_back((physics::phy_space_body*) std::malloc(sizeof(physics::phy_space_body)));
		file >> bodies[i]->mass;
		file >> bodies[i]->x;
		file >> bodies[i]->y;
		file >> bodies[i]->radius;
		file >> bodies[i]->velocity.x;
		file >> bodies[i]->velocity.y;		;
		file >> bodies[i]->propulsion.x;
		file >> bodies[i]->propulsion.y;

	}

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
