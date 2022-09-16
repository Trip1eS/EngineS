#pragma once

#include "Core/Base/Types.hpp"
#include "Core/Math/MathHeaders.hpp"
#include "Platform/GLCommon.hpp"

#include <array>
#include <memory>
#include <vector>

namespace EngineS {

class Program;
class Texture2D;
class Material2D;
class Transform2D;

class SpriteBatch {
  public:
	using Triangle = std::array<V2F_C4F_T2F, 3>;

	SpriteBatch(std::shared_ptr<Material2D> material);
	SpriteBatch(std::shared_ptr<Texture2D> texture, std::shared_ptr<Program> program);

	void Add(const Vector2& position, float rotation, const Vector2& scale);
	void Add(const Transform2D* transform);

	void Draw();

  private:
	std::shared_ptr<Texture2D> _texture;
	std::shared_ptr<Program>   _program;
	std::vector<Triangle>	   _triangles;

	GLuint _vao;
	GLuint _vbo;
};

} // namespace EngineS