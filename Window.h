#ifndef OPENGL_FRAMEWORK_WINDOW_H_
#define OPENGL_FRAMEWORK_WINDOW_H_
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include "Error.h"
class HHShader {
 public:
  HHShader& operator=(HHShader&) = delete;
  const Error& Init(const char*, const char*, const std::size_t);
  void Use() { glUseProgram(shader_); }
  inline const Error& find(const char*, const std::size_t);
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
#endif
