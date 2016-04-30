#include "ExpressionEvaluatorNet.h"

using namespace System::Collections::Generic;

ExpressionEvaluatorNet::ExpressionEvaluator::ExpressionEvaluator(String^ expression)
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

ExpressionEvaluatorNet::ExpressionEvaluator::~ExpressionEvaluator()
{
	delete _instance;
	_instance = nullptr;
}

double ExpressionEvaluatorNet::ExpressionEvaluator::Execute()
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

void ExpressionEvaluatorNet::ExpressionEvaluator::SetVariableValue(String^ name, double value)
{
	Parameters &params = _instance->GetParameters();


	std::string paramName = msclr::interop::marshal_as<std::string>(name);
	auto param = params.find(paramName);

	if(param != params.end())
	{
		param->second = value;
	}
	else
	{
		throw gcnew Exception(String::Format("Variable {0} not found!", name));
	}
}

array<String^>^ ExpressionEvaluatorNet::ExpressionEvaluator::Variables()
{
	List<String^>^ result = gcnew List<String^>;

	Parameters &params = _instance->GetParameters();
	for(auto it = params.begin(); it != params.end(); ++it)
	{
		auto key = it->first;

		String^ managedKey = msclr::interop::marshal_as<String^>(key);
		result->Add(managedKey);
	}

	return result->ToArray();
}

double ExpressionEvaluatorNet::ExpressionEvaluator::GetVariableValue(String^ name)
{
	Parameters &params = _instance->GetParameters();


	std::string paramName = msclr::interop::marshal_as<std::string>(name);

	if(params.find(paramName) != params.end())
	{
		return params[paramName];
	}
	else
	{
		throw gcnew Exception(String::Format("Variable {0} not found!", name));
	}
}
