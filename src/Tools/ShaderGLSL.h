#pragma once

#include "GLCommon.h"

struct SShaderGLSL
{
	enum ShaderType
	{
		VERTEX_SHADER = 1,
		FRAGMENT_SHADER = 2,
		GEOMETRY_SHADER = 4
	};
	GLuint program;
};

int compile_and_link_shader(SShaderGLSL & shader, int typeMask, const char * sourceBuffer, int bufferSize);
int destroy_shader(SShaderGLSL & shader);
int load_shader_from_file(SShaderGLSL & shader, const char * path, int typemask);
