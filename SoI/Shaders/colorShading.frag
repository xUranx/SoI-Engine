#version 130

in vec4 fragmentColour;
in vec2 fragmentPosition;

out vec4 colour;

uniform float time;

void main()
{
	colour = vec4(fragmentColour.r * (cos(fragmentPosition.x * 4.0 + time) + 1.0) * 0.5, 
				  fragmentColour.g  * (cos(fragmentPosition.y * 8.0 + time)+1.0) * 0.5,
				  fragmentColour.b  * (cos(fragmentPosition.x * 1.4 + time)+1.0) * 0.5,
				  1.0);
}