#pragma once
#include <ZimEngine/OPrerequisites.h>
#include <ZimEngine/Math/OVec4.h>
#include <ZimEngine/Math/ORect.h>
#include <ZimEngine/Graphics/OVertexArrayObject.h>

class OGraphicsEngine
{
public:
    OGraphicsEngine();
    ~OGraphicsEngine();
public:
    OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferData& data);
public:
    void clear(const OVec4& color);
    void setViewport(const ORect& size);
    void setVertexArrayObject(const OVertexArrayObjectPtr& vao);
    void drawTriangles(ui32 vertexCount, ui32 offset);
};