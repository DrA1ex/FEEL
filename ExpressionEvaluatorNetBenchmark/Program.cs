using System;
using System.Diagnostics;
using ExpressionEvaluatorNet;

namespace ExpressionEvaluatorNetBenchmark
{
    public class FeelVsManaged
    {
        private const double From = -1.6;
        private const double To = 1.6;
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
    }

    internal class Program
    {
        private static void Main()
        {
            var bench = new FeelVsManaged();
            const uint benchmarkRepeats = 15;

            for(uint i = 0; i < benchmarkRepeats; i++)
            {
                bench.FeelTest();
            }

            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();

            var stopWatch = new Stopwatch();
            stopWatch.Start();

            for(uint i = 0; i < benchmarkRepeats; i++)
            {
                bench.FeelTest();
            }

            stopWatch.Stop();

            var expressionTime = stopWatch.Elapsed.TotalMilliseconds / benchmarkRepeats;

            Console.WriteLine("Expression: {0:F} ms", expressionTime);

            for(uint i = 0; i < benchmarkRepeats; i++)
            {
                bench.ManagedTest();
            }

            stopWatch = null;

            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();

            stopWatch = new Stopwatch();
            stopWatch.Start();

            for(uint i = 0; i < benchmarkRepeats; i++)
            {
                bench.ManagedTest();
            }

            stopWatch.Stop();

            var managedTime = stopWatch.Elapsed.TotalMilliseconds / benchmarkRepeats;

            var percentage = expressionTime / managedTime - 1;

            Console.WriteLine("Managed: {0:F} ms ({1:p} {2})", managedTime, Math.Abs(percentage), percentage > 0 ? "faster" : "slower");
        }
    }
}