#ifndef OPENGL_FRAMEWORK_WINDOW_H_
#define OPENGL_FRAMEWORK_WINDOW_H_
#include "GLHs.h" 
#include <vector>
#include "Error.h"
#include "SDL2/SDL.h"
static Error kError;
class HHShader {
 public:
  HHShader& operator=(HHShader&) = delete;
  ~HHShader() { glDeleteProgram(shader_); }
  const Error& Init(const char*, const char*, const std::size_t);
  void Use() { glUseProgram(shader_); }
  inline const Error& find(const char*, const std::size_t);
  inline const Error& SetUniform(const std::size_t, const int);
  inline const Error& SetUniformByName(const char*, const int);
  inline const Error& SetUniform(const std::size_t, const float);
  inline const Error& SetUniformByName(const char*, const float);
 private:
  GLuint shader_;
  std::vector<GLuint> uniform_location;
};
class HHWindow {
 public:
  HHWindow& operator=(HHWindow&) = delete;
  HHWindow() { window_ = nullptr, context_ = nullptr; }
  ~HHWindow() { SDL_DestroyWindow(window_); }
  inline const Error& Create(const char*, const int, const int, const int,
                             const int, const Uint32);
  void Swap() { SDL_GL_SwapWindow(window_); }
 private:
  SDL_Window* window_;
  SDL_GLContext context_;
  static bool is_glew_inited_;
};
class HHVAO {
 public:
  HHVAO() { glGenVertexArrays(1, &vao_); }
  ~HHVAO() { glDeleteVertexArrays(1, &vao_); }
  void Use() { glBindVertexArray(vao_); }
  static void Release() { glBindVertexArray(0); }
 private:
  GLuint vao_;
};
class HHBuffer {
 public:
  HHBuffer(const GLsizei size) : size_(size) { glGenBuffers(size, &buffer_); }
  ~HHBuffer() { glDeleteBuffers(size_, &buffer_); }
  void Bind(const GLenum target) { glBindBuffer(target, buffer_); }
 private:
  GLuint buffer_;
  GLsizei size_;
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
const Error& HHShader::SetUniform(const std::size_t location,
                                  const float value) {
  glUniform1f(uniform_location[location], value);
  kError.IsGLSuccess();
  return kError;
}
const Error& HHShader::SetUniformByName(const char* location,
                                        const float value) {
  glUniform1f(glGetUniformLocation(shader_, location), value);
  kError.IsGLSuccess();
  return kError;
}
const Error& HHWindow::Create(const char* title, const int x, const int y,
                              const int w, const int h, const Uint32 flag) {
  window_ = SDL_CreateWindow(title, x, y, w, h, flag);
  if (kError.IsSDLSuccess(window_) == false) return kError;
  context_ = SDL_GL_CreateContext(window_);
  if (kError.IsSDLSuccess(context_) == false) return kError;
  if (is_glew_inited_ == false) {
    if (kError.IsGlewSuccess(glewInit()) != false) is_glew_inited_ = true;
  }
  return kError;
}
#endif
