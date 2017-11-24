#version 300 es

in vec4 fragmentColour;
in vec2 fragmentPosition;
in vec2 fragmentUV;

out vec4 colour;

uniform float time;
uniform sampler2D Textu;


void main()
{
	
	vec4 textureColour = texture(Textu, fragmentUV);
	if(textureColour == vec4(0,0,0,1))
	{
		colour = fragmentColour;
	}
	else
	{
		colour = textureColour * fragmentColour;
	}
	
	//colour = vec4(fragmentColour.r * (cos(time) + 1.0) * 0.5, 
	//			  fragmentColour.g  * (cos(time)*0.3 +1.0) * 0.5,
	//			  fragmentColour.b  * (sin(time)+1.0) * 0.5,
	//			  1.0) * textureColour;
}