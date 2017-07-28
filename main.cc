#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <iostream>
const int kScreenWidth = 640;
const int kScreenHeight = 480;
void Init() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                      SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetSwapInterval(1);
  SDL_StartTextInput();
}
void Quit() {
  SDL_Quit();
  SDL_StopTextInput();
}
int main(int, char**) {
  SDL_Window* main_window = nullptr;
  SDL_GLContext main_context;
  Init();
  main_window = SDL_CreateWindow("My First OpenGL Program",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                kScreenWidth,
                                kScreenHeight,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
  main_context = SDL_GL_CreateContext(main_window);
  glewInit();
  GLuint vertex_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar* vertex_shader_source[] = {
    "#version 330 core\nlayout(location = 0)in vec3 position;void main(){gl_Position=vec4(position.x,position.y,position.z,1.0);}"
  };
  glShaderSource(vertex_shader, 1, vertex_shader_source, nullptr);
  glCompileShader(vertex_shader);
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar* fragment_shader_source[] = {
    "#version 330 core\nout vec4 color;void main(){color=vec4(1.0f,0.5f,0.2f,1.0f);}"
  };
  glShaderSource(fragment_shader, 1, fragment_shader_source, nullptr);
  glCompileShader(fragment_shader);
  GLuint fragment_shader_yellow = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar* fragment_shader_yellow_source[] = {
    "#version 330 core\nout vec4 color;void main(){color=vec4(1.0f,1.0f,0.f,1.0f);}"
  };
  glShaderSource(fragment_shader_yellow, 1, fragment_shader_yellow_source, nullptr);
  glCompileShader(fragment_shader_yellow);
  GLuint shader_program = glCreateProgram(), shader_program_yellow = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  glAttachShader(shader_program_yellow, vertex_shader);
  glAttachShader(shader_program_yellow, fragment_shader_yellow);
  glLinkProgram(shader_program_yellow);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  glDeleteShader(fragment_shader_yellow);
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  GLfloat verteces[] {
    -0.5f, -0.5f, 0.f,
    0.f, 0.5f, 0.f,
    0.5f, -0.5f, 0.f,
    1.f, 0.5f, 0.f
  };
  GLuint indices[] {
    0, 1, 2,
    1, 2, 3
  };
  GLuint vbo;
  GLuint ebo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verteces), verteces, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  SDL_Event main_event;
  bool is_end = false;
  float color = 0;
  while (is_end != true) {
    while (SDL_PollEvent(&main_event) == true) {
      switch (main_event.type) {
        case SDL_QUIT:
          is_end = true;
          break;
        case SDL_TEXTINPUT:
          if (main_event.text.text[0] == 'w') color += 0.01f;
          if (main_event.text.text[0] == 's') color -= 0.01f;
          glClearColor(color, color, color, 1.f);
          break;
      }
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader_program);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glUseProgram(shader_program_yellow);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(3 * sizeof(GLuint)));
    SDL_GL_SwapWindow(main_window);
  }
  glBindVertexArray(0);
  SDL_DestroyWindow(main_window);
  Quit();
  return 0;
}
