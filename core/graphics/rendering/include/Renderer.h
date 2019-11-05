#pragma once

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

public:
    Renderer(Window* window, Program* geometryProgram, Program* lightingProgram);
    ~Renderer();

    bool windowClosed() const;
    void render(Scene* scene);
};