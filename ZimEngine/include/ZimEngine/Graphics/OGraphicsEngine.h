#pragma once
#include <ZimEngine/OPrerequisites.h>
#include <ZimEngine/Math/OVec4.h>
#include <ZimEngine/Math/ORect.h>
#include <ZimEngine/Graphics/OVertexArrayObject.h>
#include <ZimEngine/Graphics/OShaderProgram.h>

class OGraphicsEngine
{
public:
    OGraphicsEngine();
    ~OGraphicsEngine();
public:
    OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferData& data);
    OShaderProgramPtr createShaderProgram(const OShaderProgramDesc& desc);
public:
    void clear(const OVec4& color);
    void setViewport(const ORect& size);
    void setVertexArrayObject(const OVertexArrayObjectPtr& vao);
    void setShaderProgram(const OShaderProgramPtr& program);
    void drawTriangles(ui32 vertexCount, ui32 offset);
};