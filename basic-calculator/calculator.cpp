#include "calculator.h"
#include "ui_calculator.h"

// Used to represent the current value being displayed
QString currValue = "";

// Used to denote whether we have a balanced parentheses expression
size_t parensCount = 0;

// We use these values to constrain the maximum length of a number
const size_t MAX_NUM_LENGTH = 16;
size_t currNumLen = 0;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    // Initially set the display value to 0.0
    ui->display->setText(QString::number(0.0));

    // Connect all of the numeric buttons to the numPressed() slot
    QPushButton *numButtons[10];

    for (size_t i = 0; i < 10; i++) {
        QString name = "button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(name);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(numPressed()));
    }

    // Connect the clear button to the clearPressed() slot
    QPushButton *clearButton = Calculator::findChild<QPushButton *>("buttonClear");
    connect(clearButton, SIGNAL(released()), this, SLOT(clearPressed()));

    // Connect the dot button to the decimalPressed() slot
    QPushButton *decimalButton = Calculator::findChild<QPushButton *>("buttonDot");
    connect(decimalButton, SIGNAL(released()), this, SLOT(decimalPressed()));

    // Connect the operator buttons to the operatorPressed() slot
    QString buttonNames[4] = {"buttonAdd", "buttonSub", "buttonDiv", "buttonMul"};

    for (QString name: buttonNames) {
        QPushButton *newButton = Calculator::findChild<QPushButton *>(name);
        connect(newButton, SIGNAL(released()), this, SLOT(operatorPressed()));
    }

    // Connect the equal button to the equalsPressed() slot
    QPushButton *equalsButton = Calculator::findChild<QPushButton *>("equalsButton");
    connect(equalsButton, SIGNAL(released()), this, SLOT(equalsPressed()));

    // Connect the parentheses buttons to the parensPressed() slot
    QString parenNames[2] = {"parenOpenButton", "parenClosedButton"};

    for (QString name: parenNames) {
        QPushButton *newButton = Calculator::findChild<QPushButton *>(name);
        connect(newButton, SIGNAL(released()), this, SLOT(parenPressed()));
    }
}

Calculator::~Calculator()
{
    delete ui;
}

/*
 * When a number is pressed, we want to add it on to the current
 * number that is being displayed. We also increment the
 * currNumLen.
 */
void Calculator::numPressed() {
    // We want to constrain numbers to 16 digits for now
    if (currNumLen >= MAX_NUM_LENGTH) {
        return;
    }

    QPushButton *button = (QPushButton *) sender();
    QString newValue = button->text();

    currValue += newValue;

    // We have added one more digit onto the current number
    currNumLen += 1;

    ui->display->setText(currValue);
}

/*
 * When the clear button is pressed, set the displayed value to 0.0.
 * Also reset the currNumLen to zero
 */
void Calculator::clearPressed() {
    currValue = "";
    currNumLen = 0;

    ui->display->setText(currValue);
}

/*
 * When the decimal button is pressed, add a "." to the current value
 */
void Calculator::decimalPressed() {
    currValue += ".";
}

/*
 * When the operator buttons are pressed, add them to the current value
 * that is being displayed, with the necessary spaces. Also set the
 * currNumLen to zero, as we are no longer building up a number.
 */
void Calculator::operatorPressed() {
    QPushButton *button = (QPushButton *) sender();
    QString op = button->text();

    // We don't want to allow two operators to be placed in succession. This
    // will prevent expressions like 1 ++ 3 from occuring. The operator will
    // always be the second to last character in the current expression, so
    // we just verify that this character is not an operator before proceeding.
    QChar lastChar = currValue[currValue.length() - 2];
    QChar operators[] = {'+', '-', 'x', '/'};

    if (std::find(std::begin(operators), std::end(operators), lastChar) != std::end(operators)) {
        return;
    }

    currValue += " " + op + " ";
    currNumLen = 0;

    ui->display->setText(currValue);
}

/*
 * When the equals button is pressed, we want to evaluate the current
 * expression and set the displayed text to this value.
 */
void Calculator::equalsPressed() {
    double result = evaluateExpression(currValue);

    // Set the displayed text to the result, constrained to 16 digits
    ui->display->setText(QString::number(result, 'g', 16));
}

/*
 * When a parentheses button is pressed, we want to add the relevent
 * parentheses onto our current expression. If adding the parentheses
 * will make the expression invalid, then we return immediately.
 */
void Calculator::parenPressed() {
    QPushButton *button = (QPushButton *) sender();
    QString paren = button->text();

    // We don't want to permit an unbalanced expression
    if (paren == ")" && parensCount == 0) {
        return;
    }

    // Update the parentheses count depending on which type it is
    if (paren == "(") {
        parensCount += 1;
    } else if (paren == ")") {
        parensCount -= 1;
    }

    currValue += paren;
    ui->display->setText(currValue);
}

/*
 * TODO
 */
double Calculator::evaluateExpression(QString expression) {
    (void) expression;
    return -6.0;
}