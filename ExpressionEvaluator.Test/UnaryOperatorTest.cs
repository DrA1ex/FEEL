using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace ExpressionEvaluator.Test
{
    [TestClass]
    public class UnaryOperatorTest
    {
        private const double Delta = 0.0000000001;

        [TestMethod]
        public void AbsTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("abs (-5) + abs(-8) - abs 15 ");

            Assert.AreEqual(Math.Abs(-5) + Math.Abs(-8) - Math.Abs(15), expr.Execute(), Delta);
        }

        [TestMethod]
        public void SqrtTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("sqrt 81 + sqrt(25) - sqrt 2 ");

            Assert.AreEqual(Math.Sqrt(81) + Math.Sqrt(25) - Math.Sqrt(2), expr.Execute(), Delta);
        }

        [TestMethod]
        public void NegTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("-x -5 - -7- -sqrt(2)");
            const double x = 124;
            expr.SetVariableValue("x", x);

            Assert.AreEqual(-x - 5 - -7 - -Math.Sqrt(2), expr.Execute(), Delta);
        }

        [TestMethod]
        public void NegTest2()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("-(sqrt(x)) - 5 - -7");
            const double x = 124;
            expr.SetVariableValue("x", x);

            Assert.AreEqual(-(Math.Sqrt(x)) - 5 - -7, expr.Execute(), Delta);
        }

        [TestMethod]
        public void CeilTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("ceil (7.7) + ceil(-8.9) - ceil (7.1) ");

            Assert.AreEqual(Math.Ceiling(7.7) + Math.Ceiling(-8.9) - Math.Ceiling(7.1), expr.Execute(), Delta);
        }

        [TestMethod]
        public void FloorTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("floor (7.7) + floor(-8.9) - floor (7.1)");

            Assert.AreEqual(Math.Floor(7.7) + Math.Floor(-8.9) - Math.Floor(7.1), expr.Execute(), Delta);
        }

        [TestMethod]
        public void CosTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("cos __pi + cos(0) - cos -17 ");

            Assert.AreEqual(Math.Cos(Math.PI) + Math.Cos(0.0) - Math.Cos(-17.0), expr.Execute(), Delta);
        }

        [TestMethod]
        public void SinTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("sin __pi + sin(0) - sin -17 ");

            Assert.AreEqual(Math.Sin(Math.PI) + Math.Sin(0.0) - Math.Sin(-17.0), expr.Execute(), Delta);
        }

        [TestMethod]
        public void TanTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("tan (__pi) + tan(8) - tan 0");

            Assert.AreEqual(Math.Tan(Math.PI) + Math.Tan(8) - Math.Tan(0), expr.Execute(), Delta);
        }

        [TestMethod]
        public void CtanTest()
        {
            var expr = new ExpressionEvaluatorNet.ExpressionEvaluator("ctan (__pi/2) + ctan(6) - ctan (-__pi/2) ");

            Assert.AreEqual(1 / Math.Tan(Math.PI / 2) + 1 / Math.Tan(6) - 1 / Math.Tan(-Math.PI / 2), expr.Execute(), Delta);
        }
    }
}
