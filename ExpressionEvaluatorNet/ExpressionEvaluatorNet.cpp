#include "ExpressionEvaluatorNet.h"

using namespace System::Collections::Generic;

Feel::ExpressionEvaluator::ExpressionEvaluator(String^ expression)
{
	std::string mathExpression = msclr::interop::marshal_as<std::string>(expression);

	try
	{
		_instance = new Expression(mathExpression);
	}
	catch(std::exception e)
	{
		throw gcnew Exception(msclr::interop::marshal_as<String^>(e.what()));
	}
	catch(...)
	{
		throw gcnew Exception("Unexpected exception");
	}
}

Feel::ExpressionEvaluator::~ExpressionEvaluator()
{
	delete _instance;
	_instance = nullptr;
}

double Feel::ExpressionEvaluator::Execute()
{
	try
	{
		return _instance->Execute();
	}
	catch(std::exception e)
	{
		throw gcnew Exception(msclr::interop::marshal_as<String^>(e.what()));
	}
	catch(...)
	{
		throw gcnew Exception("Unexpected exception");
	}
}

void Feel::ExpressionEvaluator::SetVariableValue(String^ name, double value)
{
	std::string paramName = msclr::interop::marshal_as<std::string>(name);
	try
	{
		_instance->SetParameter(paramName, value);
	} 
	catch(std::exception e)
	{
		throw gcnew Exception(msclr::interop::marshal_as<String^>(e.what()));
	}
}

array<String^>^ Feel::ExpressionEvaluator::Variables()
{
	List<String^>^ result = gcnew List<String^>;

	const Parameters & params = _instance->GetParameters();
	for(auto it = params.cbegin(); it != params.cend(); ++it)
	{
		auto key = it->first;

		String^ managedKey = msclr::interop::marshal_as<String^>(key);
		result->Add(managedKey);
	}

	return result->ToArray();
}

double Feel::ExpressionEvaluator::GetVariableValue(String^ name)
{
	const Parameters &params = _instance->GetParameters();

	std::string paramName = msclr::interop::marshal_as<std::string>(name);

	if(params.find(paramName) != params.cend())
	{
		return *params.at(paramName);
	}
	else
	{
		throw gcnew Exception(String::Format("Variable {0} not found!", name));
	}
}
