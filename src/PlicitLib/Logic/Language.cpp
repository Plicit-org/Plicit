#include<string>
#include<stdexcept>
#include<vector>
#include<concepts>
#include "Language.h"

namespace MathTeXlib::Logic
{

	Language::Language()
	{
		Quantifier forall { "ForAll" };
		AddQuantifier(forall);
		Quantifier exists { "Exists" };
		AddQuantifier(exists);
		Quantifier existsUnique { "ExistsUnique" };
		AddQuantifier(existsUnique);

		Connective logicAnd { "And", 2 };
		AddConnective(logicAnd);
		Connective logicOr { "Or", 2 };
		AddConnective(logicOr);
		Connective implies { "Implies", 2 };
		AddConnective(implies);
		Connective logicNot { "Not", 1 };
		AddConnective(logicNot);
		Connective equivalent { "Equivalent", 2 };
		AddConnective(equivalent);
		Connective logicXor { "Xor", 2 };
		AddConnective(logicXor);

		Relation equal { "Equal", 2 };
		AddRelation(equal);
	}

	MathTeXlib::Logic::Language::Variable Language::GetVariable(std::string const& name)
	{
		if(Variables.contains(name) == true) return Variables.at(name);
		Variable addVariable { name };
		AddObject(addVariable, Variables, "variable");
		return addVariable;
	}
	
	template<typename T> 
	void Language::AddObject(T object, std::map<std::string, T> collection, std::string const& type)
		requires std::is_base_of_v<Object, T>
	{
		if(Names.contains(object.GetName()) == true)
		{
			throw std::invalid_argument("Invalid " + type + " name " + object.GetName() + 
				" there is already an object in this language with this name.");
		}
		Names.insert(object.GetName());
		collection[object.GetName()] = object;
	}

	template<typename T>
	T Language::GetObject(std::string name, std::map<std::string, T> collection, std::string const& type) const
		requires std::is_base_of_v<Object, T>
	{
		if(collection.contains(name) == true) return collection.at(name);
		throw std::invalid_argument("Unknown " + type + " " + name);
	}

	Language::Term::Term(MathTeXlib::Logic::Language::Function value, 
		std::vector<Term> arguments) : Value { value }, Arguments { arguments }
	{
		if (value.GetSize() != Arguments.size())
		{
			std::string errmsg = "Invalid number of arguments for function " + 
				value.GetName() + ", got " + std::to_string(Arguments.size()) + 
				" arguments, expected " + std::to_string(value.GetSize()) + " arguments.";
			throw std::length_error(errmsg);
		}
		for(Term term : Arguments)
		{
			Variables.merge(term.GetVariables());
		}

	}

	Language::Term Language::Term::Substitute(Language::Term const& newValue, Language::Term const& oldValue,
		MathTeXlib::Logic::Language const& language) const
	{
		if ((*this) == oldValue) return newValue;
		if (Arguments.size() == 0) return *this;
		std::vector<Term> arguments;
		for(Language::Term term : Arguments)
		{
			arguments.push_back(term.Substitute(newValue, oldValue, language));
		}
		return Term { language.GetFunction(Value.GetName()), arguments};
	}

	bool Language::Term::operator==(Term const& rhs) const
	{
		bool ret = false;
		if (Value.GetName() == rhs.Value.GetName())
		{
			ret = true;
			ret = ret && (Arguments == rhs.Arguments);
		}
		return ret;
	}
}
