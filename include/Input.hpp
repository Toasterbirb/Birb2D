#pragma once
#include "SDL.h"
#include "Vector/Vector2.hpp"
#include "Vector/Vector2Int.hpp"

namespace Birb
{
	namespace Input
	{
		enum KeyCode
		{
			NUM_0,
			NUM_1,
			NUM_2,
			NUM_3,
			NUM_4,
			NUM_5,
			NUM_6,
			NUM_7,
			NUM_8,
			NUM_9,
			A, B, C, D, E, F, G, H, I, J,
			K, L, M, N, O, P, Q, R, S, T,
			U, V, W, X, Y, Z,
			BACKSPACE,
			CAPS_LOCK,
			CUT,
			PASTE,
			DELETE_KEY,
			ARROW_DOWN, ARROW_UP, ARROW_LEFT, ARROW_RIGHT,
			END,
			EQUALS,
			ESCAPE,
			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
			F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
			HOME,
			KP_1, KP_2, KP_3, KP_4, KP_5,
			KP_6, KP_7, KP_8, KP_9, KP_0,
			ALT_LEFT, ALT_RIGHT,
			CTRL_LEFT, CTRL_RIGHT,
			SHIFT_LEFT, SHIFT_RIGHT,
			PAGE_DOWN, PAGE_UP,
			PRINT_SCREEN,
			RETURN,
			SEMICOLON,
			SLASH,
			SPACE,
			TAB,
			//AMPERSAND,
			//ASTERISK,
			//AT,
			//CARET,
			//DOLLAR,
			//EXCLAIM,
			//GREATER_THAN, LESS_THAN,
			//HASH,
			//LEFT_PAREN, RIGHT_PAREN,
			//PERCENT,
			//PLUS,
			//QUESTION,
			//QUOTE,
			//UNDERSCORE,
			NOT_RECOGNIZED
		};

		KeyCode EventToKeycode(const SDL_Event& event);
		Vector2 MovementDirection(const SDL_Event& event);

		/// A class used for tracking mouse dragging
		class MouseDrag
		{
		public:
			MouseDrag(); ///< Initialize a MouseDrag "listener"
			void 		Poll(const SDL_Event& event);
			bool 		isDragging() const;
			Vector2Int 	startPos() const; ///< Drag start position. Value gets cleared when new drag starts
			Vector2Int 	endPos() const; ///< Current drag end position. Value gets cleared when new drag starts
			float 		distance() const; ///< Distance between start and end positions
		private:
			bool 		m_dragging;
			Vector2Int 	m_startPos;
			Vector2Int 	m_endPos;
		};
	}
}
