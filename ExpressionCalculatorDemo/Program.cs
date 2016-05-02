using System;
using Feel;

namespace ExpressionCalculatorDemo
{
    class Program
    {
        static void Main()
        {
            Console.WriteLine("Supported operations: +,-,*,/,^,%");
            Console.WriteLine("Supported functions: cos, sin, tan, ctan, abs, floor, ceil, sqrt");
            Console.WriteLine("You can also use variables (word) and brackets");
            Console.WriteLine("Enter a expression to compute (e.g. (1+2)^(2 + sin(x))-1 )");

            var expression = Console.ReadLine();

            var expr = new ExpressionEvaluator(expression);
            var variables = expr.Variables();

            foreach (var variable in variables)
            {
                if (!double.IsNaN(expr.GetVariableValue(variable)))
                    continue;

                Console.WriteLine("Enter value of '{0}':", variable);

                string valueString;
                double value;
                do
                {
                    valueString = Console.ReadLine();

                } while (String.IsNullOrWhiteSpace(valueString) || !double.TryParse(valueString, out value));

                expr.SetVariableValue(variable, value);

            }

            Console.WriteLine();
            Console.WriteLine("Result of computation is: {0}", expr.Execute());

            Console.ReadKey(true);
        }
    }
}
