using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Feel.Test
{
    [TestClass]
    public class TernaryOperatorTest
    {
        [TestMethod]
        public void Choice()
        {
            var expr = new ExpressionEvaluator("choice(i, nonZero, zero)");

            expr.SetVariableValue("zero", 10);
            expr.SetVariableValue("nonZero", 11);

            expr.SetVariableValue("i", -1);
            Assert.AreEqual(11, expr.Execute());

            expr.SetVariableValue("i", 0);
            Assert.AreEqual(10, expr.Execute());

            expr.SetVariableValue("i", 1);
            Assert.AreEqual(11, expr.Execute());
        }

        [TestMethod]
        public void Choice2()
        {
            var expr = new ExpressionEvaluator("choice(a + 10 <= b - 20, 1, 0)");

            expr.SetVariableValue("a", -20);
            expr.SetVariableValue("b", 30);
            Assert.AreEqual(1, expr.Execute());

            expr.SetVariableValue("a", 20);
            expr.SetVariableValue("b", 30);
            Assert.AreEqual(0, expr.Execute());

            expr.SetVariableValue("a", 0);
            expr.SetVariableValue("b", 40);
            Assert.AreEqual(1, expr.Execute());
        }

        [TestMethod]
        public void CommaTest()
        {
            Assert.AreEqual(1, new ExpressionEvaluator("choice(-1^2, 1, 0)").Execute());

            Assert.AreEqual(-1, new ExpressionEvaluator("choice(-1^2, -1, 0)").Execute());

            Assert.AreEqual(-1, new ExpressionEvaluator("choice(-(1^2), -1, 0)").Execute());

            Assert.AreEqual(0, new ExpressionEvaluator("choice(-1 - -(1^2), -1, 0)").Execute());
        }
    }
}