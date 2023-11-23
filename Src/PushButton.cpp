
#include "PushButton.hpp"


/***************************************************************/
/*                       PushButton                            */
/***************************************************************/

PushButton::PushButton()
{
	// Initialize to PushButtonReleased state
	_state = PushButtonReleased::Instance();
}

void PushButton::Update(bool button_state)
{
	_state->Update(this, button_state);
}

bool PushButton::IsPressed(void)
{
	return _state->IsPressed();
}

void PushButton::ChangeState(PushButtonState* state)
{
	_state = state;
}


/***************************************************************/
/*                    PushButtonState                          */
/***************************************************************/

void PushButtonState::ChangeState(PushButton* push_button, PushButtonState* state)
{
	push_button->ChangeState(state);
}


/***************************************************************/
/*                   PushButtonPressed                         */
/***************************************************************/

PushButtonPressed PushButtonPressed::_instance;

PushButtonPressed::PushButtonPressed() :
		confidenceThreshold(200),
		buttonReleasedConfidenceLevel(0)
{}

PushButtonPressed* PushButtonPressed::Instance(void)
{
	return &_instance;
}

void PushButtonPressed::Update(PushButton* push_button, bool button_state)
{
	if(!button_state)
	{
		// Once the Button Released Confidence Level has been reached
		if(buttonReleasedConfidenceLevel > confidenceThreshold)
		{
			// Reset the Button Released Confidence Level
			buttonReleasedConfidenceLevel = 0;

			// Transition to the PushButtonReleased state
			ChangeState(push_button, PushButtonReleased::Instance());
		}
		else
		{
			// Increase the Button Released Confidence level
			buttonReleasedConfidenceLevel += 1;
		}
	}
}

bool PushButtonPressed::IsPressed(void)
{
	return true;
}


/***************************************************************/
/*                   PushButtonReleased                        */
/***************************************************************/

PushButtonReleased PushButtonReleased::_instance;

PushButtonReleased::PushButtonReleased() :
		confidenceThreshold(200),
		buttonPressedConfidenceLevel(0)
{}

PushButtonReleased* PushButtonReleased::Instance(void)
{
	return &_instance;
}

void PushButtonReleased::Update(PushButton* push_button, bool button_state)
{
	if(button_state)
	{
		// Once the Button Pressed Confidence Level has been reached
		if(buttonPressedConfidenceLevel > confidenceThreshold)
		{
			// Reset the Button Pressed Confidence Level
			buttonPressedConfidenceLevel = 0;

			// Transition to the PushButtonPressed state
			ChangeState(push_button, PushButtonPressed::Instance());
		}
		else
		{
			// Increase the Button Pressed Confidence level
			buttonPressedConfidenceLevel += 1;
		}
	}
}

bool PushButtonReleased::IsPressed(void)
{
	return false;
}
