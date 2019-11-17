#pragma once

#include <utility>
#include <string>
#include <vector>
#include <Uniform.h>
#include <Shader.h>

class Program;
class Window;
class Scene;

/*
    The Renderer controls the window, performs
    once-per-frame actions such as clearing the window before rendering,
    and updating the window after rendering.
*/
class Renderer
{
private:
    Window* window;
    Program* geometryProgram;
    Program* lightingProgram;

    UniformMat4f projection;
    UniformMat4f model;

public:
    Renderer(Window* window, const std::vector<std::pair<std::string, Shader::Type>> geometryShaders/*, const std::vector<std::pair<std::string, Shader::Type>> lightingShaders*/);
    ~Renderer();

    bool windowClosed() const;
    void render(Scene* scene);

    void setProjection(float fov, float aspectratio, float near, float far);
};