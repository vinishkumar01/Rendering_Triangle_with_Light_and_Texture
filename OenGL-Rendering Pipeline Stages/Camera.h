#pragma once

#include<GL\glew.h>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

#include<GLFW/glfw3.h>


class Camera
{
public:
	Camera();

	Camera(glm::vec3 startPostion, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed, GLfloat startTurnSpeed);

	void KeyControls(bool* keys, GLfloat deltaTime);
	void MouseControls(GLfloat XChange, GLfloat YChange);

	glm::mat4 calculateViewMatrix();

	~Camera();

private:

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	//														  |	
	GLfloat Yaw; // X Angle -- Horizontal -2 -1 0 1 2   <-----+----->
	GLfloat Pitch; // Y Angle -- Vertical  2 1 0 -1 -2        |

	GLfloat MovementSpeed;
	GLfloat turnSpeed;

	void Update();
};

