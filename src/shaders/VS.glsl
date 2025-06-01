#version 420 core

layout (location = 0) in vec2 inPositionMesh;

out vec2 position;

void main()
{
	position = inPositionMesh;
	gl_Position = vec4(inPositionMesh, 0, 1);
}
