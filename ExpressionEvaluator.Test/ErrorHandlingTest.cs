using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace ExpressionEvaluator.Test
{
    [TestClass]
    public class ErrorHandlingTest
    {

        static void TestNan(double value)
        {
            if (!double.IsNaN(value))
                Assert.Fail("Result should be NaN, but returned {0} instead", value);
        }

        static void TestInf(double value)
        {
            if (!double.IsInfinity(value))
                Assert.Fail("Result should be Inf, but returned {0} instead", value);
        }

        [TestMethod]
        public void DivByZeroTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("1/0");

            TestInf(expr.Execute());
        }

        [TestMethod]
        public void ModByZeroTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("1%0");

            TestNan(expr.Execute());
        }

        [TestMethod]
        public void UndefinedTokenTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("a^z");
            TestNan(expr.Execute());
        }

        [TestMethod]
        [ExpectedException(typeof(Exception), AllowDerivedTypes = false)]
        public void BracketMismatchTest()
        {
            try
            {
                var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("(16*)15^2)");
            }
            catch (Exception e)
            {
                if (!e.Message.Contains("Syntactic error"))
                    Assert.Fail("Bad exception: {0}", e.Message);

                throw;
            }

            Assert.Fail("Should throw exception");
        }

        [TestMethod]
        [ExpectedException(typeof(Exception), AllowDerivedTypes = false)]
        public void ArgumentMismatchTest()
        {
            try
            {
                var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("abs e * sin");
            }
            catch (Exception e)
            {
                if (!e.Message.Contains("Syntactic error"))
                    Assert.Fail("Bad exception: {0}", e.Message);

                throw;
            }

            Assert.Fail("Should throw exception");
        }
    }
}
