﻿using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Feel.Test
{
    [TestClass]
    public class ErrorHandlingTest
    {
        // ReSharper disable once UnusedParameter.Local
        private static void TestNan(double value)
        {
            if(!double.IsNaN(value))
                Assert.Fail("Result should be NaN, but returned {0} instead", value);
        }

        // ReSharper disable once UnusedParameter.Local
        private static void TestInf(double value)
        {
            if(!double.IsInfinity(value))
                Assert.Fail("Result should be Inf, but returned {0} instead", value);
        }

        [TestMethod]
        public void DivByZeroTest()
        {
            var expr = new ExpressionEvaluator("1/0");

            TestInf(expr.Execute());
        }

        [TestMethod]
        public void ModByZeroTest()
        {
            var expr = new ExpressionEvaluator("1%0");

            TestNan(expr.Execute());
        }

        [TestMethod]
        public void UndefinedTokenTest()
        {
            var expr = new ExpressionEvaluator("a^z");
            TestNan(expr.Execute());
        }

        [TestMethod]
        [ExpectedException(typeof(Exception), AllowDerivedTypes = false)]
        public void BracketMismatchTest()
        {
            try
            {
                // ReSharper disable once UnusedVariable
                var expr = new ExpressionEvaluator("(16*)15^2)");
            }
            catch(Exception e)
            {
                if(!e.Message.Contains("Syntactic error"))
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
                // ReSharper disable once UnusedVariable
                var expr = new ExpressionEvaluator("abs e * sin");
            }
            catch(Exception e)
            {
                if(!e.Message.Contains("Syntactic error"))
                    Assert.Fail("Bad exception: {0}", e.Message);

                throw;
            }

            Assert.Fail("Should throw exception");
        }

        [TestMethod]
        public void TestUnknownVariableError()
        {
            var expr = new ExpressionEvaluator("abs a * b");
            expr.SetVariableValue("a", 1);

            var throwed = false;

            try
            {
                expr.SetVariableValue("c", 2);
            }
            catch(Exception)
            {
                //ok
                throwed = true;
            }

            expr.SetVariableValue("b", 2);
            expr.Execute();

            if(!throwed)
            {
                Assert.Fail("Should throw exception");
            }
        }
    }
}