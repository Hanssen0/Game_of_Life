#ifndef OPENGL_FRAMEWORK_ERROR_H_
#define OPENGL_FRAMEWORK_ERROR_H_
#include "GLHs.h"
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
class Error {
 public:
  /*Add a string after error type
  */
  Error() { clear(); }
  inline Error& operator+=(const char*); 
  const char* GetError() { return description_.c_str(); }
  const bool is_error() const { return is_error_; }
  bool IsGLSuccess();
  inline bool IsShaderSuccess(const GLuint);
  inline bool IsProgramSuccess(const GLuint);
  inline bool IsSDLSuccess(const SDL_Window*);
  inline bool IsSDLSuccess(const SDL_GLContext&);
  inline bool IsGlewSuccess(const GLenum);
  void set_error(const bool error = true) { is_error_ = error; }
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
bool Error::IsShaderSuccess(const GLuint shader) {
  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) {
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &success);
    std::vector<char> error_log(success);
    glGetShaderInfoLog(shader, success, nullptr, &error_log[0]);
    description_ = &error_log[0];
    is_error_ = true;
    return false;
  }
  return true;
}
bool Error::IsProgramSuccess(const GLuint program) {
  GLint success = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &success);
    std::vector<char> error_log(success);
    glGetProgramInfoLog(program, success, nullptr, &error_log[0]);
    description_ = &error_log[0];
    is_error_ = true;
    return false;
  }
  return true;
}
bool Error::IsSDLSuccess(const SDL_Window* window) {
  if (window == nullptr) {
    description_ = SDL_GetError();
    is_error_ = true;
    return false;
  }
  return true;
}
bool Error::IsSDLSuccess(const SDL_GLContext& context) {
  if (context == nullptr) {
    description_ = SDL_GetError();
    is_error_ = true;
    return false;
  }
  return true;
}
bool Error::IsGlewSuccess(const GLenum flag) {
  if (flag != GLEW_OK) {
    description_ = reinterpret_cast<const char*>(glewGetErrorString(flag));
    is_error_ = true;
    return false;
  }
  return true;
}
#endif
