#include "doctest.h"
#include "Input.hpp"

namespace Birb
{
	namespace Input
	{
		TEST_CASE("Converting SDL input events into understandable keycodes")
		{
			SDL_Event event;
			event.type = SDL_KEYDOWN;

			SUBCASE("Numbers")
			{
				SUBCASE("0")
				{
					event.key.keysym.scancode = SDL_SCANCODE_0;
					CHECK(EventToKeycode(event) == NUM_0);
				}

				SUBCASE("1")
				{
					event.key.keysym.scancode = SDL_SCANCODE_1;
					CHECK(EventToKeycode(event) == NUM_1);
				}

				SUBCASE("2")
				{
					event.key.keysym.scancode = SDL_SCANCODE_2;
					CHECK(EventToKeycode(event) == NUM_2);
				}

				SUBCASE("3")
				{
					event.key.keysym.scancode = SDL_SCANCODE_3;
					CHECK(EventToKeycode(event) == NUM_3);
				}

				SUBCASE("4")
				{
					event.key.keysym.scancode = SDL_SCANCODE_4;
					CHECK(EventToKeycode(event) == NUM_4);
				}

				SUBCASE("5")
				{
					event.key.keysym.scancode = SDL_SCANCODE_5;
					CHECK(EventToKeycode(event) == NUM_5);
				}

				SUBCASE("6")
				{
					event.key.keysym.scancode = SDL_SCANCODE_6;
					CHECK(EventToKeycode(event) == NUM_6);
				}

				SUBCASE("7")
				{
					event.key.keysym.scancode = SDL_SCANCODE_7;
					CHECK(EventToKeycode(event) == NUM_7);
				}

				SUBCASE("8")
				{
					event.key.keysym.scancode = SDL_SCANCODE_8;
					CHECK(EventToKeycode(event) == NUM_8);
				}

				SUBCASE("9")
				{
					event.key.keysym.scancode = SDL_SCANCODE_9;
					CHECK(EventToKeycode(event) == NUM_9);
				}
			}

			SUBCASE("Alphabet")
			{
				SUBCASE("A")
				{
					event.key.keysym.scancode = SDL_SCANCODE_A;
					CHECK(EventToKeycode(event) == A);
				}

				SUBCASE("B")
				{
					event.key.keysym.scancode = SDL_SCANCODE_B;
					CHECK(EventToKeycode(event) == B);
				}

				SUBCASE("C")
				{
					event.key.keysym.scancode = SDL_SCANCODE_C;
					CHECK(EventToKeycode(event) == C);
				}

				SUBCASE("D")
				{
					event.key.keysym.scancode = SDL_SCANCODE_D;
					CHECK(EventToKeycode(event) == D);
				}

				SUBCASE("E")
				{
					event.key.keysym.scancode = SDL_SCANCODE_E;
					CHECK(EventToKeycode(event) == E);
				}

				SUBCASE("F")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F;
					CHECK(EventToKeycode(event) == F);
				}

				SUBCASE("G")
				{
					event.key.keysym.scancode = SDL_SCANCODE_G;
					CHECK(EventToKeycode(event) == G);
				}

				SUBCASE("H")
				{
					event.key.keysym.scancode = SDL_SCANCODE_H;
					CHECK(EventToKeycode(event) == H);
				}

				SUBCASE("I")
				{
					event.key.keysym.scancode = SDL_SCANCODE_I;
					CHECK(EventToKeycode(event) == I);
				}

				SUBCASE("J")
				{
					event.key.keysym.scancode = SDL_SCANCODE_J;
					CHECK(EventToKeycode(event) == J);
				}

				SUBCASE("K")
				{
					event.key.keysym.scancode = SDL_SCANCODE_K;
					CHECK(EventToKeycode(event) == K);
				}

				SUBCASE("L")
				{
					event.key.keysym.scancode = SDL_SCANCODE_L;
					CHECK(EventToKeycode(event) == L);
				}

				SUBCASE("M")
				{
					event.key.keysym.scancode = SDL_SCANCODE_M;
					CHECK(EventToKeycode(event) == M);
				}

				SUBCASE("N")
				{
					event.key.keysym.scancode = SDL_SCANCODE_N;
					CHECK(EventToKeycode(event) == N);
				}

				SUBCASE("O")
				{
					event.key.keysym.scancode = SDL_SCANCODE_O;
					CHECK(EventToKeycode(event) == O);
				}

				SUBCASE("P")
				{
					event.key.keysym.scancode = SDL_SCANCODE_P;
					CHECK(EventToKeycode(event) == P);
				}

				SUBCASE("Q")
				{
					event.key.keysym.scancode = SDL_SCANCODE_Q;
					CHECK(EventToKeycode(event) == Q);
				}

				SUBCASE("R")
				{
					event.key.keysym.scancode = SDL_SCANCODE_R;
					CHECK(EventToKeycode(event) == R);
				}

				SUBCASE("S")
				{
					event.key.keysym.scancode = SDL_SCANCODE_S;
					CHECK(EventToKeycode(event) == S);
				}

				SUBCASE("T")
				{
					event.key.keysym.scancode = SDL_SCANCODE_T;
					CHECK(EventToKeycode(event) == T);
				}

				SUBCASE("U")
				{
					event.key.keysym.scancode = SDL_SCANCODE_U;
					CHECK(EventToKeycode(event) == U);
				}

				SUBCASE("V")
				{
					event.key.keysym.scancode = SDL_SCANCODE_V;
					CHECK(EventToKeycode(event) == V);
				}

				SUBCASE("W")
				{
					event.key.keysym.scancode = SDL_SCANCODE_W;
					CHECK(EventToKeycode(event) == W);
				}

				SUBCASE("X")
				{
					event.key.keysym.scancode = SDL_SCANCODE_X;
					CHECK(EventToKeycode(event) == X);
				}

				SUBCASE("Y")
				{
					event.key.keysym.scancode = SDL_SCANCODE_Y;
					CHECK(EventToKeycode(event) == Y);
				}

				SUBCASE("Z")
				{
					event.key.keysym.scancode = SDL_SCANCODE_Z;
					CHECK(EventToKeycode(event) == Z);
				}
			}

