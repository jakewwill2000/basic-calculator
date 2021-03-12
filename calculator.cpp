#include "calculator.h"
#include "ui_calculator.h"

// Used to represent the current value being displayed
QString currValue = "";

// Indicator variable denoting whether currValue is a decimal. We need this
// because adding new digits is handled differently before and after the
// decimal point.
bool afterDecimal = false;

// Represents the current digit (after the decimal point). This is used when
// adding new digits onto the current value displayed.
int digit = 0;

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
}

Calculator::~Calculator()
{
    delete ui;
}

/*
 * When a number is pressed, we want to add it on to the current
 * number that is being displayed. If the current number is 0, then
 * we just set the display number to the number that is pressed.
 */
void Calculator::numPressed() {
    // We want to constrain numbers to 16 digits for now
    if (currValue.length() >= 16) {
        return;
    }

    QPushButton *button = (QPushButton *) sender();
    QString newValue = button->text();

    currValue += newValue;

    ui->display->setText(currValue);
}

/*
 * When the clear button is pressed, set the displayed value to 0.0
 */
void Calculator::clearPressed() {
    currValue = "";

    ui->display->setText(currValue);
}

/*
 * When the decimal button is pressed, toggle the afterDecimal indicator
 * variable. The other functions should then handle their respective cases
 * accordingly.
 */
void Calculator::decimalPressed() {
    currValue += ".";
}
