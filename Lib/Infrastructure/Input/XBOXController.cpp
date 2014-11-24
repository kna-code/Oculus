#include "stdafx.h"
#include "XBOXController.h"
#include <math.h>

namespace Infrastructure
{

//-----------------------------------------------------------------------------------
// Life Cycle
//-----------------------------------------------------------------------------------

XBOXController::XBOXController(int playerNumber)
: m_deadzoneLeftThumb(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
, m_deadzoneRightThumb(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
, m_triggerThreshold(XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
, m_isConnected(false)
{
    // Set the Controller Number
    m_controllerNum = playerNumber - 1;

	// Initialize the States
	ZeroMemory(&m_previousState, sizeof(XINPUT_STATE));
    ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
}

//-----------------------------------------------------------------------------------
// Public Methods
//-----------------------------------------------------------------------------------

void XBOXController::Update()
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD Result = XInputGetState(m_controllerNum, &state);
	if(Result == ERROR_SUCCESS)
    {
		m_isConnected = true;

		// Update the states only when they have changed
		if(m_currentState.dwPacketNumber != state.dwPacketNumber)	
		{
			CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
			CopyMemory(&m_currentState, &state, sizeof(XINPUT_STATE));
		}

		// TODO: Trigger events based on the change in state.		
    }
    else
    {		
	   m_isConnected = false;

	   // Clear the states.
       ZeroMemory(&m_previousState, sizeof(XINPUT_STATE));
	   ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
    }
}

void XBOXController::Vibrate(int leftVal, int rightVal)
{
	if(!IsConnected())
	{
		return;
	}

    // Create a Vibraton State
    XINPUT_VIBRATION vibration;

    // Zeroise the Vibration
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    vibration.wLeftMotorSpeed = leftVal;
    vibration.wRightMotorSpeed = rightVal;

    // Vibrate the controller
    XInputSetState(m_controllerNum, &vibration);
}

Vec2 XBOXController::GetLeftThumbStickPosition()
{
	if(!IsConnected())
	{
		return Vec2(0.0f, 0.0f);
	}

	XINPUT_STATE state = GetCurrentState();
	return NormalizeThumbStickPosition( state.Gamepad.sThumbLX,  state.Gamepad.sThumbLY, m_deadzoneLeftThumb);
}

Vec2 XBOXController::GetRightThumbStickPosition()
{
	if(!IsConnected())
	{
		return Vec2(0.0f, 0.0f);
	}

	XINPUT_STATE state = GetCurrentState();
	return NormalizeThumbStickPosition( state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, m_deadzoneRightThumb);
}

float XBOXController::GetLeftTriggerPosition()
{
	if(!IsConnected())
	{
		return 0;
	}

	XINPUT_STATE state = GetCurrentState();
	return NormalizeTiggerPosition(state.Gamepad.bLeftTrigger, m_triggerThreshold);
}
float XBOXController::GetRightTriggerPosition()
{
	if(!IsConnected())
	{
		return 0;
	}

	XINPUT_STATE state = GetCurrentState();
	return NormalizeTiggerPosition(state.Gamepad.bRightTrigger, m_triggerThreshold);
}

//-----------------------------------------------------------------------------------
// Private Methods
//-----------------------------------------------------------------------------------

Vec2 XBOXController::NormalizeThumbStickPosition(int x, int y, int deadZone)
{
	//determine how far the controller is pushed
	float magnitude = sqrt(float(x*x) + float(y*y));

	//determine the direction the controller is pushed
	float normalizedX = float(x) / magnitude;
	float normalizedY = float(y) / magnitude;

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > deadZone)
	{
	  //clip the magnitude at its expected maximum value
	  if (magnitude > 32767) magnitude = 32767;
  
	  //adjust magnitude relative to the end of the dead zone
	  magnitude -= deadZone;

	  //optionally normalize the magnitude with respect to its expected range
	  //giving a magnitude value of 0.0 to 1.0
	  normalizedMagnitude = magnitude / (32767 - deadZone);

	  return Vec2(normalizedX, normalizedY);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;

		return Vec2(0.0f, 0.0f);
	}
}

float XBOXController::NormalizeTiggerPosition(int value, int deadZone)
{
	if (value > deadZone)
	{
	  //clip the magnitude at its expected maximum value
	  if (value > 32767) value = 32767;
  
	  //adjust magnitude relative to the end of the dead zone
	  value -= deadZone;

	  //optionally normalize the magnitude with respect to its expected range
	  //giving a magnitude value of 0.0 to 1.0
	  float normalizedValue = float(value) / (32767 - deadZone);

	  return normalizedValue;
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		return 0;
	}
}


}