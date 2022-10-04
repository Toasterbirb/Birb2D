#include "Input.hpp"
#include "Math.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	namespace Input
	{
		KeyCode EventToKeycode(const SDL_Event& event)
		{
			/* Skip events that don't have anything to do with
			 * keyboard input */
			if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP)
				return NOT_RECOGNIZED;

			KeyCode code;

			switch (event.key.keysym.scancode)
			{
				case (SDL_SCANCODE_0):
					return NUM_0;

				case (SDL_SCANCODE_1):
					return NUM_1;

				case (SDL_SCANCODE_2):
					return NUM_2;

				case (SDL_SCANCODE_3):
					return NUM_3;

				case (SDL_SCANCODE_4):
					return NUM_4;

				case (SDL_SCANCODE_5):
					return NUM_5;

				case (SDL_SCANCODE_6):
					return NUM_6;

				case (SDL_SCANCODE_7):
					return NUM_7;

				case (SDL_SCANCODE_8):
					return NUM_8;

				case (SDL_SCANCODE_9):
					return NUM_9;

				case (SDL_SCANCODE_A):
					return A;

				case (SDL_SCANCODE_B):
					return B;

				case (SDL_SCANCODE_C):
					return C;

				case (SDL_SCANCODE_D):
					return D;

				case (SDL_SCANCODE_E):
					return E;

				case (SDL_SCANCODE_F):
					return F;

				case (SDL_SCANCODE_G):
					return G;

				case (SDL_SCANCODE_H):
					return H;

				case (SDL_SCANCODE_I):
					return I;

				case (SDL_SCANCODE_J):
					return J;

				case (SDL_SCANCODE_K):
					return K;

				case (SDL_SCANCODE_L):
					return L;

				case (SDL_SCANCODE_M):
					return M;

				case (SDL_SCANCODE_N):
					return N;

				case (SDL_SCANCODE_O):
					return O;

				case (SDL_SCANCODE_P):
					return P;

				case (SDL_SCANCODE_Q):
					return Q;

				case (SDL_SCANCODE_R):
					return R;

				case (SDL_SCANCODE_S):
					return S;

				case (SDL_SCANCODE_T):
					return T;

				case (SDL_SCANCODE_U):
					return U;

				case (SDL_SCANCODE_V):
					return V;

				case (SDL_SCANCODE_W):
					return W;

				case (SDL_SCANCODE_X):
					return X;

				case (SDL_SCANCODE_Y):
					return Y;

				case (SDL_SCANCODE_Z):
					return Z;

				case (SDL_SCANCODE_BACKSPACE):
					return BACKSPACE;

				case (SDL_SCANCODE_CAPSLOCK):
					return CAPS_LOCK;

				case (SDL_SCANCODE_CUT):
					return CUT;

				case (SDL_SCANCODE_PASTE):
					return PASTE;

				case (SDL_SCANCODE_DELETE):
					return DELETE_KEY;

				case (SDL_SCANCODE_UP):
					return ARROW_UP;

				case (SDL_SCANCODE_DOWN):
					return ARROW_DOWN;

				case (SDL_SCANCODE_LEFT):
					return ARROW_LEFT;

				case (SDL_SCANCODE_RIGHT):
					return ARROW_RIGHT;

				case (SDL_SCANCODE_END):
					return END;

				case (SDL_SCANCODE_EQUALS):
					return EQUALS;

				case (SDL_SCANCODE_ESCAPE):
					return ESCAPE;

				case (SDL_SCANCODE_F1):
					return F1;

				case (SDL_SCANCODE_F2):
					return F2;

				case (SDL_SCANCODE_F3):
					return F3;

				case (SDL_SCANCODE_F4):
					return F4;

				case (SDL_SCANCODE_F5):
					return F5;

				case (SDL_SCANCODE_F6):
					return F6;

				case (SDL_SCANCODE_F7):
					return F7;

				case (SDL_SCANCODE_F8):
					return F8;

				case (SDL_SCANCODE_F9):
					return F9;

				case (SDL_SCANCODE_F10):
					return F10;

				case (SDL_SCANCODE_F11):
					return F11;

				case (SDL_SCANCODE_F12):
					return F12;

				case (SDL_SCANCODE_F13):
					return F13;

				case (SDL_SCANCODE_F14):
					return F14;

				case (SDL_SCANCODE_F15):
					return F15;

				case (SDL_SCANCODE_F16):
					return F16;

				case (SDL_SCANCODE_F17):
					return F17;

				case (SDL_SCANCODE_F18):
					return F18;

				case (SDL_SCANCODE_F19):
					return F19;

				case (SDL_SCANCODE_F20):
					return F20;

				case (SDL_SCANCODE_F21):
					return F21;

				case (SDL_SCANCODE_F22):
					return F22;

				case (SDL_SCANCODE_F23):
					return F23;

				case (SDL_SCANCODE_F24):
					return F24;

				case (SDL_SCANCODE_HOME):
					return HOME;

				case (SDL_SCANCODE_KP_1):
					return KP_1;

				case (SDL_SCANCODE_KP_2):
					return KP_2;

				case (SDL_SCANCODE_KP_3):
					return KP_3;

				case (SDL_SCANCODE_KP_4):
					return KP_4;

				case (SDL_SCANCODE_KP_5):
					return KP_5;

				case (SDL_SCANCODE_KP_6):
					return KP_6;

				case (SDL_SCANCODE_KP_7):
					return KP_7;

				case (SDL_SCANCODE_KP_8):
					return KP_8;

				case (SDL_SCANCODE_KP_9):
					return KP_9;

				case (SDL_SCANCODE_KP_0):
					return KP_0;

				case (SDL_SCANCODE_LALT):
					return ALT_LEFT;

				case (SDL_SCANCODE_RALT):
					return ALT_RIGHT;

				case (SDL_SCANCODE_LCTRL):
					return CTRL_LEFT;

				case (SDL_SCANCODE_RCTRL):
					return CTRL_RIGHT;

				case (SDL_SCANCODE_LSHIFT):
					return SHIFT_LEFT;

				case (SDL_SCANCODE_RSHIFT):
					return SHIFT_RIGHT;

				case (SDL_SCANCODE_PAGEDOWN):
					return PAGE_DOWN;

				case (SDL_SCANCODE_PAGEUP):
					return PAGE_UP;

				case (SDL_SCANCODE_PRINTSCREEN):
					return PRINT_SCREEN;

				case (SDL_SCANCODE_RETURN):
					return RETURN;

				case (SDL_SCANCODE_SEMICOLON):
					return SEMICOLON;

				case (SDL_SCANCODE_SLASH):
					return SLASH;

				case (SDL_SCANCODE_SPACE):
					return SPACE;

				case (SDL_SCANCODE_TAB):
					return TAB;

				default:
					break;
			}

			switch (event.key.keysym.mod)
			{
				case (SDLK_AMPERSAND):
					return AMPERSAND;

				case (SDLK_ASTERISK):
					return ASTERISK;

				case (SDLK_AT):
					return AT;

				case (SDLK_CARET):
					return CARET;

				case (SDLK_DOLLAR):
					return DOLLAR;

				case (SDLK_EXCLAIM):
					return EXCLAIM;

				case (SDLK_GREATER):
					return GREATER_THAN;

				case (SDLK_LESS):
					return LESS_THAN;

				case (SDLK_HASH):
					return HASH;

				case (SDLK_LEFTPAREN):
					return LEFT_PAREN;

				case (SDLK_RIGHTPAREN):
					return RIGHT_PAREN;

				case (SDLK_PERCENT):
					return PERCENT;

				case (SDLK_PLUS):
					return PLUS;

				case (SDLK_QUESTION):
					return QUESTION;

				case (SDLK_QUOTE):
					return QUOTE;

				case (SDLK_UNDERSCORE):
					return UNDERSCORE;

				default:
					return NOT_RECOGNIZED;
			}

			return code;
		}

		MouseDrag::MouseDrag()
		{
			m_dragging = false;
		}

		void MouseDrag::Poll(const SDL_Event& event)
		{
			if (m_dragging)
			{
				/* Update the current end position */
				SDL_GetMouseState(&m_endPos.x, &m_endPos.y);

				/* If we are already dragging, stop dragging if there's a mouseup event */
				if (event.type == SDL_MOUSEBUTTONUP)
					m_dragging = false;
			}
			/* Start drag if not dragging and there's mousedown event */
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&m_startPos.x, &m_startPos.y);
				m_endPos = m_startPos;
				m_dragging = true;
			}
		}

		bool MouseDrag::isDragging() const
		{
			return m_dragging;
		}

		Vector2int MouseDrag::startPos() const
		{
			return m_startPos;
		}

		Vector2int MouseDrag::endPos() const
		{
			return m_endPos;
		}

		float MouseDrag::distance() const
		{
			return Math::VectorDistance(m_startPos, m_endPos);
		}
	}
}
