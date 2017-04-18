#version 410

in vec2					TexCoords;
out vec4				frag_colour;

uniform sampler2D		text;
uniform vec3			textColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, (texture(text, TexCoords)).r);
	frag_colour = vec4(textColor, 1.0) * sampled;
}
