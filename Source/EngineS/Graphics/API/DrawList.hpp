#pragma once

#include "Core/Macros.hpp"
#include "Core/Math/Color.hpp"
#include "RenderTypes.hpp"

namespace EngineS {

class RenderPipeline;
class Buffer;
class Texture2D;
class Framebuffer;

struct RenderPassDescriptor {
    Framebuffer* framebuffer;
    bool         clearColor {false};
    Color4F      clearColorValue {0.f, 0.f, 0.f, 0.f};
    bool         clearDepth {false};
    float        clearDepthValue = 0.f;
};

class DrawList : public Object {
    ES_OBJECT
  public:
    virtual void Begin(const RenderPassDescriptor& desc)            = 0;
    virtual void SetViewport(i32 x, i32 y, u32 w, u32 h)            = 0;
    virtual void BindRenderPipeline(const RenderPipeline* pipeline) = 0;
    virtual void BindVertexBuffer(const Buffer* buffer)             = 0;
    virtual void BindTexture(const Texture2D* texture)              = 0;
    virtual void Draw(std::size_t start, std::size_t count)         = 0;
    virtual void End()                                              = 0;
};

} // namespace EngineS
