#include "Input.h"

using namespace Input;

void Input::Update()
{
	UpdateKeyboard();
	UpdateMouse();
}

GamePad TheGamePadMgr;

GamePadState Input::GetGamePadState(int player)
{
	return TheGamePadMgr.GetState(player);
}

bool Input::GamePadButtonIsPressed(GamePadButtonState btn)
{
	return btn == GamePadButtonStateTracker::PRESSED;
}