#ifndef PUSHBUTTON_HPP_
#define PUSHBUTTON_HPP_


#include "stm32f0xx_hal.h"


class PushButton;


class PushButtonState
{
public:
	virtual void Update(PushButton*, bool) = 0;

	virtual bool IsPressed(void) = 0;

protected:

	void ChangeState(PushButton*, PushButtonState*);
};


class PushButtonPressed : public PushButtonState
{
public:

	PushButtonPressed(const PushButtonPressed&) = delete;

	static PushButtonPressed* Instance();

	virtual void Update(PushButton*, bool);

	virtual bool IsPressed(void);

private:

	PushButtonPressed();

	static PushButtonPressed _instance;

	uint32_t confidenceThreshold;
	uint32_t buttonReleasedConfidenceLevel;
};


class PushButtonReleased : public PushButtonState
{
public:

	PushButtonReleased(const PushButtonReleased&) = delete;

	static PushButtonReleased* Instance();

	virtual void Update(PushButton*, bool);

	virtual bool IsPressed(void);

private:

	PushButtonReleased();

	static PushButtonReleased _instance;

	uint32_t confidenceThreshold;
	uint32_t buttonPressedConfidenceLevel;
};


class PushButton
{
public:

	PushButton();

	void Update(bool button_state);

	bool IsPressed(void);

private:

	friend class PushButtonState;

	PushButtonState* _state;

	void ChangeState(PushButtonState*);
};

#endif /* PUSHBUTTON_HPP_ */
