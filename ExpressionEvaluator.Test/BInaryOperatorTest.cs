﻿using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Feel.Test
{
    [TestClass]
    public class BInaryOperatorTest
    {
        private const double Delta = 0.0000000001;

        [TestMethod]
        public void AddTest()
        {
            var expr = new ExpressionEvaluator("1+(2+3+(4+5+6))");

            Assert.AreEqual(1 + 2 + 3 + 4 + 5 + 6, expr.Execute(), Delta);
        }

        [TestMethod]
        public void SubTest()
        {
            var expr = new ExpressionEvaluator("1-(2-3-(4-5-6))");

            Assert.AreEqual(1 - (2 - 3 - (4 - 5 - 6)), expr.Execute(), Delta);
        }

        [TestMethod]
        public void MulTest()
        {
            var expr = new ExpressionEvaluator("6*3*8*(-7)");

            Assert.AreEqual(6 * 3 * 8 * -7, expr.Execute(), Delta);
        }

        [TestMethod]
        public void DivTest()
        {
            var expr = new ExpressionEvaluator("1024/2 /4 /8");

            Assert.AreEqual(1024.0 / 2 / 4 / 8, expr.Execute(), Delta);
        }

        [TestMethod]
        public void ModTest()
        {
            var expr = new ExpressionEvaluator("9%10%5");

            Assert.AreEqual(9 % 10 % 5, expr.Execute(), Delta);
        }

        [TestMethod]
        public void PowTest()
        {
            var expr = new ExpressionEvaluator("2^2^2^3");

            Assert.AreEqual(Math.Pow(Math.Pow(Math.Pow(2.0, 2.0), 2.0), 3), expr.Execute(), Delta);
        }

        [TestMethod]
        public void EqualTest()
        {
            var expr = new ExpressionEvaluator("1 + x = y + 2");

            expr.SetVariableValue("x", 2);
            expr.SetVariableValue("y", 1);

            Assert.AreEqual(1, expr.Execute());

            expr.SetVariableValue("x", 25);
            expr.SetVariableValue("y", 25);

            Assert.AreEqual(0, expr.Execute());
        }
    }
}