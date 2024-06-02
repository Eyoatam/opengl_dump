#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

GLuint shader_create(char* vs_path, char* fs_path);
GLuint shader_load(char* path, GLenum type);

#endif
