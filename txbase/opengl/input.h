#pragma once

#include "txbase/fwddecl.h"
#include "txbase/math/vector.h"
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace TX{ namespace UI{
	enum class MouseButton {
		NONE = -1,
		LEFT = GLFW_MOUSE_BUTTON_LEFT,
		MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
		RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
	};
	enum class MouseButtonState{
		DOWN = GLFW_PRESS,
		UP = GLFW_RELEASE
	};
	struct Modifiers{
		int value;
		enum Mod {
			SHIFT = GLFW_MOD_SHIFT,
			CTRL = GLFW_MOD_CONTROL,
			ALT = GLFW_MOD_ALT,
			SUPER = GLFW_MOD_SUPER
		};
		Modifiers(int mods=0) : value(mods){}
		bool operator () (int mods){ return (value & mods) == mods; }
		Modifiers operator | (const Modifiers& ot){ return value | ot.value; }
		void operator |= (const Modifiers& ot){ value |= ot.value; }
	};
	enum class KeyCode{
		NONE = GLFW_KEY_UNKNOWN,
		SPACE = GLFW_KEY_SPACE,
		APOSTROPHE = GLFW_KEY_APOSTROPHE,
		COMMA = GLFW_KEY_COMMA,
		MINUS = GLFW_KEY_MINUS,
		PERIOD = GLFW_KEY_PERIOD,
		SLASH = GLFW_KEY_SLASH,
		N_0 = GLFW_KEY_0,
		N_1 = GLFW_KEY_1,
		N_2 = GLFW_KEY_2,
		N_3 = GLFW_KEY_3,
		N_4 = GLFW_KEY_4,
		N_5 = GLFW_KEY_5,
		N_6 = GLFW_KEY_6,
		N_7 = GLFW_KEY_7,
		N_8 = GLFW_KEY_8,
		N_9 = GLFW_KEY_9,
		SEMICOLON = GLFW_KEY_SEMICOLON,
		EQUAL = GLFW_KEY_EQUAL,
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,
		LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
		BACKSLASH = GLFW_KEY_BACKSLASH,
		RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
		GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
		WORLD_1 = GLFW_KEY_WORLD_1,
		WORLD_2 = GLFW_KEY_WORLD_2,
		ESCAPE = GLFW_KEY_ESCAPE,
		ENTER = GLFW_KEY_ENTER,
		TAB = GLFW_KEY_TAB,
		BACKSPACE = GLFW_KEY_BACKSPACE,
		INSERT = GLFW_KEY_INSERT,
		DEL = GLFW_KEY_DELETE,
		RIGHT = GLFW_KEY_RIGHT,
		LEFT = GLFW_KEY_LEFT,
		DOWN = GLFW_KEY_DOWN,
		UP = GLFW_KEY_UP,
		PAGE_UP = GLFW_KEY_PAGE_UP,
		PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
		HOME = GLFW_KEY_HOME,
		END = GLFW_KEY_END,
		CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
		SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
		NUM_LOCK = GLFW_KEY_NUM_LOCK,
		PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
		PAUSE = GLFW_KEY_PAUSE,
		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,
		F13 = GLFW_KEY_F13,
		F14 = GLFW_KEY_F14,
		F15 = GLFW_KEY_F15,
		F16 = GLFW_KEY_F16,
		F17 = GLFW_KEY_F17,
		F18 = GLFW_KEY_F18,
		F19 = GLFW_KEY_F19,
		F20 = GLFW_KEY_F20,
		F21 = GLFW_KEY_F21,
		F22 = GLFW_KEY_F22,
		F23 = GLFW_KEY_F23,
		F24 = GLFW_KEY_F24,
		F25 = GLFW_KEY_F25,
		KP_0 = GLFW_KEY_KP_0,
		KP_1 = GLFW_KEY_KP_1,
		KP_2 = GLFW_KEY_KP_2,
		KP_3 = GLFW_KEY_KP_3,
		KP_4 = GLFW_KEY_KP_4,
		KP_5 = GLFW_KEY_KP_5,
		KP_6 = GLFW_KEY_KP_6,
		KP_7 = GLFW_KEY_KP_7,
		KP_8 = GLFW_KEY_KP_8,
		KP_9 = GLFW_KEY_KP_9,
		KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
		KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
		KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
		KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
		KP_ADD = GLFW_KEY_KP_ADD,
		KP_ENTER = GLFW_KEY_KP_ENTER,
		KP_EQUAL = GLFW_KEY_KP_EQUAL,
		LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
		LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
		LEFT_ALT = GLFW_KEY_LEFT_ALT,
		LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
		RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
		RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
		RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
		RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
		MENU = GLFW_KEY_MENU,
		LAST = GLFW_KEY_LAST
	};
	enum class KeyState {
		DOWN = GLFW_PRESS,
		UP = GLFW_RELEASE,
		HOLD = GLFW_REPEAT
	};
	struct Input {
		Vec2i windowSize;
		bool windowChanged;
		Vec2 cursor;
		Vec2 prevCursor;
		MouseButton button;
		MouseButtonState buttonState;
		float scroll;
		unsigned char text;
		KeyCode key;
		KeyState keyState;
		Modifiers mods;

		Input() {}

		inline bool operator ()(KeyCode k) { return key == k; }
		inline bool operator ()(KeyState s) { return keyState == s; }
		inline bool operator ()(KeyCode k, KeyState s) { return key == k && keyState == s; }
		inline bool operator ()(MouseButton bt) { return button == bt; }
		inline bool operator ()(MouseButtonState s) { return buttonState == s; }
		inline bool operator ()(MouseButton bt, MouseButtonState s) { return button == bt && buttonState == s; }

		inline bool HasText() const { return text != 0; }
		inline bool HasKeyCode() const { return key != KeyCode::NONE; }
		inline Vec2 GetCursorMovement() const { return cursor - prevCursor; }

		inline void Clear(){
			windowChanged = false;
			ClearButton();
			ClearScroll();
			ClearText();
			ClearKeyCode();
			ClearModifiers();
		}
		inline void SetWindowSize(int w, int h) {
			Vec2i newSize(w, h);
			if (windowSize != newSize) {
				windowChanged = true;
				windowSize = newSize;
			}
		}
		inline void SetCursor(float x, float y) { prevCursor = cursor; cursor.x = x, cursor.y = y; }
		inline void SetButton(MouseButton b, MouseButtonState s){ button = b; buttonState = s; }
		inline void SetText(unsigned char c){ if (!HasText()) text = c; }
		inline void SetKeyCode(KeyCode code, KeyState s){ key = code; keyState = s; }
		inline void AddModifiers(const Modifiers& newmods){ mods |= newmods; }

		inline void ClearButton() { button = MouseButton::NONE; buttonState = MouseButtonState(-1); }
		inline void ClearScroll() { scroll = 0.f; }
		inline void ClearText() { text = 0; }
		inline void ClearKeyCode() { key = KeyCode::NONE; keyState = KeyState(-1); }
		inline void ClearModifiers() { mods = 0; }
	};
}}
