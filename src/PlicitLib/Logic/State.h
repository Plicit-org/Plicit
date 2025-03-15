#pragma once

#include <iostream>

namespace MathTeXlib::Logic
{

	enum class State
	{
		FALSE = -1,
		UNKNOWN = 0,
		TRUE = 1
	};

	State operator||(State const& lefthand, State const& righthand);
	State operator&&(State const& lefthand, State const& righthand);	
	State operator!(State const& righthand);
	State operator>>(State const& lefthand, State const& righthand);
	State operator<<(State const& lefthand, State const& righthand);

	std::ostream& operator<<(std::ostream& out, State const& in);

}
