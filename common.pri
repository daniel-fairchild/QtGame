#Includes common configuration for all subdirectory .pro files.
# INCLUDEPATH += . ..
WARNINGS += -Wall

TEMPLATE = lib
CONFIG += staticlib
#CONFIG += dll


# The following keeps the generated files at least somewhat separate 
# from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs
