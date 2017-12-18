precision mediump float;
varying vec4 fragmentColour;
varying vec2 fragmentPosition;
varying vec2 fragmentUV;

uniform float time;
uniform sampler2D Textu;


void main()
{
	
	vec4 textureColour = texture2D(Textu, fragmentUV);
	if(textureColour == vec4(0,0,0,1))
	{
		gl_FragColor = fragmentColour;
	}
	else
	{
		gl_FragColor = textureColour * fragmentColour;
	}
	
	//colour = vec4(fragmentColour.r * (cos(time) + 1.0) * 0.5, 
	//			  fragmentColour.g  * (cos(time)*0.3 +1.0) * 0.5,
	//			  fragmentColour.b  * (sin(time)+1.0) * 0.5,
	//			  1.0) * textureColour;
}