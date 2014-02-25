#ifndef __CAMERA_H
#define __CAMERA_H

#include "glm/glm.hpp"
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4, glm::ivec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

class CCamera
{
public:
    float radius;
    float theta;
    float phi;
    glm::vec3 o;
    glm::vec3 eye;
    glm::vec3 up;

	void camera_compute(CCamera & c)
	{
		c.eye.x = cos(c.theta) * sin(c.phi) * c.radius + c.o.x;   
		c.eye.y = cos(c.phi) * c.radius + c.o.y ;
		c.eye.z = sin(c.theta) * sin(c.phi) * c.radius + c.o.z;   
		c.up = glm::vec3(0.f, c.phi < M_PI ?1.f:-1.f, 0.f);
	}

	void camera_defaults(CCamera & c)
	{
		c.phi = 3.14f/2.f;
		c.theta = 3.14f/2.f;
		c.radius = 10.f;
		camera_compute(c);
	}

	void camera_zoom(CCamera & c, float factor)
	{
		c.radius += factor * c.radius ;
		if (c.radius < 0.1)
		{
			c.radius = 10.f;
			c.o = c.eye + glm::normalize(c.o - c.eye) * c.radius;
		}
		camera_compute(c);
	}

	void camera_turn(CCamera & c, float phi, float theta)
	{
		c.theta += 1.f * theta;
		c.phi   -= 1.f * phi;
		if (c.phi >= (2 * M_PI) - 0.1f )
			c.phi = 0.00001f;
		else if (c.phi <= 0.0f )
			c.phi = 2.0f * (float)M_PI - 0.1f;
		camera_compute(c);
	}

	void camera_pan(CCamera & c, float x, float y)
	{
		glm::vec3 up(0.f, c.phi < M_PI ?1.f:-1.f, 0.f);
		glm::vec3 fwd = glm::normalize(c.o - c.eye);
		glm::vec3 side = glm::normalize(glm::cross(fwd, up));
		c.up = glm::normalize(glm::cross(side, fwd));
		c.o[0] += up[0] * y * c.radius * 2;
		c.o[1] += up[1] * y * c.radius * 2;
		c.o[2] += up[2] * y * c.radius * 2;
		c.o[0] -= side[0] * x * c.radius * 2;
		c.o[1] -= side[1] * x * c.radius * 2;
		c.o[2] -= side[2] * x * c.radius * 2;       
		camera_compute(c);
	}
};

#endif //__CAMERA_H