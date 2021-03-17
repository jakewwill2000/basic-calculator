#include <QtTest>
#include "../basic-calculator/parser.h"

// add necessary includes here

class TestFormulaEvaluation : public QObject
{
    Q_OBJECT

public:
    TestFormulaEvaluation();
    ~TestFormulaEvaluation();

private slots:
    void testSimpleAddition();
    void testSimpleSubtraction();
    void testSimpleMultiplication();
    void testSimpleDivision();
    void testMultiOperatorAddition();
    void testMultiOperatorSubtraction();
    void testMultiOperatorMultiplication();
    void testMultiOperatorDivision();
    void testMixedOperatorExpressions();
    void testSimpleParentheses();
    void testComplexParentheses();
    void testParenthesesNoOperator();
    void testParenthesesMixNoOperator();
    void testParenthesesNoOperatorFollows();
    void testNegativeNumbersNoParentheses();
    void testNegativeNumbersWithParentheses();
    void testMultiplyNegativeNumbersNoParentheses();
    void testMultiplyNegativeNumbersWithParentheses();
    void testMultiplyNegativeNumbersWithParenthesesAndOperators();
};

TestFormulaEvaluation::TestFormulaEvaluation()
{

}

TestFormulaEvaluation::~TestFormulaEvaluation()
{

}

void TestFormulaEvaluation::testSimpleAddition()
{
    QString formula = "1 + 2";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 3.0);
}

void TestFormulaEvaluation::testSimpleSubtraction()
{
    QString formula = "1 - 2";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -1.0);
}

void TestFormulaEvaluation::testSimpleMultiplication()
{
    QString formula = "1 x 2";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 2.0);
}

void TestFormulaEvaluation::testSimpleDivision()
{
    QString formula = "9 / 3";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 3.0);
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

void TestFormulaEvaluation::testComplexParentheses()
{
    QString formula = "1 x 2.4 / (3.2 - 2) - 2 + 5.5 + 2.3 x (3 - 2)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 7.8);
}

void TestFormulaEvaluation::testParenthesesNoOperator()
{
    QString formula = "3 (4) (6)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 72);
}

void TestFormulaEvaluation::testParenthesesMixNoOperator()
{
    QString formula = "3 (4) (6) - 3 x 3 - (4 - 2)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 61);
}

void TestFormulaEvaluation::testParenthesesNoOperatorFollows()
{
    QString formula = "(3 - 6) 2";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -6);
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
    QString formula = "3 + -2 (-3 + 3 - 4)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -11);
}

void TestFormulaEvaluation::testMultiplyNegativeNumbersNoParentheses()
{
    QString formula = "-2 x -3 x - 1.5";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == -9);
}

void TestFormulaEvaluation::testMultiplyNegativeNumbersWithParentheses()
{
    QString formula = "(-2) (-8) (3)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 48);
}

void TestFormulaEvaluation::testMultiplyNegativeNumbersWithParenthesesAndOperators()
{
    QString formula = "(-2) (-8) x (3)";
    Parser parser = Parser(formula);
    double result = parser.evaluate();
    QVERIFY(result == 48);
}

QTEST_APPLESS_MAIN(TestFormulaEvaluation)

#include "tst_testformulaevaluation.moc"
