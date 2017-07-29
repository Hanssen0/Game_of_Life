#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <iostream>
#include "Window.h"
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
  SDL_Window* main_window2 = nullptr;
  SDL_GLContext main_context2;
  Init();
  main_window = SDL_CreateWindow("My First OpenGL Program",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                kScreenWidth,
                                kScreenHeight,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
  main_context = SDL_GL_CreateContext(main_window);
  glewInit();
  const GLchar* vertex_shader_source = {
    "#version 330 core\nlayout(location=0)in vec3 position;layout(location=1)in vec3 mycolor;uniform float pos;out vec3 outcolor;void main(){gl_Position=vec4(position.x+pos,position.y,position.z,1.0);outcolor=mycolor;}"
  };
  const GLchar* fragment_shader_source = {
    "#version 330 core\nin vec3 outcolor;out vec4 color;void main(){color=vec4(outcolor,1.f);}"
  };
  HHShader main_shader;
  main_shader.Init(vertex_shader_source, fragment_shader_source, 1);
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  GLfloat verteces[] {
    -0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f,
    0.f, 0.5f, 0.f, 0.f, 1.f, 0.f,
    0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f
  };
  GLuint indices[] {
    0, 1, 2,
  };
  GLuint vbo;
  GLuint ebo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verteces), verteces, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  main_shader.Use();
  glClearColor(1.f, 1.f, 1.f, 1.f);
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
          break;
      }
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    SDL_GL_SwapWindow(main_window);
    SDL_GL_SwapWindow(main_window2);
  }
  glBindVertexArray(0);
  SDL_DestroyWindow(main_window);
  SDL_DestroyWindow(main_window2);
  Quit();
  return 0;
}
