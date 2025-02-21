#include <ZimEngine/Graphics/OShaderProgram.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <iostream>

OShaderProgram::OShaderProgram(const OShaderProgramDesc& desc)
{
    m_programId = glCreateProgram();
    attach(desc.vertexShaderFilePath, VertexShader);
    attach(desc.fragmentShaderFilePath, FragmentShader);
    link();
}
OShaderProgram::~OShaderProgram()
{
    for (ui32 i = 0; i < 2; i++)
    {
        glDetachShader(m_programId, m_attachedShaders[i]);
        glDeleteShader(m_attachedShaders[i]);
    }
    glDeleteProgram(m_programId);
}

void OShaderProgram::attach(const wchar_t* shaderFilePath, const OShaderType& type)
{
    std::string shaderCode;

    std::ifstream shaderStream(shaderFilePath);
    //std::wcout << std::wstring(shaderFilePath);

    std::wstringstream sstr;
    sstr << shaderStream.rdbuf(); // Read entire file content into stringstream
    std::wstring text = sstr.str(); // Convert stream to string
    
    std::wcout << L"Shader File Content:\n" << text << std::endl;

    if (shaderStream.is_open()) //shaderStream.is_open() returns false
    {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    }
    else {
        return;
    }

    ui32 shaderId = 0;
    if (type == VertexShader) shaderId = glCreateShader(GL_VERTEX_SHADER);
    else if (type == FragmentShader) shaderId = glCreateShader(GL_FRAGMENT_SHADER);

    auto sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL);
    glCompileShader(shaderId);
    checkShaderCompilation(shaderId);

    glAttachShader(m_programId, shaderId);
    m_attachedShaders[type] = shaderId;
}

void OShaderProgram::link()
{
    glLinkProgram(m_programId);
}

ui32 OShaderProgram::getId()
{
    return m_programId;   
}

void OShaderProgram::checkShaderCompilation(ui32 shaderId) {
    int success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cerr << "Shader Compilation Failed: " << infoLog << std::endl;
    }
}