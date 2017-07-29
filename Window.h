#ifndef OPENGL_FRAMEWORK_HH_SHADER_H_
#define OPENGL_FRAMEWORK_HH_SHADER_H_
#include <GL/glew.h>
#include <GL/gl.h>
#include "Error.h"
class HHShader {
 public:
  HHShader& operator=(HHShader&) = delete;
  Error Init(const char*, const char*);
  void Use() { glUseProgram(shader_); }
 private:
  GLuint shader_;
};
#endif
