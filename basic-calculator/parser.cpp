#include "parser.h"

/*
 * Construct an instance of a parser from a formula
 */
Parser::Parser(QString expression) {
    this->expression = expression;
    this->index = 0;
    this->currentValue = 0.0;
}

/*
 * This function returns a double representing the evaluated value of
 * the formula associated with this parser. The algorithm is not
 * challenging to understand, but a bit tricky to implement. The function
 * assumes that formulas are given in the correct format.
 *
 * A high level overview of this algorithm is as follows. Take as input
 * a formula consisting of digits, operators, and parentheses. We are
 * iterating over the entire formula - any expressions in parentheses
 * are evaluated recursively, and a pointer to the current location in
 * the formula is updated accordingly. We keep track of the 'last'
 * number encountered (usually the second to last) and the 'current'
 * number encountered (usually the last). We leverage the fact that
 * for an expression a + b, we can simply add a to a running total
 * because it has no impact on the following expression due to operator
 * precedence. Similarly, in something like a x b, we can combine
 * a x b into a single number, because nothing will take a higher
 * priority than multiplication (or division). See the inline comments
 * below for more details.
 *
 * This function is not optimized for efficiency, and does not need
 * to be because expressions long enough to cause significant slowdowns
 * are extremely unlikely to occur.
 */
double Parser::evaluate() {
    // Our running total of the result
    double result = 0;

    // We keep track of the second to last and last numbers we have
    // encountered
    QString currNum = "";
    QString lastNum = "0";

    // We can start our expression off with 0 + without changing anything,
    // and if the first character is a '-', we simply start off currNum
    // as negative.
    QChar lastOp = '+';
    if (this->expression[0] == '-') {
        currNum = '-';
        this->index += 1;
    }

    while (this->index < (size_t) this->expression.length()) {
        // The current character we are processing in the expression
        QChar curr = this->expression[this->index];

        if (curr.isDigit() == true || curr == '.') {
            // If we are processing a digit or a period, then we are building
            // up the current number to process.
            currNum += curr;
        } else if (curr == '(') {
            // If we process an opening parentheses, we recursively evalute the
            // contents of the parentheses. Note that index here is defined in the
            // scope of the class, not the scope of this function, and will be
            // different after the recursive call.
            this->index += 1;
            currNum = QString::number(this->evaluate());
        } else if (curr == ')') {
            // If we encounter a closing parentheses, we return the current result
            // plus any last operation we need to apply. For the top level call of
            // function, this will never occur in a balanced parentheses expression.
            return result + this->applyOp(lastNum.toDouble(), currNum.toDouble(), lastOp);
        } else if (curr == ' ') {
            // Skip over spaces, we don't care about them
            this->index += 1;
            continue;
        } else if (curr == '+' || curr == '-') {
            // If the next character is a digit (not a space), then this '-' represents
            // a negative number, not subtraction. Handle this accordingly.
            if (curr == '-' && this->expression[this->index + 1].isDigit()) {
                this->index += 1;
                currNum += '-';
                continue;
            }

            // Alternatively, we are dealing with addition or subtraction. Add the last
            // number onto our running result, as it is irrelevent to future calculations.
            // Set lastNum to the current number, and start off a new current number as
            // an empty string.
            result += applyOp(lastNum.toDouble(), currNum.toDouble(), lastOp);
            lastNum = QString::number(0);
            currNum = "";
            lastOp = curr;
        } else if (curr == 'x' || curr == '/') {
            if (lastOp == '+' || lastOp == '-') {
                // If the last operator was addition or subtraction, we can add the
                // lastNum to our running total because it no longer matters.
                result += lastNum.toDouble();
                lastNum = currNum;

                // If the last operator was subtraction, then we make sure to negate
                // the new lastNum. Because - a x b = (-a) x b, this does not affect
                // our final result.
                if (lastOp == '-') {
                    lastNum = QString::number(lastNum.toDouble() * -1);
                }
            } else {
                // If the last operator was multiplication or division, we can combine
                // the last two numbers using the last operator.
                lastNum = QString::number(this->applyOp(lastNum.toDouble(), currNum.toDouble(), lastOp));
            }

            // In both cases, we set the currNum to an empty string and lastOp to the
            // operator that we just processed
            currNum = "";
            lastOp = curr;
        } else {
            // Very *ungracefully* abort from the program if we encounter any invalid
            // characters
            abort();
        }

        // Skip to the next index in our expression
        this->index += 1;
    }

    // At the very end, we might need to add in our last two numbers if they haven't already
    // been processed
    QChar last = this->expression[this->expression.length() - 1];
    if (last.isDigit() || last == ')') {
        result += this->applyOp(lastNum.toDouble(), currNum.toDouble(), lastOp);
    }

    // Return the final result.
    return result;
}

/*
 * This is a helper function to take two doubles and apply a given operator to them
 */
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
