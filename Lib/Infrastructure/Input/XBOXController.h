// References:
// http://msdn.microsoft.com/en-us/library/windows/desktop/ee417001%28v=vs.85%29.aspx

#pragma once

// No MFC
#define WIN32_LEAN_AND_MEAN

// We need the Windows Header and the XInput Header
#include <windows.h>
#include <XInput.h>
#include "../General/Types.h"

// Now, the XInput Library
// NOTE: COMMENT THIS OUT IF YOU ARE NOT USING
// A COMPILER THAT SUPPORTS THIS METHOD OF LINKING LIBRARIES
//#pragma comment(lib, "XInput.lib")

namespace Infrastructure
{

// Enum Mapping for the XBox controlls.
enum XBOXControlId
{
	DPAD_UP = XINPUT_GAMEPAD_DPAD_UP,
	DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
	DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
	DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
	START = XINPUT_GAMEPAD_START,
	BACK = XINPUT_GAMEPAD_BACK,
	LEFT_THUMB = XINPUT_GAMEPAD_LEFT_THUMB,
	RIGHT_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB,
	LEFT_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RIGHT_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	GAMEPAD_A = XINPUT_GAMEPAD_A,
	GAMEPAD_B = XINPUT_GAMEPAD_B,
	GAMEPAD_X = XINPUT_GAMEPAD_X,
	GAMEPAD_Y = XINPUT_GAMEPAD_Y
};

// XBOX Controller Class Definition
class XBOXController
{
private:
	XINPUT_STATE m_previousState;
	XINPUT_STATE m_currentState;

	bool m_isConnected;

	int m_controllerNum;

	int m_deadzoneLeftThumb;
	int m_deadzoneRightThumb;
	int m_triggerThreshold;
public:
	XBOXController(int playerNumber);
	
	void Update();
	void Vibrate(int leftVal = 0, int rightVal = 0);

	Vec2 GetLeftThumbStickPosition();
	Vec2 GetRightThumbStickPosition();
	float GetLeftTriggerPosition();
	float GetRightTriggerPosition();

	bool IsConnected();
	XINPUT_STATE GetPreviousState();
	XINPUT_STATE GetCurrentState();

private:
	Vec2 NormalizeThumbStickPosition(int x, int y, int deadZone);
	float NormalizeTiggerPosition(int value, int deadZone);		
};

inline bool XBOXController::IsConnected()
{
	return 	m_isConnected;
}


inline XINPUT_STATE XBOXController::GetPreviousState()
{
	return 	m_previousState;
}


inline XINPUT_STATE XBOXController::GetCurrentState()
{
	return 	m_currentState;
}

}

