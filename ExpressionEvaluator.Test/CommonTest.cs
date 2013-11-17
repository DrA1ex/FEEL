using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace ExpressionEvaluator.Test
{
    [TestClass]
    public class CommonTest
    {
        private const double Delta = 0.0000000001;

        [TestMethod]
        public void ExpressionParseTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("15^2-4*15^3+7*8*9-150^2");

            Assert.AreEqual(-35271, expr.Execute(), Delta);
        }

        [TestMethod]
        public void ExtendedEspressionParseTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("( abs( floor x )%2 )*( ( x^2 )/100 ) " +
                                                                      "+ ( abs( floor( x+1 ) )%2 )*( sqrt( abs( x )" +
                                                                      "*( 100 - abs( x ) ) ) + 100 ) + 10");
            expr.SetVariableValue("x", -0.3);

            Assert.AreEqual(10.0009, expr.Execute(), Delta);
        }

        [TestMethod]
        public void ExtendedEspressionParseTest2()
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
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("( abs( floor x )%2 )*( ( x^2 )/100 ) " +
                                                                      "+ abs( floor( x+1 )%2 ) " +
                                                                      "* ( sqrt( abs( x )" +
                                                                      "*( 100 - abs( x ) ) ) + 100 ) + 10");

            var exprTest = new Func<double, double>(x => (Math.Abs(Math.Floor(x)) % 2) * ((Math.Pow(x, 2)) / 100)
                                                         + Math.Abs(Math.Floor(x + 1) % 2) * (Math.Sqrt(Math.Abs(x) * (100 - Math.Abs(x))) + 100) + 10);

            expr.SetVariableValue("x", -0.6);
            const double step = 0.01;
            double sum = 0;
            double testSum = 0;
            for (double x = -100; x < 100; x += step)
            {
                expr.SetVariableValue("x", x);
                sum += expr.Execute();
                testSum += exprTest(x);
            }

            Assert.AreEqual(testSum, sum, Delta);
        }
    }
}
