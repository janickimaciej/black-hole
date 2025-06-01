#version 420 core

const float PI = 3.14159265;

struct BlackHole
{
	vec3 position;
	float mass;
};

in vec2 position;

uniform float nearPlane;
uniform float farPlane;
uniform vec3 cameraPosition;
uniform mat4 projectionViewInverse;
uniform BlackHole blackHole;
uniform samplerCube skybox;

out vec4 outColor;

vec3 getIncident();
float getDeflectionAngle(float rayBlackHoleDistance);
float solveDepressedCubicEquation(float p, float q);
float findUpperLimit(float constTerm);
float fun(float w, float constTerm);
float funDeriv(float w, float constTerm);

void main()
{
	vec3 unitIncident = normalize(getIncident());
	float t = dot(blackHole.position - cameraPosition, unitIncident);
	vec3 closestPoint = cameraPosition + t * unitIncident;
	vec3 unitOrthogonal = normalize(blackHole.position - closestPoint);

	float deflectionAngle = getDeflectionAngle(length(blackHole.position - closestPoint));
	if (deflectionAngle < -0.5 || deflectionAngle > 2 * PI)
	{
		outColor = vec4(0, 0, 0, 1);
		return;
	}

	vec3 deflected = cos(deflectionAngle) * unitIncident + sin(deflectionAngle) * unitOrthogonal;

	outColor = texture(skybox, deflected);
}

vec3 getIncident()
{
	return (projectionViewInverse * (farPlane * vec4(position, 1, 1) -
		nearPlane * vec4(position, -1, 1))).xyz;
}

float getDeflectionAngle(float rayBlackHoleDistance)
{
	const int iterations = 100;
	float constTerm = 2 * blackHole.mass / rayBlackHoleDistance;
	float w1 = findUpperLimit(constTerm);
	if (w1 < 0)
	{
		return -1;
	}
	float dw = w1 / iterations;

	float sum = 0;
	float w = dw / 2.0;
	for (int i = 0; i < iterations; ++i)
	{
		sum += pow(fun(w, constTerm), -0.5f);
		w += dw;
	}

	return 2 * sum * dw - PI;
}

float solveDepressedCubicEquation(float p, float q)
{
	float squareRootTerm = sqrt(pow(q, 2) / 4.0 + pow(p, 3) / 27.0);
	return pow(-q / 2.0 + squareRootTerm, 1.0 / 3.0) +
		pow(-q / 2.0 - squareRootTerm, 1.0 / 3.0);
}

float findUpperLimit(float constTerm)
{
	float w = 1.0;

	for (int i = 0; i < 100; ++i)
	{
		float newW = w - fun(w, constTerm) / funDeriv(w, constTerm);
		if (abs(newW - w) < 0.001f)
		{
			return newW;
		}
		w = newW;
	}
	return -1;
}

float fun(float w, float constTerm)
{
	return 1 - w * w * (1 - constTerm * w);
}

float funDeriv(float w, float constTerm)
{
	return w * (-2 + 3 * constTerm * w);
}
