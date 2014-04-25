#include "../qtgame.h"


QtGame::QtGame()
{



//    this->canvas = new QtGCanvas();
//    this->gamepad = new QtGamepad();
//    this->sound = new QtGSound();
}


void QtGame::init(QApplication *qapp, QtGCanvas *glcanv){
    this->app = qapp;
    this->canvas = glcanv;
}
