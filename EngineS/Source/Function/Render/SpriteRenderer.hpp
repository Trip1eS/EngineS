#pragma once

#include <memory>

#include "Core/Math/MathHeaders.hpp"
#include "Function/Object/Component/Component.hpp"
#include "Function/Render/Renderer.hpp"

namespace EngineS {

class Program;
class Texture2D;
class Transform2D;

class SpriteRenderer : public Renderer {
	friend class RenderSystem;

  public:
	SpriteRenderer(std::shared_ptr<Program> shader, std::shared_ptr<Texture2D> texture);

	virtual void Render() override;

	virtual void Initialize(GameObject* parent) override;

  private:
	std::shared_ptr<Program>   _program;
	std::shared_ptr<Texture2D> _texture;
	Vector3					   _color {Vector3::One};
	Vector2					   _anchor {0.5f, 0.5f};
	static unsigned int		   _vao;
};

} // namespace EngineS
