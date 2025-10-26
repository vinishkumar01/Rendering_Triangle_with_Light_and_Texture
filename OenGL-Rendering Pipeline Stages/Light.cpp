#include "Light.h"


Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f); // we dont need to use the values between o and 250 or 255, even because the light values we pass in are not exactly the color, but the amount of a colr that we need to do So its sort of the color is already defined by the texture so that like a part on a brick will be red. The color of our light is telling us how much of that color on that brick will be shown
	ambientIntensity = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
}

void Light::UseLight(GLfloat ambientIntensLocation, GLfloat ambientColorLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensLocation, ambientIntensity);
}

Light :: ~Light()
{

}