#pragma once
#include <ZimEngine/OPrerequisites.h>

class OShaderProgram
{
public:
    OShaderProgram(const OShaderProgramDesc& desc);
    ~OShaderProgram();
    ui32 getId();

private:
    void attach(const wchar_t* shaderFilePath, const OShaderType& type);
    void link();
    void checkShaderCompilation(const ui32 shaderId);
private:
    ui32 m_programId = 0;
    ui32 m_attachedShaders[2] = {};
};