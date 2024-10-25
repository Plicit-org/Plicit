#pragma once

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
				private:
					std::string Name;
				public:
					Object(std::string name) : Name{name}{}
					std::string GetName() const { return Name; }
			};

			class Constant : public Object
			{
				public:
					Constant() : MathTeXlib::Logic::Language::Object { "" } {}
					Constant(std::string name) : MathTeXlib::Logic::Language::Object{name} {}
			};

			class Variable : public MathTeXlib::Logic::Language::Object
			{
				public:
					Variable(std::string name) : MathTeXlib::Logic::Language::Object {name} {}
					Variable() : MathTeXlib::Logic::Language::Object { "" } {}
			};

			class Function : public MathTeXlib::Logic::Language::Object
			{
				private:
					unsigned int Size;
				public:
					Function() : MathTeXlib::Logic::Language::Object { "" }, Size { 0 } {}
					Function(std::string name, unsigned int size) : MathTeXlib::Logic::Language::Object { name },
						Size { size } {}
					unsigned int GetSize() { return Size; }
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
					Relation() : MathTeXlib::Logic::Language::Object { "" } {}
					Relation(std::string name, unsigned int size) : MathTeXlib::Logic::Language::Object { name }, 
						Size { size } {}
					unsigned int GetSize() { return Size; }
			};

		private:
			std::set<std::string> Names;
			std::map<std::string, MathTeXlib::Logic::Language::Constant> Constants;
			std::map<std::string, MathTeXlib::Logic::Language::Variable> Variables;
			std::map<std::string, MathTeXlib::Logic::Language::Function> Functions;
			std::map<std::string, MathTeXlib::Logic::Language::Relation> Relations;
		
			void AddConstant(MathTeXlib::Logic::Language::Constant constant);
			void AddFunction(MathTeXlib::Logic::Language::Function function);
			void AddRelation(MathTeXlib::Logic::Language::Relation relation);

		public:
			MathTeXlib::Logic::Language::Constant GetConstant(std::string const& name) const;
			MathTeXlib::Logic::Language::Variable GetVariable(std::string const& name);
			MathTeXlib::Logic::Language::Function GetFunction(std::string const& name) const;
			MathTeXlib::Logic::Language::Relation GetRelation(std::string const& name) const;
	};
}
