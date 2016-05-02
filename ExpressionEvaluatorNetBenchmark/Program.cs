using System;
using System.Diagnostics;
using System.Globalization;
using System.Reflection;
using Ciloci.Flee;
using ExpressionEvaluatorNet;
using NCalc;

namespace ExpressionEvaluatorNetBenchmark
{
    public class FeelVsManaged
    {
        private const double From = -1.5;
        private const double To = 1.5;
        private const uint Steps = 1000000;

        private double Sum(Func<double, double> func)
        {
            var value = From;
            var step = (To - From) / Steps;

            double sum = 0;

            while(value <= To)
            {
                sum += func(value);
                value += step;
            }

            return sum;
        }

        public double ManagedTest()
        {
            return Sum(value => (Math.Pow(Math.Cos(value), 0.5) * Math.Cos(200 * value) + Math.Pow(Math.Abs(value), 0.5) - 0.7) * (4 - Math.Pow(Math.Pow(value, 2), 0.01)));
        }

        public double FeelTest()
        {
            var expr = new ExpressionEvaluator("(cos(x)^0.5*cos(200*x)+abs(x)^0.5-0.7)*(4-x^2)^0.01");
            return Sum(value =>
            {
                expr.SetVariableValue("x", value);
                return expr.Execute();
            });
        }

        public double FleeTest()
        {
            var context = new ExpressionContext();
            context.Imports.AddType(typeof(Math));

            context.Variables["x"] = 0.0;

            IGenericExpression<double> testExpr = context.CompileGeneric<double>("(cos(x)^0.5*cos(200*x)+abs(x)^0.5-0.7)*(4-x^2)^0.01");
            return Sum(value =>
            {
                context.Variables["x"] = value;
                return testExpr.Evaluate();
            });
        }

        public double NCalcTest()
        {
            var e = new Expression("(Pow(Cos(value), 0.5) * Cos(200 * value) + Pow(Abs(value), 0.5) - 0.7) * (4 - Pow(Pow(value, 2), 0.01))");

            e.Parameters["value"] = 0.0;

            return Sum(value =>
            {
                e.Parameters["x"] = value;
                return (double)e.Evaluate();
            });
        }
    }

    internal class Program
    {
        public delegate double TestMethodDelegate();

        private static readonly uint benchmarkRepeats = 15;

        private static double TestMethod(object obj, string methodName, double? other = null)
        {
            Console.WriteLine("Prepare test for method: {0}", methodName);

            var methodRef = obj.GetType().GetMethod(methodName, BindingFlags.Instance | BindingFlags.InvokeMethod | BindingFlags.Public);

            if(methodRef != null)
            {
                try
                {
                    var methodDelegate = (TestMethodDelegate)Delegate.CreateDelegate(typeof(TestMethodDelegate), obj, methodRef, true);
                    if(methodDelegate == null) throw new Exception("Unabel to crate delegate to target method");

                    Console.WriteLine("Warm up...");

                    for(uint i = 0; i < benchmarkRepeats; i++)
                    {
                        methodDelegate();
                    }

                    Console.WriteLine("Testing...");

                    GC.Collect();
                    GC.WaitForPendingFinalizers();
                    GC.Collect();

                    var stopWatch = new Stopwatch();
                    stopWatch.Start();

                    for(uint i = 0; i < benchmarkRepeats; i++)
                    {
                        methodDelegate();
                    }

                    stopWatch.Stop();

                    var testTime = stopWatch.Elapsed.TotalMilliseconds / benchmarkRepeats;


                    if(other.HasValue)
                    {
                        var percentage = 1 - testTime / other.Value;
                        Console.WriteLine("{0}: {1:F} ms ({2:p} {3})", methodName, testTime, Math.Abs(percentage), percentage > 0 ? "faster" : "slower");
                    }
                    else
                    {
                        Console.WriteLine("{0}: {1:F} ms", methodName, testTime);
                    }

                    return testTime;
                }
                catch(Exception e)
                {
                    Console.WriteLine("Failed to run test: {0}", e.Message);
                }
            }
            else
            {
                Console.WriteLine("Failed to run test: Unable to find method {0}", methodName);
            }

            return double.NaN;
        }

        private static void Main()
        {
            var bench = new FeelVsManaged();

            CultureInfo.DefaultThreadCurrentCulture = CultureInfo.InvariantCulture;

            var exprTime = TestMethod(bench, nameof(bench.FeelTest));

            TestMethod(bench, nameof(bench.FleeTest), exprTime);
            TestMethod(bench, nameof(bench.NCalcTest), exprTime);

            TestMethod(bench, nameof(bench.ManagedTest), exprTime);
        }
    }
}