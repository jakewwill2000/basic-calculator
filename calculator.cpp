#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    // Connect all of the numeric buttons to the numPressed() slot
    ui->display->setText(QString::number(0.0));
    QPushButton *numButtons[10];

    for (size_t i = 0; i < 10; i++) {
        QString name = "button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(name);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(numPressed()));
    }

    // Connect the clear button to the clearPressed() slot
    QPushButton *clearButton = Calculator::findChild<QPushButton *>("buttonClear");
    connect(clearButton, SIGNAL(released()), this, SLOT(clearPressed()));
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
    QPushButton *button = (QPushButton *) sender();
    QString buttonValue = button->text();
    QString displayValue = ui->display->text();

    if (displayValue.toDouble() == 0) {
        ui->display->setText(buttonValue);
    } else {
        ui->display->setText(displayValue + buttonValue);
    }
}

/*
 * When the clear button is pressed, set the displayed value to 0.0
 */
void Calculator::clearPressed() {
    ui->display->setText("0.0");
}
