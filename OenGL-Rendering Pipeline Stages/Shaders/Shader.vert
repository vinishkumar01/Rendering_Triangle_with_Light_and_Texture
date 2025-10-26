#version 440

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex;

out vec4 vertices_colors;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()	
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	vertices_colors = vec4(clamp(position, 0.0f,1.0f), 1.0f);
	TexCoord = tex;
}
