#include "../ExpressionEvaluatorLib/ExpressionEvaluatorLib.h"
#include <iostream>
#include <functional>
#include <omp.h>

double sumInInterval(double from, double to, size_t steps, std::function<double(double)> func)
{
	double value = from;
	double step = (to - from) / steps;

	double sum = 0;

	while (value <= to)
	{
		sum += func(value);
		value += step;
	}

	return sum;
}

double avgTime(std::function<void()> func, size_t repeat)
{
	double start = omp_get_wtime();

	for (size_t i = 0; i < repeat; ++i)
	{
		func();
	}

	double end = omp_get_wtime();

	return ((end - start) / repeat) * 1000;
}

int main()
{
	Expression expr("(cos(x)^0.5*cos(200*x)+abs(x)^0.5-0.7)*(4-x^2)^0.01");

	const double from = -1.5;
	const double to = 1.5;
	const size_t steps = 1000000;

	const size_t bench_repeats = 15;

	double exprTime = avgTime([&]
	{
		const Parameters &parameters = expr.GetParameters();

		ValueType *xValue = parameters.at("x");
		sumInInterval(from, to, steps, [&expr, xValue](double value)
		{
			*xValue = value;
			return expr.Execute();
		});
	}, bench_repeats);

	std::cout << "Expression: " << exprTime << "ms" << std::endl;

	double nativeTime = avgTime([&from, &to, &steps]
	{
		sumInInterval(from, to, steps, [](double value)
		{
			return (pow(cos(value), 0.5) * cos(200 * value) + pow(abs(value), 0.5) - 0.7) * (4 - pow(pow(value, 2), 0.01));
		});
	}, bench_repeats);

	double percantage = (exprTime / nativeTime * 100.0) - 100;

	std::cout << "Native: " << nativeTime << "ms"
		<< " (" << abs(percantage) << "% " << (percantage > 0 ? "faster" : "slower") << ")"
		<< std::endl << std::endl;

	return 0;
}
