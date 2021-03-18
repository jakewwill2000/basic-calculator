#include <QtTest>
#include "../basic-calculator/parser.h"

class TestFormulaEvaluation : public QObject
{
    Q_OBJECT

public:
    TestFormulaEvaluation();
    ~TestFormulaEvaluation();

private slots:
    void testSingleNumber();
    void testSingleNegativeNumber();
    void testSimpleAddition();
    void testComplexAddition();
    void testSimpleSubtraction();
    void testComplexSubtraction();
    void testSimpleMultiplication();
    void testComplexMultiplication();
    void testComplexDivision();
    void testSimpleDivision();
    void testMultiOperatorAddition();
    void testMultiOperatorSubtraction();
    void testMultiOperatorMultiplication();
    void testMultiOperatorDivision();
    void testMixedOperatorExpressions();
    void testSimpleParentheses();
    void testOnlyParentheses();
    void testComplexParentheses();
    void testNegativeNumbersNoParentheses();
    void testNegativeNumbersWithParentheses();
    void testMultiplyNegativeNumbersNoParentheses();
    void testMultiplyNegativeNumbersWithParentheses();
    void testSimpleNestedParentheses();
    void testNestedParenthesesMultiOperator();
    void testNestedParenthesesNegativeNumbers();
    void testConsecutiveSequenceSum();
    void testDeepParentheses();
};

TestFormulaEvaluation::TestFormulaEvaluation()
{

}

TestFormulaEvaluation::~TestFormulaEvaluation()
{

}

void TestFormulaEvaluation::testSingleNumber() {
    QString formula = "1";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 1);
}

void TestFormulaEvaluation::testSingleNegativeNumber()
{
    QString formula = "-1";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -1);
}

void TestFormulaEvaluation::testSimpleAddition()
{
    QString formula = "1 + 2";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 3.0);
}

void TestFormulaEvaluation::testComplexAddition()
{
    QString formula = "1 + 3 + 1.2 + 12 + 9 + 10 + 101923.6372";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 101959.8372);
}

void TestFormulaEvaluation::testSimpleSubtraction()
{
    QString formula = "1 - 2";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -1.0);
}

void TestFormulaEvaluation::testComplexSubtraction()
{
    QString formula = "1 - 10 - 11 - 12.3 - 1253.2 - 3.1415 - 3";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -1291.6415);
}

void TestFormulaEvaluation::testSimpleMultiplication()
{
    QString formula = "1 x 2";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 2.0);
}

void TestFormulaEvaluation::testComplexMultiplication()
{
    QString formula = "1 x 2 x 3.3 x 3.4 x 121.33";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 2722.6452);
}

void TestFormulaEvaluation::testSimpleDivision()
{
    QString formula = "9 / 3";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 3.0);
}

void TestFormulaEvaluation::testComplexDivision()
{
    QString formula = "1024 / 2 / 4 / 8 / 16 / 5 / 5";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 0.04);
}

void TestFormulaEvaluation::testMultiOperatorAddition()
{
    QString formula = "1 + 2 + 3 + 4.2";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 10.2);
}

void TestFormulaEvaluation::testMultiOperatorSubtraction()
{
    QString formula = "10 - 5 - 5 - 3.4";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -3.4);
}

void TestFormulaEvaluation::testMultiOperatorMultiplication()
{
    QString formula = "4.2 x 3.1 x 2.0";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 26.04);
}

void TestFormulaEvaluation::testMultiOperatorDivision()
{
    QString formula = "48 / 2 / 3 / 2";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 4);
}

void TestFormulaEvaluation::testMixedOperatorExpressions()
{
    QString formula = "1 + 2.0 - 3.2 x 4.1 - 8.37 / 3.1 x 2.0 + 6.7";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -8.82);
}

void TestFormulaEvaluation::testSimpleParentheses()
{
    QString formula = "1 - (3 - 4)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 2);
}

void TestFormulaEvaluation::testOnlyParentheses()
{
    QString formula = "(1)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 1);
}

void TestFormulaEvaluation::testComplexParentheses()
{
    QString formula = "1 x 2.4 / (3.2 - 2) - 2 + 5.5 + 2.3 x (3 - 2)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 7.8);
}

void TestFormulaEvaluation::testNegativeNumbersNoParentheses()
{
    QString formula = "3 + -2 x 8 - 6 / 3";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -15);
}

void TestFormulaEvaluation::testNegativeNumbersWithParentheses()
{
    QString formula = "3 + -2 x (-3 + 3 - 4)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 11);
}

void TestFormulaEvaluation::testMultiplyNegativeNumbersNoParentheses()
{
    QString formula = "-2 x -3 x -1.5";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -9);
}

void TestFormulaEvaluation::testMultiplyNegativeNumbersWithParentheses()
{
    QString formula = "(-2) x (-8) x (3)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 48);
}

void TestFormulaEvaluation::testSimpleNestedParentheses()
{
    QString formula = "1 + (2 + (1 + 2))";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 6);
}

void TestFormulaEvaluation::testNestedParenthesesMultiOperator()
{
    QString formula = "1 + 2 - 3 x (1 - 2 - (3 x 4 / 2 - 1))";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 21);
}

void TestFormulaEvaluation::testNestedParenthesesNegativeNumbers()
{
    QString formula = "1 - -2 + -3 x (-2 + 4 - -2 / (-2 + 2 + 4))";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -4.5);
}

void TestFormulaEvaluation::testConsecutiveSequenceSum()
{
    QString formula = "";

    for (size_t i = 0; i < 1000; i++) {
        formula += QString::number(i) + " + ";
    }

    formula += "1000";

    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 500500);
}

void TestFormulaEvaluation::testDeepParentheses()
{
    QString formula = "";

    for (size_t i = 0; i < 1000; i++) {
        formula += '(';
    }

    formula += "1 + 2 - 3 - 4 x 5 / 2";

    for (size_t i = 0; i < 1000; i++) {
        formula += ')';
    }

    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -10);
}

QTEST_APPLESS_MAIN(TestFormulaEvaluation)

#include "tst_testformulaevaluation.moc"
