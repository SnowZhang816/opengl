#include "Shader.h"
#include "iostream"
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

Shader::Shader(const char* vsPath, const char* fsPath)
{
    string vsCode;
    string fsCode;
    ifstream vsFile;
    ifstream fsFile;
    vsFile.exceptions(ifstream::failbit | ifstream::badbit);
    fsFile.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
        /* code */
        vsFile.open(vsPath);
        fsFile.open(fsPath);
        stringstream vsStream;
        stringstream fsStream;

        vsStream << vsFile.rdbuf();
        fsStream << fsFile.rdbuf();

        vsFile.close();
        fsFile.close();

        vsCode = vsStream.str();
        fsCode = fsStream.str();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    const char* vsStr = vsCode.c_str();
    const char* fsStr = fsCode.c_str();

    unsigned int vsShader;
    vsShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsShader, 1, &vsStr, NULL);
    glCompileShader(vsShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vsShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vsShader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    unsigned int fsShader;
    fsShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsShader, 1, &fsStr, NULL);
    glCompileShader(fsShader);
    glGetShaderiv(fsShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fsShader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    this->ID = glCreateProgram();
    glAttachShader(ID, vsShader);
    glAttachShader(ID, fsShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
}

Shader::~Shader(){
    glDeleteProgram(ID);
}

void Shader::use()
{
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
