#include <iostream>
#include "State.h"

namespace MathTeXlib::Logic
{

	State operator||(State const& lefthand, State const& righthand)
	{
		State ret {State::FALSE};
		if (lefthand == State::TRUE || righthand == State::TRUE) ret = State::TRUE;
		if (lefthand == State::UNKNOWN && righthand == State::UNKNOWN) ret = State::UNKNOWN;
		return ret;
	}

	State operator&&(State const& lefthand, State const& righthand)
	{
		State ret {State::FALSE};
		if (lefthand == State::TRUE && righthand == State::TRUE) ret = State::TRUE;
		if ((lefthand == State::UNKNOWN && righthand != State::FALSE) || 
			(righthand == State::UNKNOWN && lefthand != State::FALSE)) ret = State::UNKNOWN;
		return ret;
	}
	
	State operator!(State const& righthand)
	{
		State ret {State::UNKNOWN};
		if (righthand == State::FALSE) ret = State::TRUE;
		if (righthand == State::TRUE) ret = State::FALSE;
		return ret;
	}

	State operator>>(State const& lefthand, State const& righthand)
	{
		State ret {State::FALSE};
		if (lefthand == State::FALSE || righthand == State::TRUE || 
			(lefthand==State::TRUE && righthand==State::UNKNOWN)) ret = State::TRUE;
		if (lefthand == State::UNKNOWN) ret = State::UNKNOWN;
		return ret;
	}

	State operator<<(State const& lefthand, State const& righthand)
	{
		State ret {State::FALSE};
		if (righthand == State::FALSE || lefthand == State::TRUE || 
			(righthand==State::TRUE && lefthand==State::UNKNOWN)) ret = State::TRUE;
		if (righthand == State::UNKNOWN) ret = State::UNKNOWN;
		return ret;
	}

	std::ostream& operator<<(std::ostream& out, State const& in)
	{
		switch(in)
		{
			case State::TRUE:
				out<<"true";
				break;
			case State::FALSE:
				out<<"false";
				break;
			case State::UNKNOWN:
				out<<"unknown";
				break;
		}
		return out;
	}

}
