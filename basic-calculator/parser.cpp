#include "parser.h"

Parser::Parser(QString expression) {
    this->expression = expression;
    this->index = 0;
    this->currentValue = 0.0;
}

double Parser::evaluate() {
    double result = 0;

    QString currNum = "";
    QString lastNum = "0";

    QChar lastOp = '+';
    if (this->expression[0] == '-') {
        currNum = '-';
        this->index += 1;
    }

    while (this->index < (size_t) this->expression.length()) {
        QChar curr = this->expression[this->index];

        if (curr.isDigit() == true || curr == '.') {
            currNum += curr;
        } else if (curr == '(') {
            this->index += 1;
            currNum = QString::number(this->evaluate());
        } else if (curr == ')') {
            return result + this->applyOp(lastNum.toDouble(), currNum.toDouble(), lastOp);
        } else if (curr == ' ') {
            this->index += 1;
            continue;
        } else if (curr == '+' || curr == '-') {
            if (curr == '-' && this->expression[this->index + 1].isDigit()) {
                this->index += 1;
                currNum += '-';
                continue;
            }

            result += applyOp(lastNum.toDouble(), currNum.toDouble(), lastOp);
            lastNum = QString::number(0);
            currNum = "";
            lastOp = curr;
        } else if (curr == 'x' || curr == '/') {
            if (lastOp == '+' || lastOp == '-') {
                result += lastNum.toDouble();
                lastNum = currNum;

                if (lastOp == '-') {
                    lastNum = QString::number(lastNum.toDouble() * -1);
                }
            } else {
                lastNum = QString::number(this->applyOp(lastNum.toDouble(), currNum.toDouble(), lastOp));
            }

            currNum = "";
            lastOp = curr;
        } else {
            abort();
        }

        this->index += 1;
    }

    QChar last = this->expression[this->expression.length() - 1];
    if (last.isDigit() || last == ')') {
        result += this->applyOp(lastNum.toDouble(), currNum.toDouble(), lastOp);
    }

    return result;
}

double Parser::applyOp(double num1, double num2, QChar op) {
    if (op == '+') {
        return num1 + num2;
    } else if (op == '-') {
        return num1 - num2;
    } else if (op == 'x') {
        return num1 * num2;
    } else if (op == '/') {
        return num1 / num2;
    }

    abort();
}
