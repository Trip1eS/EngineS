#include "GameEngine.hpp"
#include "Core/Base/AutoReleasePool.hpp"
#include "Core/Base/Macros.hpp"
#include "Core/Base/PoolManager.hpp"
#include "Core/Logging/LoggingSystem.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Input/InputSystem.hpp"
#include "Function/Object/GameObject.hpp"
#include "Function/Render/RenderSystem.hpp"
#include "Function/Render/WindowSystem.hpp"
#include "Function/Scene/SceneManager.hpp"
#include "Resource/ResourceManager.hpp"

namespace EngineS {

static GameEngine* s_SharedInstance;

GameEngine* GameEngine::Instance() {
	if (!s_SharedInstance) {
		s_SharedInstance = new (std::nothrow) GameEngine;
		assert(s_SharedInstance != nullptr);
	}
	return s_SharedInstance;
}

int GameEngine::FPSCalculator::Calculate(float deltaTime) {
	frameCount++;
	if (frameCount == 1) {
		averageDuration = deltaTime;
	} else {
		averageDuration = averageDuration * (1 - fpsSmoothing) + deltaTime * fpsSmoothing;
	}
	fps = static_cast<int>(1.0f / averageDuration);
	return fps;
}

void GameEngine::StartEngine() {
	Global::Instance()->Initialize();
	LOG_INFO("Engine started");
}

void GameEngine::Shutdown() {
	LOG_INFO("Engine shutting down");
	_shouldShutdown = true;
}

void GameEngine::Run() {
	auto window = WindowSystem::Instance();
	while (!window->ShouldClose()) {
		const float deltaTime = GetDeltaTime();
		Update(deltaTime);

		if (_shouldShutdown) {
			Global::Instance()->Shutdown();
			break;
		}
	}
}

float GameEngine::GetDeltaTime() {
	float deltaTime;
	auto  nowTime  = std::chrono::steady_clock::now();
	auto  timeSpan = std::chrono::duration_cast<std::chrono::duration<float>>(nowTime - _lastTickTime);
	deltaTime	   = timeSpan.count();
	_lastTickTime  = nowTime;
	return deltaTime;
}

void GameEngine::Update(float deltaTime) {
	ResourceManager::Instance()->Update();
	InputSystem::Instance()->Update();
	WindowSystem::Instance()->PollEvents();

	LogicUpdate(deltaTime);
	for (auto& func : _updateFuncs) func(deltaTime);

	_fpsCalculator.Calculate(deltaTime);

	RenderUpdate();

	PoolManager::Instance()->GetCurrentPool()->Clear();
}

void GameEngine::LogicUpdate(float deltaTime) {
	const auto& objs = SceneManager::Instance()->GetCurrentScene()->GetGameObjects();
	for (auto& obj : objs) {
		obj->Update(deltaTime);
	}
}

void GameEngine::RenderUpdate() {
	RenderSystem::Instance()->Update();
}

} // namespace EngineS