			SUBCASE("Backspace")
			{
				event.key.keysym.scancode = SDL_SCANCODE_BACKSPACE;
				CHECK(EventToKeycode(event) == BACKSPACE);
			}

			SUBCASE("Caps lock")
			{
				event.key.keysym.scancode = SDL_SCANCODE_CAPSLOCK;
				CHECK(EventToKeycode(event) == CAPS_LOCK);
			}

			SUBCASE("Cut")
			{
				event.key.keysym.scancode = SDL_SCANCODE_CUT;
				CHECK(EventToKeycode(event) == CUT);
			}

			SUBCASE("Paste")
			{
				event.key.keysym.scancode = SDL_SCANCODE_PASTE;
				CHECK(EventToKeycode(event) == PASTE);
			}

			SUBCASE("Delete")
			{
				event.key.keysym.scancode = SDL_SCANCODE_DELETE;
				CHECK(EventToKeycode(event) == DELETE_KEY);
			}

			SUBCASE("Up arrow")
			{
				event.key.keysym.scancode = SDL_SCANCODE_UP;
				CHECK(EventToKeycode(event) == ARROW_UP);
			}

			SUBCASE("Down arrow")
			{
				event.key.keysym.scancode = SDL_SCANCODE_DOWN;
				CHECK(EventToKeycode(event) == ARROW_DOWN);
			}

			SUBCASE("Left arrow")
			{
				event.key.keysym.scancode = SDL_SCANCODE_LEFT;
				CHECK(EventToKeycode(event) == ARROW_LEFT);
			}

			SUBCASE("Right arrow")
			{
				event.key.keysym.scancode = SDL_SCANCODE_RIGHT;
				CHECK(EventToKeycode(event) == ARROW_RIGHT);
			}

			SUBCASE("End")
			{
				event.key.keysym.scancode = SDL_SCANCODE_END;
				CHECK(EventToKeycode(event) == END);
			}

