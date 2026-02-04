#version 420 core

layout (location = 0) in vec2 inPosMesh;

out vec2 pos;

void main()
{
	pos = inPosMesh;
	gl_Position = vec4(inPosMesh, 0, 1);
}
