#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <string>
#include <vector>

namespace EngineS {

class WindowSystem {
  public:
	static WindowSystem* Instance();

	WindowSystem() = default;
	~WindowSystem();

	void				 Initialize(int width, int height, const char* title);
	void				 PollEvents() const;
	bool				 ShouldClose() const;
	void				 SetTitle(const std::string& title);
	GLFWwindow*			 GetWindow() const { return _window; }
	std::tuple<int, int> GetWindowSize() const { return {_width, _height}; }

	using OnResetFunc		= std::function<void()>;
	using OnKeyFunc			= std::function<void(int, int, int, int)>;
	using OnCharFunc		= std::function<void(unsigned int)>;
	using OnCharModsFunc	= std::function<void(int, unsigned int)>;
	using OnMouseButtonFunc = std::function<void(int, int, int)>;
	using OnCursorEnterFunc = std::function<void(int)>;
	using OnCursorPosFunc	= std::function<void(double, double)>;
	using OnScrollFunc		= std::function<void(double, double)>;
	using OnDropFunc		= std::function<void(int, const char**)>;
	using OnWindowSizeFunc	= std::function<void(int, int)>;
	using OnWindowCloseFunc = std::function<void()>;

	void RegisterOnResetFunc(OnResetFunc func) { _onResetFuncs.push_back(func); }
	void RegisterOnKeyFunc(OnKeyFunc func) { _onKeyFuncs.push_back(func); }
	void RegisterOnCharFunc(OnCharFunc func) { _onCharFuncs.push_back(func); }
	void RegisterOnCharModsFunc(OnCharModsFunc func) { _onCharModsFuncs.push_back(func); }
	void RegisterOnMouseButtonFunc(OnMouseButtonFunc func) { _onMouseButtonFuncs.push_back(func); }
	void RegisterOnCursorPosFunc(OnCursorPosFunc func) { _onCursorPosFuncs.push_back(func); }
	void RegisterOnCursorEnterFunc(OnCursorEnterFunc func) { _onCursorEnterFuncs.push_back(func); }
	void RegisterOnScrollFunc(OnScrollFunc func) { _onScrollFuncs.push_back(func); }
	void RegisterOnDropFunc(OnDropFunc func) { _onDropFuncs.push_back(func); }
	void RegisterOnWindowSizeFunc(OnWindowSizeFunc func) { _onWindowSizeFuncs.push_back(func); }
	void RegisterOnWindowCloseFunc(OnWindowCloseFunc func) { _onWindowCloseFuncs.push_back(func); }

  private:
	void OnReset() {
		for (auto& func : _onResetFuncs) func();
	}

	void OnKey(int key, int scanCode, int action, int mods) {
		for (auto& func : _onKeyFuncs) func(key, scanCode, action, mods);
	}

	void OnChar(unsigned int codePoint) {
		for (auto& func : _onCharFuncs) func(codePoint);
	}

	void OnCharMods(int codePoint, unsigned int mods) {
		for (auto& func : _onCharModsFuncs) func(codePoint, mods);
	}

	void OnMouseButton(int button, int action, int mods) {
		for (auto& func : _onMouseButtonFuncs) func(button, action, mods);
	}

	void OnCursorPos(double xPos, double yPos) {
		for (auto& func : _onCursorPosFuncs) func(xPos, yPos);
	}

	void OnCursorEnter(int entered) {
		for (auto& func : _onCursorEnterFuncs) func(entered);
	}

	void OnScroll(double xOffset, double yOffset) {
		for (auto& func : _onScrollFuncs) func(xOffset, yOffset);
	}

	void OnDrop(int count, const char** paths) {
		for (auto& func : _onDropFuncs) func(count, paths);
	}

	void OnWindowSize(int width, int height) {
		_width	= width;
		_height = height;
		for (auto& func : _onWindowSizeFuncs) func(width, height);
	}

	void OnWindowClose() {
		for (auto& func : _onWindowCloseFuncs) func();
	}

  private:
	GLFWwindow* _window {nullptr};
	int			_width {0};
	int			_height {0};

	std::vector<OnResetFunc>	   _onResetFuncs;
	std::vector<OnKeyFunc>		   _onKeyFuncs;
	std::vector<OnCharFunc>		   _onCharFuncs;
	std::vector<OnCharModsFunc>	   _onCharModsFuncs;
	std::vector<OnMouseButtonFunc> _onMouseButtonFuncs;
	std::vector<OnCursorEnterFunc> _onCursorEnterFuncs;
	std::vector<OnCursorPosFunc>   _onCursorPosFuncs;
	std::vector<OnScrollFunc>	   _onScrollFuncs;
	std::vector<OnDropFunc>		   _onDropFuncs;
	std::vector<OnWindowSizeFunc>  _onWindowSizeFuncs;
	std::vector<OnWindowCloseFunc> _onWindowCloseFuncs;
};

} // namespace EngineS