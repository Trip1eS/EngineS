#include "Render/OpenGL/RenderDeviceOpenGL.hpp"
#include "Render/OpenGL/BufferOpenGL.hpp"
#include "Render/OpenGL/DrawListOpenGL.hpp"
#include "Render/OpenGL/FramebufferOpenGL.hpp"
#include "Render/OpenGL/ProgramOpenGL.hpp"
#include "Render/OpenGL/RenderPipelineOpenGL.hpp"
#include "Render/OpenGL/ShaderOpenGL.hpp"
#include "Render/OpenGL/Texture2DOpenGL.hpp"

#include <GLFW/glfw3.h>

namespace EngineS {

RenderDeviceOpenGL::RenderDeviceOpenGL() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        Logger::Error("Failed to initialize GLAD");
        return;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

RenderDeviceOpenGL::~RenderDeviceOpenGL() = default;

Shader* RenderDeviceOpenGL::CreateShader() {
    return new ShaderOpenGL();
}

const Type* RenderDeviceOpenGL::GetShaderType() {
    return TypeOf<ShaderOpenGL>();
}

Program* RenderDeviceOpenGL::CreateProgram() {
    return new ProgramOpenGL();
}

const Type* RenderDeviceOpenGL::GetProgramType() {
    return TypeOf<ProgramOpenGL>();
}

Buffer* RenderDeviceOpenGL::CreateBuffer(std::size_t size, BufferType type, BufferUsage usage) {
    return new BufferOpenGL(size, type, usage);
}

const Type* RenderDeviceOpenGL::GetBufferType() {
    return TypeOf<BufferOpenGL>();
}

Texture2D* RenderDeviceOpenGL::CreateTexture2D() {
    return new Texture2DOpenGL();
}

const Type* RenderDeviceOpenGL::GetTexture2DType() {
    return TypeOf<Texture2DOpenGL>();
}

DrawList* RenderDeviceOpenGL::CreateDrawList() {
    return new DrawListOpenGL();
}

const Type* RenderDeviceOpenGL::GetDrawListType() {
    return TypeOf<DrawListOpenGL>();
}

RenderPipeline* RenderDeviceOpenGL::CreateRenderPipeline(const RenderPipelineDescriptor& desc) {
    return new RenderPipelineOpenGL(desc);
}

const Type* RenderDeviceOpenGL::GetRenderPipelineType() {
    return TypeOf<RenderPipelineOpenGL>();
}

Framebuffer* RenderDeviceOpenGL::CreateFramebuffer(const FramebufferDescriptor& desc) {
    return new FramebufferOpenGL(desc);
}

const Type* RenderDeviceOpenGL::GetFramebufferType() {
    return TypeOf<FramebufferOpenGL>();
}

} // namespace EngineS