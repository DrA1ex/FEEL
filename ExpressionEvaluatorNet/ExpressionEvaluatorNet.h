#pragma once

#include "../ExpressionEvaluatorLib/ExpressionEvaluatorLib.h"
#include <msclr\marshal_cppstd.h>

using namespace System;

namespace Feel {

	public ref class ExpressionEvaluator
	{
		Expression *_instance;

	public:

		ExpressionEvaluator(String^ expression);
		~ExpressionEvaluator();

		double Execute();

		void SetVariableValue(String^ name, double value);

		double GetVariableValue(String^ name);

		array<String^>^ Variables();
	};
}
