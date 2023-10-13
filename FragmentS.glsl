#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
   
    vec4 colour1 = texture2D(texture_1, texcoord);
	out_color = colour1;


}
