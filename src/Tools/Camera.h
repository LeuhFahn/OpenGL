#ifndef __CAMERA_H
#define __CAMERA_H

#include "glm/glm.hpp"
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4, glm::ivec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

struct SGUIStates
{
    bool m_bPanLock;
    bool m_bturnLock;
    bool m_bZoomLock;
    int m_nLockPositionX;
    int m_nLockPositionY;
    int m_nCamera;
    double m_dTime;
    bool m_bPlaying;
    static const float MOUSE_PAN_SPEED;
    static const float MOUSE_ZOOM_SPEED;
    static const float MOUSE_TURN_SPEED;

	void init_gui_states()
	{
		m_bPanLock = false;
		m_bturnLock = false;
		m_bZoomLock = false;
		m_nLockPositionX = 0;
		m_nLockPositionY = 0;
		m_nCamera = 0;
		m_dTime = 0.0;
		m_bPlaying = false;
	}
};

class CCamera
{
public:
    float m_fRadius;
    float m_fTheta;
    float m_fPhi;
	float m_fFov;
	float m_fNear;
	float far;
	float m_fWidth;
	float m_fHeight;
    glm::vec3 o;
    glm::vec3 eye;
    glm::vec3 up;

	glm::mat4 projection;
    glm::mat4 worldToView;
	glm::mat4 worldToScreen;

	void camera_compute()
	{
		eye.x = cos( m_fTheta) * sin( m_fPhi) *  m_fRadius +  o.x;   
		eye.y = cos( m_fPhi) *  m_fRadius +  o.y ;
		eye.z = sin( m_fTheta) * sin( m_fPhi) *  m_fRadius +  o.z;    
		up = glm::vec3(0.f,  m_fPhi < M_PI ?1.f:-1.f, 0.f);

		projection = glm::perspective( m_fFov,  m_fWidth /  m_fHeight,  m_fNear,  far); 
		worldToView = glm::lookAt( eye,  o,   up);
		worldToScreen = projection * worldToView;
	}

	void camera_defaults()
	{
		m_fPhi = 3.14f/2.f;
		m_fTheta = 3.14f/2.f;
		m_fRadius = 10.f;
		m_fFov = 45.f;
		m_fNear = 0.1f;
		far = 1000.f;
		camera_compute();
	}

	void camera_zoom(float factor)
	{
		 m_fRadius += factor *  m_fRadius ;
		if ( m_fRadius < 0.1)
		{
			 m_fRadius = 10.f;
			 o =  eye + glm::normalize( o -  eye) *  m_fRadius;
		}
		camera_compute();
	}

	void camera_turn(float fPhi, float fTheta)
	{
		m_fTheta += 1.f * fTheta;
		m_fPhi   -= 1.f * fPhi;
		if ( m_fPhi >= (2 * M_PI) - 0.1f )
			 m_fPhi = 0.00001f;
		else if ( m_fPhi <= 0.0f )
			 m_fPhi = 2.0f * (float)M_PI - 0.1f;
		camera_compute();
	}

	void camera_pan(float x, float y)
	{
		glm::vec3 up(0.f,  m_fPhi < M_PI ?1.f:-1.f, 0.f);
		glm::vec3 fwd = glm::normalize( o -  eye);
		glm::vec3 side = glm::normalize(glm::cross(fwd, up));
		up = glm::normalize(glm::cross(side, fwd));
		o[0] += up[0] * y *  m_fRadius * 2;
		o[1] += up[1] * y *  m_fRadius * 2;
		o[2] += up[2] * y *  m_fRadius * 2;
		o[0] -= side[0] * x *  m_fRadius * 2;
		o[1] -= side[1] * x *  m_fRadius * 2;
		o[2] -= side[2] * x *  m_fRadius * 2;       
		camera_compute();
	}

	void SetSizeScreen(float fWidth, float fHeight)
	{
		m_fWidth = fWidth;
		m_fHeight = fHeight;
		camera_compute();
	}
};

#endif //__CAMERA_H