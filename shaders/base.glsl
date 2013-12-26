#if defined(VERTEX)
out vec4 vFragColor;
void main() 
{
	vFragColor = vec4(1.0, 0.0, 0.0, 1.0);
}

#endif

#if defined(FRAGMENT)

in vec4 vFragColor;
out vec4 color;
void main() 
{
	color = vec4(1.0,0.0,0.0,0.0);//vFragColor;
}
#endif