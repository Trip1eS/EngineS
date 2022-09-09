#include "RenderSystem.hpp"

#include "Core/Base/Macros.hpp"
#include "Core/Math/MathHeaders.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Object/Component/Camera.hpp"
#include "Function/Object/Component/Transform2D.hpp"
#include "Function/Object/GameObject.hpp"
#include "Function/Render/Program.hpp"
#include "Function/Render/SpriteRenderer.hpp"
#include "Function/Render/Texture2D.hpp"
#include "Function/Render/WindowSystem.hpp"
#include "Function/Scene/SceneManager.hpp"

namespace EngineS {

void RenderSystem::PreWindowInitialize() {
	if (!glfwInit()) {
		LOG_FATAL("Failed to initialize GLFW");
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void RenderSystem::Initialize() {
	_window = Global::Instance()->windowSystem->GetWindow();

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		LOG_FATAL("Failed to initialize GLAD");
		return;
	}

	Global::Instance()->windowSystem->RegisterOnWindowSizeFunc([](int w, int h) { glViewport(0, 0, w, h); });

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto resourceManager = Global::Instance()->resourceManager;
	_programHandle		 = resourceManager->GetHandle<Program>("sprite.glsl");
	resourceManager->LoadResource(_programHandle);
	resourceManager->AddWatch(_programHandle);
}

void RenderSystem::Update() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	auto* scene	 = Global::Instance()->sceneManager->GetCurrentScene();
	auto* camera = scene->GetMainCamera();

	auto program = Global::Instance()->resourceManager->GetLoadedResource<Program>(_programHandle);
	program->Use();
	program->Set("image", 0);
	program->Set("projection", camera->GetProjectionMatrix());
	program->Set("view", camera->GetViewMatrix());

	for (auto& obj : scene->GetGameObjects()) {
		if (obj->renderer != nullptr) {
			static_cast<SpriteRenderer*>(obj->renderer)->_program = program;
			obj->renderer->Render();
		}
	}

	glfwSwapBuffers(_window);
}

} // namespace EngineS