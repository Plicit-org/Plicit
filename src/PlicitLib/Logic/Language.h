#pragma once

#include<concepts>
#include<stdexcept>
#include<map>
#include<set>
#include<vector>
#include<string>


namespace MathTeXlib::Logic
{
	
	class Language
	{
		
		protected:
			class Object
			{
				public:
					enum class ObjectType
					{
						INVALID,
						CONSTANT,
						VARIABLE,
						FUNCTION,
						RELATION,
						CONNECTIVE,
						QUANTIFIER
					};
					Object() : Name { "" }, TypeOfObject { ObjectType::INVALID } {}
					Object(std::string const& name, ObjectType const& typeOfObject) : Name{ name }, 
						TypeOfObject { typeOfObject } {}
					std::string GetName() const { return Name; }
					ObjectType GetType() const { return TypeOfObject; }

				private:
					std::string Name;
					ObjectType TypeOfObject;
			};

			class Constant : public MathTeXlib::Logic::Language::Object
			{
				public:
					Constant() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID } {}
					Constant(std::string const& name) : MathTeXlib::Logic::Language::Object{ name, ObjectType::CONSTANT } {}
			};

			class Variable : public MathTeXlib::Logic::Language::Object
			{
				public:
					Variable(std::string const& name) : MathTeXlib::Logic::Language::Object { name, ObjectType::VARIABLE } {}
					Variable() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID } {}
			};

			class Function : public MathTeXlib::Logic::Language::Object
			{
				private:
					unsigned int Size;
				public:
					Function() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID }, Size { 0 } {}
					Function(std::string const& name, unsigned int const size) : Size { size },
						MathTeXlib::Logic::Language::Object { name, ObjectType::FUNCTION } {}
					unsigned int GetSize() const { return Size; }
			};


			class Term
			{
				private:
					std::map<std::string, MathTeXlib::Logic::Language::Variable> Variables;
					MathTeXlib::Logic::Language::Object Value;
					std::vector<Term> Arguments;
				public:
					Term(MathTeXlib::Logic::Language::Variable value) : Value {value} 
						{ Variables[value.GetName()] = value; }
					Term(MathTeXlib::Logic::Language::Constant value) : Value(value) {}
					Term(MathTeXlib::Logic::Language::Function value, std::vector<Term> arguments); 
					
					std::string GetName() const { return Value.GetName(); }
					Term Substitute(Term const& newValue, Term const& oldValue, 
						MathTeXlib::Logic::Language const& language) const;

					bool IsClosed() const { return Variables.size() == 0; }
					std::map<std::string, MathTeXlib::Logic::Language::Variable> GetVariables () { return Variables; }
					bool operator==(Term const& rhs) const;
			};

			class Relation : public MathTeXlib::Logic::Language::Object
			{
				private:
					unsigned int Size;
				public:
					Relation() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID }, Size { 0 } {}
					Relation(std::string const& name, unsigned int const size) : Size { size },
						MathTeXlib::Logic::Language::Object { name, ObjectType::RELATION } {}
					unsigned int GetSize() const { return Size; }
			};

			class Connective : public MathTeXlib::Logic::Language::Object
			{
				private:
					unsigned int Size;
				public:
					Connective() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID }, Size { 0 } {}
					Connective(std::string const& name, unsigned int const size) : Size { size },
						MathTeXlib::Logic::Language::Object { name, ObjectType::CONNECTIVE } {}
					unsigned int GetSize() const { return Size; }
			};

			class Quantifier : public MathTeXlib::Logic::Language::Object
			{
				public:
					Quantifier() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID } {}
					Quantifier(std::string const& name) : 
						MathTeXlib::Logic::Language::Object { name, ObjectType::QUANTIFIER } {}
			};
		
			void AddConstant(MathTeXlib::Logic::Language::Constant constant)
			{ AddObject(constant, Constants, "constant"); }
			
			void AddFunction(MathTeXlib::Logic::Language::Function function) 
			{ AddObject(function, Functions, "function"); }
		
			void AddRelation(MathTeXlib::Logic::Language::Relation relation) 
			{ AddObject(relation, Relations, "relation"); }
			
		private:
			std::set<std::string> Names;
			std::map<std::string, MathTeXlib::Logic::Language::Constant> Constants;
			std::map<std::string, MathTeXlib::Logic::Language::Variable> Variables;
			std::map<std::string, MathTeXlib::Logic::Language::Function> Functions;
			std::map<std::string, MathTeXlib::Logic::Language::Relation> Relations;
			std::map<std::string, MathTeXlib::Logic::Language::Connective> Connectives;
			std::map<std::string, MathTeXlib::Logic::Language::Quantifier> Quantifiers;
			template<typename T> 
			void AddObject(T object, std::map<std::string, T> collection, std::string const& type) 
				requires std::is_base_of_v<Object, T>;

			template<typename T>
			T GetObject(std::string name, std::map<std::string, T> collection, std::string const& type) const 
				requires std::is_base_of_v<Object, T>;

			void AddConnective(MathTeXlib::Logic::Language::Connective connective) 
			{ AddObject(connective, Connectives, "connective"); }

			void AddQuantifier(MathTeXlib::Logic::Language::Quantifier quantifier) 
			{ AddObject(quantifier, Quantifiers, "quantifier"); }


		public:
			Language();

			MathTeXlib::Logic::Language::Constant GetConstant(std::string const& name) const
			{ return GetObject(name, Constants, "constant"); }

			MathTeXlib::Logic::Language::Function GetFunction(std::string const& name) const
			{ return GetObject(name, Functions, "function"); }

			MathTeXlib::Logic::Language::Relation GetRelation(std::string const& name) const
			{ return GetObject(name, Relations, "relation"); }

			MathTeXlib::Logic::Language::Connective GetConnective(std::string const& name) const
			{ return GetObject(name, Connectives, "connective"); }

			MathTeXlib::Logic::Language::Quantifier GetQuantifier(std::string const& name) const
			{ return GetObject(name, Quantifiers, "quantifier"); }

			MathTeXlib::Logic::Language::Variable GetVariable(std::string const& name);

	};
}
