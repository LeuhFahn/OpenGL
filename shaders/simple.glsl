#if defined(VERTEX)
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Object;
uniform float Time;

in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

out vData
{
	vec2 uv;
    vec3 normal;
    vec3 position;
}vertex;

void main(void)
{	
	mat4 RotationMatrix = mat4( cos( Time ), 0.0, 	-sin( Time ), 		0.0,
								0.0,  1.0,			0.0, 		0.0,
								sin( Time ),           0.0, 		cos( Time ), 0.0,
								0.0,           0.0, 		0.0, 1.0 );
	gl_Position = Projection * View * RotationMatrix *vec4(VertexPosition, 1.0);
}

#endif

#if defined(FRAGMENT)
uniform vec3 CameraPosition;

in fData
{
	vec2 uv;
    vec3 normal;
    vec3 position;
};

out vec4 Color;

void main(void)
{
	Color = vec4(1.0, 0.0, 0.0, 0.0);
}
#endif