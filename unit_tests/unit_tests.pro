QT += testlib
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += ../basic-calculator/
DEPENDPATH += $${INCLUDEPATH}

TEMPLATE = app

# I have not found a good way to link the two subprojects together.
# This method of including all the necessary .h, .cpp, and .ui files
# works, but it essentially causes the basic-calculator project to
# be built twice. For a small project like this it is inconsequential,
# but will dramatically increase build times for larger projects.

SOURCES +=  tst_testformulaevaluation.cpp \
            ../basic-calculator/parser.cpp

HEADERS += ../basic-calculator/parser.h
