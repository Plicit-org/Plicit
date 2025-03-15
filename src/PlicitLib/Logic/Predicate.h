#pragma once
#include <functional>
#include "State.h"

namespace MathTeXlib::Logic
{
	class Predicate
	{
		private:
			std::function<State()> EvaluationFunction;
		public:
			Predicate(std::function<State()> evaluationFunction) : EvaluationFunction {evaluationFunction} {}
			State Evaluate() const;
			Predicate operator|(Predicate const& righthand) const;
			Predicate operator&(Predicate const& righthand) const;
			Predicate operator>>(Predicate const& righthand) const;
			Predicate operator<<(Predicate const& righthand) const;
			Predicate operator!() const;
			virtual ~Predicate() {}
	};
}
