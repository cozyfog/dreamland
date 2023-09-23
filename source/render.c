#define _UTILS_WIN32

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "gl/glew.h"
#include "typedef.h"
#include "utils.h"
#include "cmath.h"
#include "vector.h"
#include "render.h"
#include "core.h"

global u32 vao;
global u32 vbo;
global u32 shader;

global f32 *projection_matrix;
global Core *core;

global const char *vertex_source =
"#version 460 core\n"
"layout (location = 0) in vec3 i_pos;\n"
"layout (location = 1) in vec2 i_tex_coord;\n"
"uniform mat4 u_projection;\n"
"uniform vec3 u_scale;\n"
"uniform vec3 u_pos;"
"out vec2 tex_coord;\n"
"void main() {\n"
"  mat4 scale = mat4(u_scale.x, 0, 0, 1, 0, u_scale.y, 0, 1, 0, 0, u_scale.z, 1, 0, 0, 0, 1);\n"
"  gl_Position = (vec4(i_pos, 1.0f) * scale + vec4(u_pos, 1.0f)) * u_projection;\n"
"  tex_coord = vec2(i_tex_coord.x, 1.0f - i_tex_coord.y);\n"
"}\0";

global const char *fragment_source =
"#version 460 core\n"
"out vec4 color;\n"
"in vec2 tex_coord;\n"
"uniform sampler2D u_texture;\n"
"void main() {\n"
"  vec4 tex_color = texture(u_texture, tex_coord);\n"
"  if (tex_color.a == 0.0)\n"
"    discard;\n"
"  color = tex_color;\n"
"}\0";

global f32 vertices[] = {
	// Vert Coords        //Tex Coords
	-0.5f, +0.5f, +0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, +0.0f,  0.0f, 0.0f,
	+0.5f, -0.5f, +0.0f,  1.0f, 0.0f,
	
	+0.5f, -0.5f, +0.0f,  1.0f, 0.0f,
	+0.5f, +0.5f, +0.0f,  1.0f, 1.0f,
	-0.5f, +0.5f, +0.0f,  0.0f, 1.0f
};

void renderEntry() {
	core = getGlobalCore();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	projection_matrix = newOrthoProjectionMatrix(-SCREEN_VIEW_WIDTH / 4, SCREEN_VIEW_WIDTH / 4, -SCREEN_VIEW_HEIGHT / 4, SCREEN_VIEW_HEIGHT / 4, -1.0f, 1.0f);
	
	// Shader
	u32 vertex;
	u32 fragment;
	i32 success;
	char info_log[512];
	
	// ERROR(daniel): Create vertex shader.
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_source, NULL);
	glCompileShader(vertex);
	
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vertex, 512, NULL, info_log);
	assert(success, info_log);
	
	// ERROR(daniel): Create fragment shader.
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_source, NULL);
	glCompileShader(fragment);
	
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(fragment, 512, NULL, info_log);
	assert(success, info_log);
	
	// ERROR(daniel): Create and Link shader program.
	shader = glCreateProgram();
	glAttachShader(shader, vertex);
	glAttachShader(shader, fragment);
	glLinkProgram(shader);
	
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(shader, 512, NULL, info_log);
	assert(success, info_log);
	
	// Delete unsused shaders.
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	// Using shaders and rendering.
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, NULL);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
}

void renderDrawSprite(u32 sprite, vec3 pos, vec3 scale) {
	glUseProgram(shader);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, sprite);
	
	glUniform1i(glGetUniformLocation(shader, "u_texture"), 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "u_projection"), 1, false, projection_matrix);
	glUniform3f(glGetUniformLocation(shader, "u_scale"), scale.x, scale.y, scale.z);
	glUniform3f(glGetUniformLocation(shader, "u_pos"), pos.x, pos.y, pos.z);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void renderUpdate() {
	glUseProgram(shader);
	glBindVertexArray(vao);
	
	for (u64 i = 0; i < core->entity_count; ++i) {
		Entity *entity = core->entities[i];
		
		glBindTexture(GL_TEXTURE_2D, entity->sprite);
		
		glUniform1i(glGetUniformLocation(shader, "u_texture"), 0);
		glUniformMatrix4fv(glGetUniformLocation(shader, "u_projection"), 1, false, projection_matrix);
		glUniform3f(glGetUniformLocation(shader, "u_scale"), entity->scale.x, entity->scale.y, entity->scale.z);
		glUniform3f(glGetUniformLocation(shader, "u_pos"), entity->pos.x, entity->pos.y, entity->pos.z);
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	
	glBindVertexArray(0);
	glFinish();
}