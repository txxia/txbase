#pragma once

#include "txbase/fwddecl.h"
#include "txbase/opengl/input.h"

namespace TX {
	namespace UI {
		class Application {
		public:
			struct AppConfig {
				std::string title;
				Vec2i windowSize = Vec2i(800, 600);
				bool fullscreen = false;
				bool resizable = true;
				float fps = 60;
			};
		public:
			Application();
			~Application();
			void Run();

		protected:
			/// <summary>
			/// Called before main loop.
			/// </summary>
			virtual void Start() {}
			/// <summary>
			/// Rendering loop, returns true if need update.
			/// </summary>
			virtual bool Render() { return false; }

			virtual void OnKey(KeyCode code, KeyState state, Modifiers modifiers) {}
			virtual void OnText(uint32_t code, Modifiers modifiers) {}
			virtual void OnMouseMove(float x, float y) {}
			virtual void OnMouseScroll(float vx, float vy) {}
			virtual void OnMouseButton(MouseButton button, MouseButtonState state, Modifiers mods) {}
			virtual void OnResize() {}
			virtual void OnWindowResize(int w, int h) {}
			virtual void OnWindowFocusChanged(bool focused) {}
			virtual void OnWindowPos(int x, int y) {}
			virtual void OnWindowMinimize() {}
			virtual void OnExit() {}

		protected:
			static const char * GetVersion();
			GLFWwindow *		GetWindow();
			MouseButtonState	Get(MouseButton button);
			bool				Get(KeyCode code);
			float				GetTime();
			float				GetDeltaTime();
			float				GetFrameRate();
			void				GetCursorPos(float *x, float *y);
// 			void				Refresh();
			bool				IsWindowVisible();
			void				Exit();
		private:
			static Application * This(GLFWwindow *window);
			static void GLFWKey(GLFWwindow *window, int key, int scancode, int action, int mods);
			static void GLFWChar(GLFWwindow *window, uint32_t codepoint);
// 			static void GLFWCharMods(GLFWwindow *window, uint32_t codepoint, int mods);
			static void GLFWCursorPos(GLFWwindow *window, double x, double y);
			static void GLFWMouseButton(GLFWwindow *window, int b, int s, int mods);
			static void GLFWMouseScroll(GLFWwindow *window, double xoff, double yoff);
			static void GLFWFramebufferSize(GLFWwindow *window, int w, int h);
			static void GLFWWindowSize(GLFWwindow *window, int w, int h);
			static void GLFWWindowFocus(GLFWwindow *window, int focused);
			static void GLFWWindowPos(GLFWwindow *window, int x, int y);
			static void GLFWWindowIconify(GLFWwindow *window, int iconified);
			static void GLFWError(int error, const char* desc);

			void FrameStart();
			void FrameEnd();
		protected:
			AppConfig config;
		private:
			GLFWwindow *window;
			float frameStart;
			float frameEnd;
			float deltaTime;
			float fps;
		};

		class InputHandledApplication : public Application {
		protected:
			void Start() {
				input.SetWindowSize(config.windowSize.x, config.windowSize.y);
			}
		protected:
			void OnKey(KeyCode code, KeyState state, Modifiers modifiers) {
				input.SetKeyCode(code, state);
				input.AddModifiers(modifiers);
			}
			void OnText(uint32_t code, Modifiers modifiers) {
				input.SetText(code);
				input.AddModifiers(modifiers);
			}
			void OnMouseMove(float x, float y) {
				input.SetCursor(x, y);
			}
			void OnMouseScroll(float vx, float vy) {
				input.scroll = vy;
			}
			void OnMouseButton(MouseButton button, MouseButtonState state, Modifiers mods) {
				input.SetButton(button, state);
				input.AddModifiers(mods);
			}
			void OnResize() {
				input.SetWindowSize(config.windowSize.x, config.windowSize.y);
			}
			//virtual void OnWindowResize(int w, int h) {}
			//virtual void OnWindowFocusChanged(bool focused) {}
			//virtual void OnWindowPos(int x, int y) {}
			//virtual void OnWindowMinimize() {}
		protected:
			Input input;
		};
	}
}
