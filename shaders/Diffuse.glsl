#if defined(VERTEX)
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Object;
uniform float Time;
uniform int nSqrtNbInstance;

in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

out vec2 uv;
out vec3 normal;
out vec3 position;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{	
	mat4 RotationMatrix = mat4( cos( Time ), 0.0, 	-sin( Time ), 		0.0,
								0.0,  1.0,			0.0, 		0.0,
								sin( Time ),           0.0, 		cos( Time ), 0.0,
								0.0,           0.0, 		0.0, 1.0 );
								
	uv = VertexTexCoord;
	normal = vec3(Object * vec4(VertexNormal, 1.0));; 
	position = vec3(Object * vec4(VertexPosition, 1.0));
	position.x += (gl_InstanceID%nSqrtNbInstance); 
	position.z += (gl_InstanceID/nSqrtNbInstance); 
	position.y +=  cos(rand(vec2(gl_InstanceID, 1.0f)) * Time * (gl_InstanceID%10 + 1));
	gl_Position = Projection * View * vec4(position, 1.0);
}

#endif

#if defined(FRAGMENT)
uniform sampler2D Diffuse;

in vec2 uv;
in vec3 normal;
in vec3 position;

out vec4 Color;

void main(void)
{
	vec3 diffuse = texture(Diffuse, uv).rgb;
	Color = vec4(diffuse, 0.0);
}
#endif