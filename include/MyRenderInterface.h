#pragma once

#include <Rocket/Core/RenderInterface.h>

class MyRenderInterface : public Rocket::Core::RenderInterface
{
public:
    MyRenderInterface();
    virtual ~MyRenderInterface();

    virtual void RenderGeometry(Rocket::Core::Vertex *vertices, int num_vertices, int *indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f &translation) override;
    virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex *vertices, int num_vertices, int *indices, int num_indices, Rocket::Core::TextureHandle texture) override;
    virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f &translation) override;
    virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry) override;
    virtual void EnableScissorRegion(bool enable) override;
    virtual void SetScissorRegion(int x, int y, int width, int height) override;
    virtual bool LoadTexture(Rocket::Core::TextureHandle &texture_handle, Rocket::Core::Vector2i &texture_dimensions, const Rocket::Core::String &source) override;
    virtual bool GenerateTexture(Rocket::Core::TextureHandle &texture_handle, const Rocket::Core::byte *source, const Rocket::Core::Vector2i &source_dimensions) override;
    virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle) override;
    virtual float GetHorizontalTexelOffset() override;
    virtual float GetVerticalTexelOffset() override;
};
