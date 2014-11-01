#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

// No MFC
#define WIN32_LEAN_AND_MEAN

// We need the Windows Header and the XInput Header
#include <windows.h>
#include <XInput.h>

// Now, the XInput Library
// NOTE: COMMENT THIS OUT IF YOU ARE NOT USING
// A COMPILER THAT SUPPORTS THIS METHOD OF LINKING LIBRARIES
//#pragma comment(lib, "XInput.lib")

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
    XINPUT_STATE _controllerState;
    int _controllerNum;
public:
    XBOXController(int playerNumber);
    XINPUT_STATE GetState();
    bool IsConnected();
    void Vibrate(int leftVal = 0, int rightVal = 0);
};

#endif
