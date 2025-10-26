#include "Camera.h"



Camera :: Camera(){}

Camera::Camera(glm::vec3 startPostion, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed, GLfloat startTurnSpeed)
{
	position = startPostion;
	worldUp = startUp;
	Yaw = startYaw;
	Pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	MovementSpeed = startMovementSpeed;
	turnSpeed = startTurnSpeed;

	Update();
}

void Camera::KeyControls(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = MovementSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	else if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	else if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
	else if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
}

void Camera::MouseControls(GLfloat XChange, GLfloat YChange)
{
	XChange *= turnSpeed;
	YChange *= turnSpeed;

	Yaw += XChange;
	Pitch += YChange;

	if (Pitch > 89.0f) // Setting limit so that the camera cannot go after 90^ degree
	{
		Pitch = 89.0f;
	}
	else if (Pitch < -89.0f)
	{
		Pitch = -89.0f;
	}

	Update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::Update()
{
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front = glm::normalize(front); // When we are trying to normalize a vector, we are trying to remove the magnitude. there will be magnitude, we will be setting the magnitude to 1, so basically we are saying that 1 unit in this direction

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera :: ~Camera()
{

}