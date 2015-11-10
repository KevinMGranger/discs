#pragma once

#include <windows.h>
#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"

/// <summary>
/// The Input namespace contains helper functions for input.
/// </summary>
namespace Input {

#pragma region typedefs
	typedef DirectX::Keyboard Keyboard;
	typedef DirectX::Keyboard::State KeyboardState;
	typedef DirectX::Keyboard::Keys Keys;
	typedef DirectX::Keyboard::Keys Key;
	typedef DirectX::Keyboard::KeyboardStateTracker KeyboardStateTracker;

	typedef DirectX::Mouse Mouse;
	typedef DirectX::Mouse::State MouseState;
	typedef DirectX::Mouse::ButtonStateTracker MouseButtonStateTracker;

	// TODO: Gamepad Stuff
	typedef DirectX::GamePad GamePad;
	typedef DirectX::GamePad::ButtonStateTracker GamePadButtonStateTracker;
#pragma endregion

	/// <summary>
	/// Update all input state tracking.
	/// </summary>
	void Update();

	/// <summary>
	/// Determine if the given key was pressed this frame.
	/// </summary>
	/// <param name="key">The key to test against.</param>
	/// <returns>true if down this frame, false if not down or was also down last frame.</return>
	bool KeyPressedThisFrame(Key key);

	/// <summary>
	/// Determine if the given key is down at all.
	/// </summary>
	/// <param name="key">The key to test against</param>
	/// <returns>true if the key is down, false if it is not.</returns>
	bool KeyIsDown(Key key);

	/// <summary>
	/// Determine if the given key was released this frame.
	/// </summary>
	/// <param name="key">The key to test against</param>
	/// <returns>true if the key was released this frame, false if it is down or was released last frame.</returns>
	bool KeyReleasedThisFrame(Key key);

	/// <summary>
	/// Determine if the given key is up.
	/// </summary>
	/// <param name="key">The key to test against</param>
	/// <returns>true if the key is up, false if it is not.</returns>
	bool KeyIsUp(Key key);
};