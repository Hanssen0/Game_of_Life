#ifndef OPENGL_FRAMEWORK_WINDOW_H_
#define OPENGL_FRAMEWORK_WINDOW_H_
#include "GLHs.h" 
#include <vector>
#include "Error.h"
class HHShader {
 public:
  HHShader& operator=(HHShader&) = delete;
  const Error& Init(const char*, const char*, const std::size_t);
  void Use() { glUseProgram(shader_); }
  inline const Error& find(const char*, const std::size_t);
  inline const Error& SetUniform(const std::size_t, const int);
  inline const Error& SetUniformByName(const char*, const int);
  inline const Error& SetUniform(const std::size_t, const float);
  inline const Error& SetUniformByName(const char*, const float);
  static Error kError;
 private:
  GLuint shader_;
  std::vector<GLuint> uniform_location;
};
const Error& HHShader::find(const char* name, const std::size_t location) {
  if (uniform_location.size() >= location) { 
    kError.clear();
    kError.set_error();
    kError += "Location not exist";
    return kError;
  }
  uniform_location[location] = glGetUniformLocation(shader_, name);
  kError.IsGLSuccess();
  return kError;
}
const Error& HHShader::SetUniform(const std::size_t location, const int value) {
  glUniform1i(uniform_location[location], value);
  kError.IsGLSuccess();
  return kError;
}
const Error& HHShader::SetUniformByName(const char* location, const int value) {
  glUniform1i(glGetUniformLocation(shader_, location), value);
  kError.IsGLSuccess();
  return kError;
}
const Error& HHShader::SetUniform(const std::size_t location, const float value) {
  glUniform1f(uniform_location[location], value);
  kError.IsGLSuccess();
  return kError;
}
const Error& HHShader::SetUniformByName(const char* location, const float value) {
  glUniform1f(glGetUniformLocation(shader_, location), value);
  kError.IsGLSuccess();
  return kError;
}
#endif