			SUBCASE("Equals")
			{
				event.key.keysym.scancode = SDL_SCANCODE_EQUALS;
				CHECK(EventToKeycode(event) == EQUALS);
			}

			SUBCASE("Escape")
			{
				event.key.keysym.scancode = SDL_SCANCODE_ESCAPE;
				CHECK(EventToKeycode(event) == ESCAPE);
			}

			SUBCASE("Function keys")
			{
				SUBCASE("F1")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F1;
					CHECK(EventToKeycode(event) == F1);
				}

				SUBCASE("F2")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F2;
					CHECK(EventToKeycode(event) == F2);
				}

				SUBCASE("F3")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F3;
					CHECK(EventToKeycode(event) == F3);
				}

				SUBCASE("F4")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F4;
					CHECK(EventToKeycode(event) == F4);
				}

				SUBCASE("F5")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F5;
					CHECK(EventToKeycode(event) == F5);
				}

				SUBCASE("F6")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F6;
					CHECK(EventToKeycode(event) == F6);
				}

				SUBCASE("F7")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F7;
					CHECK(EventToKeycode(event) == F7);
				}

				SUBCASE("F8")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F8;
					CHECK(EventToKeycode(event) == F8);
				}

				SUBCASE("F9")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F9;
					CHECK(EventToKeycode(event) == F9);
				}

				SUBCASE("F10")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F10;
					CHECK(EventToKeycode(event) == F10);
				}

				SUBCASE("F11")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F11;
					CHECK(EventToKeycode(event) == F11);
				}

				SUBCASE("F12")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F12;
					CHECK(EventToKeycode(event) == F12);
				}

				SUBCASE("F13")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F13;
					CHECK(EventToKeycode(event) == F13);
				}

				SUBCASE("F14")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F14;
					CHECK(EventToKeycode(event) == F14);
				}

				SUBCASE("F15")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F15;
					CHECK(EventToKeycode(event) == F15);
				}

				SUBCASE("F16")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F16;
					CHECK(EventToKeycode(event) == F16);
				}

				SUBCASE("F17")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F17;
					CHECK(EventToKeycode(event) == F17);
				}

				SUBCASE("F18")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F18;
					CHECK(EventToKeycode(event) == F18);
				}

				SUBCASE("F19")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F19;
					CHECK(EventToKeycode(event) == F19);
				}

				SUBCASE("F20")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F20;
					CHECK(EventToKeycode(event) == F20);
				}

				SUBCASE("F21")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F21;
					CHECK(EventToKeycode(event) == F21);
				}

				SUBCASE("F22")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F22;
					CHECK(EventToKeycode(event) == F22);
				}

				SUBCASE("F23")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F23;
					CHECK(EventToKeycode(event) == F23);
				}

				SUBCASE("F24")
				{
					event.key.keysym.scancode = SDL_SCANCODE_F24;
					CHECK(EventToKeycode(event) == F24);
				}
			}

			SUBCASE("Home")
			{
				event.key.keysym.scancode = SDL_SCANCODE_HOME;
				CHECK(EventToKeycode(event) == HOME);
			}

			SUBCASE("Keypad")
			{
				SUBCASE("KP 1")
				{
					event.key.keysym.scancode = SDL_SCANCODE_KP_1;
					CHECK(EventToKeycode(event) == KP_1);
				}

				SUBCASE("KP 2")
				{
					event.key.keysym.scancode = SDL_SCANCODE_KP_2;
					CHECK(EventToKeycode(event) == KP_2);
				}

				SUBCASE("KP 3")
				{
					event.key.keysym.scancode = SDL_SCANCODE_KP_3;
					CHECK(EventToKeycode(event) == KP_3);
				}

				SUBCASE("KP 4")
				{
					event.key.keysym.scancode = SDL_SCANCODE_KP_4;
					CHECK(EventToKeycode(event) == KP_4);
				}

				SUBCASE("KP 5")
				{
					event.key.keysym.scancode = SDL_SCANCODE_KP_5;
					CHECK(EventToKeycode(event) == KP_5);
				}

				SUBCASE("KP 6")
				{
					event.key.keysym.scancode = SDL_SCANCODE_KP_6;
					CHECK(EventToKeycode(event) == KP_6);
				}

				SUBCASE("KP 7")
				{
					event.key.keysym.scancode = SDL_SCANCODE_KP_7;
					CHECK(EventToKeycode(event) == KP_7);
				}

				SUBCASE("KP 8")
				{
					event.key.keysym.scancode = SDL_SCANCODE_KP_8;
					CHECK(EventToKeycode(event) == KP_8);
				}

				SUBCASE("KP 9")
				{
					event.key.keysym.scancode = SDL_SCANCODE_KP_9;
					CHECK(EventToKeycode(event) == KP_9);
				}
			}

			SUBCASE("Left Alt")
			{
				event.key.keysym.scancode = SDL_SCANCODE_LALT;
				CHECK(EventToKeycode(event) == ALT_LEFT);
			}

			SUBCASE("Right Alt")
			{
				event.key.keysym.scancode = SDL_SCANCODE_RALT;
				CHECK(EventToKeycode(event) == ALT_RIGHT);
			}

			SUBCASE("Left Ctrl")
			{
				event.key.keysym.scancode = SDL_SCANCODE_LCTRL;
				CHECK(EventToKeycode(event) == CTRL_LEFT);
			}

			SUBCASE("Right Ctrl")
			{
				event.key.keysym.scancode = SDL_SCANCODE_RCTRL;
				CHECK(EventToKeycode(event) == CTRL_RIGHT);
			}

			SUBCASE("Left Shift")
			{
				event.key.keysym.scancode = SDL_SCANCODE_LSHIFT;
				CHECK(EventToKeycode(event) == SHIFT_LEFT);
			}

			SUBCASE("Right Shift")
			{
				event.key.keysym.scancode = SDL_SCANCODE_RSHIFT;
				CHECK(EventToKeycode(event) == SHIFT_RIGHT);
			}

			SUBCASE("Page down")
			{
				event.key.keysym.scancode = SDL_SCANCODE_PAGEDOWN;
				CHECK(EventToKeycode(event) == PAGE_DOWN);
			}

			SUBCASE("Page up")
			{
				event.key.keysym.scancode = SDL_SCANCODE_PAGEUP;
				CHECK(EventToKeycode(event) == PAGE_UP);
			}

			SUBCASE("Print screen")
			{
				event.key.keysym.scancode = SDL_SCANCODE_PRINTSCREEN;
				CHECK(EventToKeycode(event) == PRINT_SCREEN);
			}

			SUBCASE("Return")
			{
				event.key.keysym.scancode = SDL_SCANCODE_RETURN;
				CHECK(EventToKeycode(event) == RETURN);
			}

			SUBCASE("Semicolon")
			{
				event.key.keysym.scancode = SDL_SCANCODE_SEMICOLON;
				CHECK(EventToKeycode(event) == SEMICOLON);
			}

			SUBCASE("Slash")
			{
				event.key.keysym.scancode = SDL_SCANCODE_SLASH;
				CHECK(EventToKeycode(event) == SLASH);
			}

			SUBCASE("Space")
			{
				event.key.keysym.scancode = SDL_SCANCODE_SPACE;
				CHECK(EventToKeycode(event) == SPACE);
			}

			SUBCASE("Tab")
			{
				event.key.keysym.scancode = SDL_SCANCODE_TAB;
				CHECK(EventToKeycode(event) == TAB);
			}

			//SUBCASE("Ampersand &")
			//{
			//	event.key.keysym.mod = SDLK_AMPERSAND;
			//	CHECK(EventToKeycode(event) == AMPERSAND);
			//}

			//SUBCASE("Asterisk *")
			//{
			//	event.key.keysym.mod = SDLK_ASTERISK;
			//	CHECK(EventToKeycode(event) == ASTERISK);
			//}

			//SUBCASE("At @")
			//{
			//	event.key.keysym.mod = SDLK_AT;
			//	CHECK(EventToKeycode(event) == AT);
			//}

			//SUBCASE("Caret ^")
			//{
			//	event.key.keysym.mod = SDLK_CARET;
			//	CHECK(EventToKeycode(event) == CARET);
			//}

			//SUBCASE("Dollar $")
			//{
			//	event.key.keysym.mod = SDLK_CARET;
			//	CHECK(EventToKeycode(event) == CARET);
			//}

			//SUBCASE("Exclaim !")
			//{
			//	event.key.keysym.mod = SDLK_EXCLAIM;
			//	CHECK(EventToKeycode(event) == EXCLAIM);
			//}

			//SUBCASE("Greater than >")
			//{
			//	event.key.keysym.mod = SDLK_GREATER;
			//	CHECK(EventToKeycode(event) == GREATER_THAN);
			//}

			//SUBCASE("Less than <")
			//{
			//	event.key.keysym.mod = SDLK_LESS;
			//	CHECK(EventToKeycode(event) == LESS_THAN);
			//}

			//SUBCASE("Hash #")
			//{
			//	event.key.keysym.mod = SDLK_HASH;
			//	CHECK(EventToKeycode(event) == HASH);
			//}

			//SUBCASE("Left parenthesis (")
			//{
			//	event.key.keysym.mod = SDLK_LEFTPAREN;
			//	CHECK(EventToKeycode(event) == LEFT_PAREN);
			//}

			//SUBCASE("Right parenthesis )")
			//{
			//	event.key.keysym.mod = SDLK_RIGHTPAREN;
			//	CHECK(EventToKeycode(event) == RIGHT_PAREN);
			//}

			//SUBCASE("Percent %")
			//{
			//	event.key.keysym.mod = SDLK_PERCENT;
			//	CHECK(EventToKeycode(event) == PERCENT);
			//}

			//SUBCASE("Plus +")
			//{
			//	event.key.keysym.mod = SDLK_PLUS;
			//	CHECK(EventToKeycode(event) == PLUS);
			//}

			//SUBCASE("Question ?")
			//{
			//	event.key.keysym.mod = SDLK_QUESTION;
			//	CHECK(EventToKeycode(event) == QUESTION);
			//}

			//SUBCASE("Quote \"")
			//{
			//	event.key.keysym.mod = SDLK_QUOTE;
			//	CHECK(EventToKeycode(event) == QUOTE);
			//}

			//SUBCASE("Underscore _")
			//{
			//	event.key.keysym.mod = SDLK_UNDERSCORE;
			//	CHECK(EventToKeycode(event) == UNDERSCORE);
			//}
		}
	}

	TEST_CASE("Convert movement key to a direction")
	{
		SDL_Event event;
		Vector2 direction;

		event.type = SDL_KEYDOWN;

		SUBCASE("W")
		{
			event.key.keysym.scancode = SDL_SCANCODE_W;
			direction = Vector2::Down();
		}

		SUBCASE("A")
		{
			event.key.keysym.scancode = SDL_SCANCODE_A;
			direction = Vector2::Left();
		}

		SUBCASE("S")
		{
			event.key.keysym.scancode = SDL_SCANCODE_S;
			direction = Vector2::Up();
		}

		SUBCASE("D")
		{
			event.key.keysym.scancode = SDL_SCANCODE_D;
			direction = Vector2::Right();
		}

		SUBCASE("Up arrow")
		{
			event.key.keysym.scancode = SDL_SCANCODE_UP;
			direction = Vector2::Down();
		}

		SUBCASE("Left arrow")
		{
			event.key.keysym.scancode = SDL_SCANCODE_LEFT;
			direction = Vector2::Left();
		}

		SUBCASE("Down arrow")
		{
			event.key.keysym.scancode = SDL_SCANCODE_DOWN;
			direction = Vector2::Up();
		}

		SUBCASE("Right arrow")
		{
			event.key.keysym.scancode = SDL_SCANCODE_RIGHT;
			direction = Vector2::Right();
		}

		CHECK(Input::MovementDirection(event) == direction);
	}
}
