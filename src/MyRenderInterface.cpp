#include "MyRenderInterface.h"
#include <GL/glew.h>
#include <cstring>

MyRenderInterface::MyRenderInterface() {}
MyRenderInterface::~MyRenderInterface() {}

void MyRenderInterface::RenderGeometry(Rocket::Core::Vertex *vertices, int num_vertices, int *indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f &translation)
{
    glPushMatrix();
    glTranslatef(translation.x, translation.y, 0);

    if (texture)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, (GLuint)texture);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < num_indices; ++i)
    {
        const Rocket::Core::Vertex &vertex = vertices[indices[i]];
        glColor4ubv((GLubyte *)&vertex.colour);
        glTexCoord2f(vertex.tex_coord.x, vertex.tex_coord.y);
        glVertex2f(vertex.position.x, vertex.position.y);
    }
    glEnd();

    glPopMatrix();
}

Rocket::Core::CompiledGeometryHandle MyRenderInterface::CompileGeometry(Rocket::Core::Vertex *vertices, int num_vertices, int *indices, int num_indices, Rocket::Core::TextureHandle texture)
{
    return 0;
}

void MyRenderInterface::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f &translation)
{
    // Not implemented
}

void MyRenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
    // Not implemented
}

void MyRenderInterface::EnableScissorRegion(bool enable)
{
    if (enable)
        glEnable(GL_SCISSOR_TEST);
    else
        glDisable(GL_SCISSOR_TEST);
}

void MyRenderInterface::SetScissorRegion(int x, int y, int width, int height)
{
    glScissor(x, y, width, height);
}

bool MyRenderInterface::LoadTexture(Rocket::Core::TextureHandle &texture_handle, Rocket::Core::Vector2i &texture_dimensions, const Rocket::Core::String &source)
{
    // Simple dummy loader (does nothing)
    texture_handle = 0;
    texture_dimensions = Rocket::Core::Vector2i(0, 0);
    return false;
}

bool MyRenderInterface::GenerateTexture(Rocket::Core::TextureHandle &texture_handle, const Rocket::Core::byte *source, const Rocket::Core::Vector2i &source_dimensions)
{
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, source_dimensions.x, source_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texture_handle = (Rocket::Core::TextureHandle)texture_id;
    return true;
}

void MyRenderInterface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
    GLuint texture = (GLuint)texture_handle;
    glDeleteTextures(1, &texture);
}

float MyRenderInterface::GetHorizontalTexelOffset()
{
    return 0.0f;
}

float MyRenderInterface::GetVerticalTexelOffset()
{
    return 0.0f;
}
