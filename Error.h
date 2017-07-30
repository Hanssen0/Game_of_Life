#ifndef OPENGL_FRAMEWORK_ERROR_H_
#define OPENGL_FRAMEWORK_ERROR_H_
#include "GLHs.h"
#include <string>
#include <vector>
class Error {
 public:
  /*Add a string after error type
  */
  Error() { clear(); }
  inline Error& operator+=(const char*); 
  const char* GetError() { return description_.c_str(); }
  bool IsGLSuccess();
  inline bool IsShaderSuccess(GLuint);
  inline bool IsProgramSuccess(GLuint);
  void set_error(bool error = true) { is_error_ = error; }
  void clear() { description_.clear(), is_error_ = false; }
 private:
  std::string description_;/*A string that describe type of error*/
  bool is_error_;
  Error & operator=(Error&) = delete;
};
Error& Error::operator+=(const char* extern_string) {
  description_ += extern_string;
  return *this;
}
bool Error::IsShaderSuccess(GLuint shader) {
  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) {
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &success);
    std::vector<char> error_log(success);
    glGetShaderInfoLog(shader, success, nullptr, &error_log[0]);
    description_ = &error_log[0];
    is_error_ = false;
    return false;
  }
  return true;
}
bool Error::IsProgramSuccess(GLuint program) {
  GLint success = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &success);
    std::vector<char> error_log(success);
    glGetProgramInfoLog(program, success, nullptr, &error_log[0]);
    description_ = &error_log[0];
    is_error_ = false;
    return false;
  }
  return true;
}
#endif
