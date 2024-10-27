#pragma once

#include<map>
#include<string>
#include<vector>
#include "Language.h"
#include "Predicate.h"

namespace MathTeXlib::Logic
{
	class Theory : public Language
	{
		protected:
			class Formula 
			{
				private:
					std::map<std::string, MathTeXlib::Logic::Language::Variable> BoundVariables;
					std::map<std::string, MathTeXlib::Logic::Language::Variable> FreeVariables;
					MathTeXlib::Logic::Language::Object MainPart;
					MathTeXlib::Logic::Language::Variable Subject;
					std::vector<Formula> Formulas;
					std::vector<MathTeXlib::Logic::Language::Term> Terms;
				public:
					Formula(MathTeXlib::Logic::Language::Relation const& relation, 
						vector<MathTeXlib::Logic::Language::Term> arguments);
					Formula(MathTeXlib::Logic::Language::Quantifier quantifier const&, 
						MathTeXlib::Logic::Language::Variable const& variable, Formula formula);
					Formula(MathTeXlib::Logic::Language::Connective, vector<Formula> arguments);
										std::map<std::string, MathTeXlib::Logic::Language::Variable> GetFreeVariables() const { return FreeVariables; }
					std::map<std::string, MathTeXlib::Logic::Language::Variable> GetBoundVariables() const
						{ return BoundVariables; }
			};
	};
}
