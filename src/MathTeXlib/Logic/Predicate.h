#pragma once
#include <functional>

namespace MathTeXlib::Logic
{
	class Predicate
	{
		private:
			std::function<bool()> EvaluationFunction;
		public:
			Predicate(std::function<bool()> evaluationFunction) : EvaluationFunction {evaluationFunction} {}
			bool Evaluate() const;
			Predicate const& operator | (Predicate const& righthand);
			Predicate const& operator & (Predicate const& righthand); 
			virtual ~Predicate() {}
	};
}
