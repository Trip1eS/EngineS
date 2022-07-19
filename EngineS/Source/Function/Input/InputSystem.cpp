#include "InputSystem.hpp"
#include "Core/Base/Macros.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Render/WindowSystem.hpp"

namespace EngineS {

void InputSystem::Initialize() {
#define KEY_CODE(name, code) _keys[KeyCode::name] = {};
#include "Function/Input/KeyCode.def"
#undef KEY_CODE
	Global::Instance()->windowSystem->RegisterOnKeyFunc(ENGINES_CALLBACK(OnKey));
}

void InputSystem::Update() {
	for (auto& key : _keys) {
		auto& state			= key.second;
		state.downLastFrame = state.downThisFrame;
	}
}

void InputSystem::OnKey(int key, int scanCode, int action, int mods) {
	auto  code			= static_cast<KeyCode>(key);
	auto& state			= _keys[code];
	state.downThisFrame = (action != GLFW_RELEASE);
}

bool InputSystem::GetKey(KeyCode key) {
	return _keys[key].downThisFrame;
}

bool InputSystem::GetKeyDown(KeyCode key) {
	auto& state = _keys[key];
	return state.downThisFrame && !state.downLastFrame;
}

bool InputSystem::GetKeyUp(KeyCode key) {
	auto& state = _keys[key];
	return !state.downThisFrame && state.downLastFrame;
}

} // namespace EngineS