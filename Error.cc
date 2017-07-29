#include <GL/glew.h>
#include "Error.h"
bool Error::IsGLSuccess() {
  GLenum error;
  const GLubyte* error_code;
  if ((error = glGetError()) != GL_NO_ERROR) {
    switch(error) {
      case GL_INVALID_ENUM:
        description_ = "Invalid Enum";
        break;
      case GL_INVALID_VALUE:
        description_ = "Invalid Value";
        break;
      case GL_INVALID_OPERATION:
        description_ = "Invalid Operation";
        break;
      case GL_STACK_OVERFLOW:
        description_ = "Stack Overflow";
        break;
      case GL_STACK_UNDERFLOW:
        description_ = "Stack Underflow";
        break;
      case GL_OUT_OF_MEMORY:
        description_ = "Out of Memory";
        break;
      case GL_TABLE_TOO_LARGE:
        description_ = "Table too Large";
        break;
      default:
        description_ = "Unknown Error";
        break;
    }
    is_error_ = false;
    return false;
  }
  return true;
}
