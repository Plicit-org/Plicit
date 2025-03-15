#pragma once

#include<algorithm>
#include<ranges>
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
					Formula() : MainPart { MathTeXlib::Logic::Language::Object {"", MathTeXlib::Logic::Language::Object::ObjectType::INVALID } }  {}
					Formula(MathTeXlib::Logic::Language::Relation const& relation, 
						std::vector<MathTeXlib::Logic::Language::Term> arguments);
					Formula(MathTeXlib::Logic::Language::Quantifier const& quantifier, 
						MathTeXlib::Logic::Language::Variable const& variable, Formula formula);
					Formula(MathTeXlib::Logic::Language::Connective const& connective, std::vector<Formula> arguments);
					
					std::map<std::string, MathTeXlib::Logic::Language::Variable> GetFreeVariables() const 
					{ return FreeVariables; }
					
					std::map<std::string, MathTeXlib::Logic::Language::Variable> GetBoundVariables() const
					{ return BoundVariables; }

					bool IsClosed() const { return FreeVariables.size() == 0; }
			};

			void AddAxiom(Formula const& axiom, std::string const& name);
			void AddProperty(std::string property) { Properties.push_back(property); }
		private:
			std::map<std::string, Formula> Axioms;
			std::vector<std::string> Properties;
		public:
			Formula GetAxiom(std::string name);
			bool HasProperty(std::string name) { return (std::ranges::count(Properties, name)) > 0; }
	};
}
