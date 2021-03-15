#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <string.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    double evaluateExpression(QString expression);


private slots:
    void numPressed();
    void clearPressed();
    void decimalPressed();
    void operatorPressed();
    void equalsPressed();
    void parenPressed();
};
#endif // CALCULATOR_H
