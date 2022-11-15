#include "Component.hpp"

#include "Function/Object/GameObject.hpp"

namespace EngineS {

void Component::Initialize(GameObject* parent) {
	gameObject = parent;
	transform  = gameObject->transform;
	renderer   = gameObject->renderer;
}

} // namespace EngineS