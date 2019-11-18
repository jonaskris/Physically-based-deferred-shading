#pragma once

#include <GLFW/glfw3.h>

namespace Input
{
    namespace Mouse
    {
        enum class Button
        {
            LEFT_CLICK = GLFW_MOUSE_BUTTON_LEFT, 
            RIGHT_CLICK = GLFW_MOUSE_BUTTON_RIGHT,
            MIDDLE_CLICK = GLFW_MOUSE_BUTTON_MIDDLE,
        };

        enum class Action
        {
            RELEASE = GLFW_RELEASE,
            PRESS = GLFW_PRESS,
            HOLD = 2
        };
    }

    namespace Keyboard
    {
        enum class Key
        {
            // 0 - 9
            NUM0 = GLFW_KEY_0, NUM1 = GLFW_KEY_1, NUM2 = GLFW_KEY_2, NUM3 = GLFW_KEY_3, NUM4 = GLFW_KEY_4, NUM5 = GLFW_KEY_5, NUM6 = GLFW_KEY_6, NUM7 = GLFW_KEY_7, NUM8 = GLFW_KEY_8, NUM9 = GLFW_KEY_9,

            // 0 - 9 keypad
            KP0 = GLFW_KEY_KP_0, KP1 = GLFW_KEY_KP_1, KP2 = GLFW_KEY_KP_2, KP3 = GLFW_KEY_KP_3, KP4 = GLFW_KEY_KP_4, KP5 = GLFW_KEY_KP_5, KP6 = GLFW_KEY_KP_6, KP7 = GLFW_KEY_KP_7, KP8 = GLFW_KEY_KP_8, KP9 = GLFW_KEY_KP_9,
			
            // Function keys
            F1 = GLFW_KEY_F1, F2 = GLFW_KEY_F2, F3 = GLFW_KEY_F3, F4 = GLFW_KEY_F4, F5 = GLFW_KEY_F5, F6 = GLFW_KEY_F6, F7 = GLFW_KEY_F7, F8 = GLFW_KEY_F8, F9 = GLFW_KEY_F9, F10 = GLFW_KEY_F10, F11 = GLFW_KEY_F11, F12 = GLFW_KEY_F12, F13 = GLFW_KEY_F13, F14 = GLFW_KEY_F14, F15 = GLFW_KEY_F15, F16 = GLFW_KEY_F16, F17 = GLFW_KEY_F17, F18 = GLFW_KEY_F18, F19 = GLFW_KEY_F19, F20 = GLFW_KEY_F20, F21 = GLFW_KEY_F21, F22 = GLFW_KEY_F22, F23 = GLFW_KEY_F23, F24 = GLFW_KEY_F24, F25 = GLFW_KEY_F25,
			
            // Alphabet
            A = GLFW_KEY_A, B = GLFW_KEY_B, C = GLFW_KEY_C, D = GLFW_KEY_D, E = GLFW_KEY_E, F = GLFW_KEY_F, G = GLFW_KEY_G, H = GLFW_KEY_H, I = GLFW_KEY_I, J = GLFW_KEY_J, K = GLFW_KEY_K, L = GLFW_KEY_L, M = GLFW_KEY_M, N = GLFW_KEY_N, O = GLFW_KEY_O, P = GLFW_KEY_P, Q = GLFW_KEY_Q, R = GLFW_KEY_R, S = GLFW_KEY_S, T = GLFW_KEY_T, U = GLFW_KEY_U, V = GLFW_KEY_V, W = GLFW_KEY_W, X = GLFW_KEY_X, Y = GLFW_KEY_Y, Z = GLFW_KEY_Z,
			
            // Misc
            SPACE = GLFW_KEY_SPACE,
			LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT, LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL, LEFT_ALT = GLFW_KEY_LEFT_ALT, RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT, RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL, RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
			ESCAPE = GLFW_KEY_ESCAPE, ENTER = GLFW_KEY_ENTER, TAB = GLFW_KEY_TAB, BACKSPACE = GLFW_KEY_BACKSPACE, RIGHT = GLFW_KEY_RIGHT, LEFT = GLFW_KEY_LEFT, DOWN = GLFW_KEY_DOWN, UP = GLFW_KEY_UP
        };

        enum class Action
        {
            RELEASE = GLFW_RELEASE,
            PRESS = GLFW_PRESS,
            REPEAT = GLFW_REPEAT,
            HOLD = 3
        };
    }
}