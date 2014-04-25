#Includes common configuration for all subdirectory .pro files.
# INCLUDEPATH += . ..
WARNINGS += -Wall


QT       += widgets opengl
QT       -= gui


TEMPLATE = lib
CONFIG += staticlib


# The following keeps the generated files at least somewhat separate 
# from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs
