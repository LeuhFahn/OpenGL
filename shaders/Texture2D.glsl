#if defined(VERTEX)
uniform float Time;

in GL_TEXTURE_2D in_Texture;

out vec3 color;

void main()
{
    gl_Position = vec4(in_Vertex, 0.0, 1.0);
    color = in_Color;
}

#endif

#if defined(FRAGMENT)

in vec3 color;

out vec4 out_Color;

void main()
{
    out_Color = vec4(color, 1.0);
	//out_Color = vec4(1.0,0.0,0.0, 1.0);
}

#endif