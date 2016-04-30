using System;
using System.Collections.Concurrent;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace ExpressionEvaluator.Test
{
    [TestClass]
    public class CommonTest
    {
        private const double Delta = 0.0000000001;

        private static readonly string GenericExpression = "( abs( floor x )%2 )*( ( x^2 )/100 ) " +
                                                           "+ abs( floor( x+1 )%2 ) " +
                                                           "* ( sqrt( abs( x )" +
                                                           "*( 100 - abs( x ) ) ) + 100 ) + 10";

        private static readonly string GenericExpressionArgument = "x";

        private static readonly Func<double, double> GenericExpressionTest
            = x => Math.Abs(Math.Floor(x)) % 2 * (Math.Pow(x, 2) / 100)
                   + Math.Abs(Math.Floor(x + 1) % 2) * (Math.Sqrt(Math.Abs(x) * (100 - Math.Abs(x))) + 100) + 10;

        [TestMethod]
        public void ExpressionParseTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("15^2-4*15^3+7*8*9-150^2");

            Assert.AreEqual(-35271, expr.Execute(), Delta);
        }

        [TestMethod]
        public void ExtendedExpressionParseTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("( abs( floor x )%2 )*( ( x^2 )/100 ) " +
                                                                      "+ ( abs( floor( x+1 ) )%2 )*( sqrt( abs( x )" +
                                                                      "*( 100 - abs( x ) ) ) + 100 ) + 10");
            expr.SetVariableValue("x", -0.3);

            Assert.AreEqual(10.0009, expr.Execute(), Delta);
        }

        [TestMethod]
        public void ExtendedExpressionParseTest2()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("( abs( x )%2 )*( ( x^2 )/100 ) " +
                                                                      "+ ( abs( x+1 )%2 )*( sqrt( abs( x )" +
                                                                      "*( 100 - abs( x ) ) ) + 100 ) + 10");
            expr.SetVariableValue("x", -0.6);

            Assert.AreEqual(53.0912375322, expr.Execute(), Delta);
        }

        [TestMethod]
        public void VariableParseTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("x^y+(a^b)/c");
            expr.SetVariableValue("x", -0.3);
            expr.SetVariableValue("x", 5);
            expr.SetVariableValue("y", 2);
            expr.SetVariableValue("a", 2);
            expr.SetVariableValue("b", 10);
            expr.SetVariableValue("c", 5);

            Assert.AreEqual(229.8, expr.Execute(), Delta);
        }

        [TestMethod]
        public void LongComputeTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator(GenericExpression);

            const double step = 0.01;
            double sum = 0;
            double testSum = 0;
            for(double x = -100; x < 100; x += step)
            {
                expr.SetVariableValue(GenericExpressionArgument, x);
                sum += expr.Execute();
                testSum += GenericExpressionTest(x);
            }

            Assert.AreEqual(testSum, sum, Delta);
        }

        [TestMethod]
        public async Task TestParallelShorUsage()
        {
            var testRange = Enumerable.Range(-1000, 2000).ToArray();
            const double step = 0.01;

            var threads = new ConcurrentBag<int>();

            var tasks = testRange.Select(i => Task.Run(() =>
            {
                threads.Add(Thread.CurrentThread.ManagedThreadId);

                var expression = new ExpressionEvaluatorNet.ExpressionEvaluator(GenericExpression);
                expression.SetVariableValue(GenericExpressionArgument, i* step);

                return expression.Execute();
            })).ToArray();

            var expressionResult = (await Task.WhenAll(tasks)).Sum();
            var testResult = testRange.Select(i => GenericExpressionTest(i * step)).Sum();

            Assert.AreEqual(testResult, expressionResult, Delta);
            Assert.IsTrue(threads.Distinct().Count() > 1, "Test was executed in 1 thread. Result isn't relaible");
        }

        [TestMethod]
        public async Task TestParallelLongUsage()
        {
            var tasksRange = Enumerable.Range(0, 50).ToArray();
            const double step = 0.01;
            var testRange = Enumerable.Range(0, (int)(200 / step)).ToArray();

            var getValueFromIndex = new Func<int, double>(i => -100 + i * step);

            var threads = new ConcurrentBag<int>();
            var tasks = tasksRange.Select(i => Task.Run(() =>
            {
                threads.Add(Thread.CurrentThread.ManagedThreadId);

                var expression = new ExpressionEvaluatorNet.ExpressionEvaluator(GenericExpression);
                return testRange.Select(rangeIndex =>
                {
                    expression.SetVariableValue(GenericExpressionArgument, getValueFromIndex(rangeIndex));
                    return expression.Execute();
                }).Sum();
            }));

            var expressionResults = await Task.WhenAll(tasks);
            var testResult = testRange.Select(i => GenericExpressionTest(getValueFromIndex(i))).Sum();

            var wrongResults = expressionResults.Where(v => Math.Abs(v - testResult) > Delta).ToArray();
            if(wrongResults.Any())
            {
                Assert.Fail($"Test failed with {wrongResults.Length} wrong results: {String.Join(", ",wrongResults.Distinct())}");
            }

            Assert.IsTrue(threads.Distinct().Count() > 1, "Test was executed in 1 thread. Result isn't relaible");
        }
    }
}