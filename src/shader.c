#include <glad/glad.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

GLuint shader_load(char* path, GLenum type) {
    FILE* fp = fopen(path, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error loading shader: %s\n", path);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* shader_code = calloc(1, len);
    assert(shader_code != NULL);
    fread(shader_code, 1, len, fp);
    shader_code[len] = '\0';
    fclose(fp);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&shader_code, NULL);
    glCompileShader(shader);

    // check for compile errors
    GLint success, log_len;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
    char* info_log = (char*)calloc(1, log_len);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(shader, log_len, NULL, info_log);
        fprintf(stderr, "Error compiling %s shader at file: %s\n%s\n",
                (type == GL_VERTEX_SHADER) ? "vertex" : "fragment", path, info_log);
        exit(1);
    }

    free(shader_code);
    free(info_log);
    return shader;
}

GLuint shader_create(char* vs_path, char* fs_path) {
    unsigned int vertex_shader   = shader_load(vs_path, GL_VERTEX_SHADER);
    unsigned int fragment_shader = shader_load(fs_path, GL_FRAGMENT_SHADER);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // check link errors
    GLint success, log_len;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
    char* info_log = (char*)calloc(1, log_len);

    if (success == GL_FALSE) {
        glGetProgramInfoLog(program, log_len, NULL, info_log);
        fprintf(stderr, "Error linking program: %s\n", info_log);
        exit(1);
    }

    // free memory
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    free(info_log);
    return program;
}
