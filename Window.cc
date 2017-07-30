#include "GLHs.h"
#include "Error.h"
#include "Window.h"
Error HHShader::kError;
const Error& HHShader::Init(const char* vertex_path, const char* fragment_path, const size_t uniform) {
  uniform_location.resize(uniform, 0);
  GLuint vertex_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_path, nullptr);
  glCompileShader(vertex_shader);
  if (kError.IsShaderSuccess(vertex_shader) != true) {
    glDeleteShader(vertex_shader);
    return kError;
  }
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_path, nullptr);
  glCompileShader(fragment_shader);
  if (kError.IsShaderSuccess(fragment_shader) != true) {
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return kError;
  }
  shader_ = glCreateProgram();
  glAttachShader(shader_, vertex_shader);
  glAttachShader(shader_, fragment_shader);
  glLinkProgram(shader_);
  if (kError.IsProgramSuccess(shader_) != true) glDeleteProgram(shader_);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  return kError;
}
