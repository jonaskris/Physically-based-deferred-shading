#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <glad/glad.h>
#include <Shader.h>

namespace graphics
{
    class Program
    {
    private:
        GLuint programId;
        bool linkedSuccessfully = false;
        bool validatedSuccessfully = false;

    public:
        Program(const std::vector<std::pair<std::string, Shader::Type>>& shaderPaths);

        GLuint getProgramId() const;
        bool getLinkedSuccessfully() const;
        bool getValidatedSuccessfully() const;

        void enable() const;
        void disable() const;

        friend std::ostream& operator<<(std::ostream& out, const Program& program);
    };
}