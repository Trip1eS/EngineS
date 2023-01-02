#include "Function/GameObjectFactory.hpp"
#include "Function/Camera.hpp"
#include "Function/GameObject.hpp"
#include "Function/Transform2D.hpp"
#include "Render/Material2D.hpp"
#include "Render/Program.hpp"
#include "Render/RenderSystem.hpp"
#include "Render/SpriteRenderer.hpp"
#include "Render/Texture2D.hpp"
#include "Resource/ResourceManager.hpp"

namespace EngineS {

GameObject* GameObjectFactory::CreateGameObject() {
    auto obj = new GameObject();
    obj->AddComponent<Transform2D>();
    return obj;
}

GameObject* GameObjectFactory::CreateSprite(std::filesystem::path path) {
    auto obj      = CreateGameObject();
    auto texture  = ResourceManager::Instance()->Load<Texture2D>(path);
    auto program  = ResourceManager::Instance()->Load<Program>("sprite.glsl");
    auto material = new Material2D(program, texture);
    auto renderer = obj->AddComponent<SpriteRenderer>();
    renderer->SetMaterial(material);
    return obj;
}

GameObject* GameObjectFactory::CreateCamera() {
    auto obj = CreateGameObject();
    obj->AddComponent<Camera>();
    return obj;
}

} // namespace EngineS