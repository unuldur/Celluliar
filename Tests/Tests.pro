QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testhashlife.cpp\
            ../App/TreeNode.cpp\
            ../App/TreeUniverse.cpp\

HEADERS +=  ../App/TreeNode.h\
            ../App/TreeUniverse.h\
