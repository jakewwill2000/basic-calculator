#ifndef PARSER_H
#define PARSER_H

#include <QMainWindow>

/*
 * This is a custom parser class I have written to assist with evaluating
 * formula expressions. It takes in a QString representing an expression,
 * and exposes the evaluate() function which returns a single decimal
 * value representing the expressions value. evaluate() assumes that the
 * formula is valid.
 */
class Parser {
public:
    QString expression;
    size_t index;
    double currentValue;
    Parser(QString expression);
    double evaluate();
};

#endif // PARSER_H
