#include "../qtgcanvas.h"
#include <QDebug>
#include <QFile>
#include <QMouseEvent>

#include "../qtgdrawer.h"


//QtGCanvas::QtGCanvas(size_t dritmsize, const QGLFormat& format, QWidget* parent)
//    : QGLWidget(format, parent)
//{

////    this->shaders = new QVector<ShaderBundle*>(10);
////    for (int i = 0; i < NUM_DQ; i++)
////        this->dqueues[i].set_draw_item_size(dritmsize);

//    this->frameno = 0;
//    this->current_shader_name = -1;
//}

//static inline void _kb_read(int t, uint8 jmin, uint8 trig, uint8 jmax, ctrl_frame_t* kbd)
//{
//    switch (t) {
//    case Qt::Key_Up:
//        kbd->joyx = jmax;
//        break;
//    case Qt::Key_Down:
//        kbd->joyx = jmin;
//        break;
//    case Qt::Key_Left:
//        kbd->joyy = jmax;
//        break;
//    case Qt::Key_Right:
//        kbd->joyy = jmin;
//        break;
//    case Qt::Key_Q:
//        kbd->ltrig = trig;
//        break;
//    case Qt::Key_W:
//        kbd->rtrig = trig;
//        break;
//    default:
//        break;
//    }
//}

void QtGCanvas::keyPressEvent(QKeyEvent *e){
    //    _kb_read(e->key(), 0, 255, 255, &kbd);
    //    if(e->key() == Qt::Key_Space)
    //        kbd.buttons |= B_A;

    //    if(e->key() == Qt::Key_Shift)
    //        kbd.buttons |= B_B;
    if(e->key() == Qt::Key_Escape){
        this->game->quit();
        this->close();
    }

}

void QtGCanvas::keyReleaseEvent(QKeyEvent *e){
    //    _kb_read(e->key(), 128, 0, 128, &kbd);
    //    if(e->key() == Qt::Key_Space)
    //        kbd.buttons &= ~B_A;

    //    if(e->key() == Qt::Key_Shift)
    //        kbd.buttons &= ~B_B;
}


QtGCanvas::QtGCanvas(QtGfxSource *agame, QGLFormat format, QWidget *parent) : QGLWidget(format, parent)
{
    this->game = agame;
    this->active_shader = 0xDEADBEEF;
    this->active_drawer = NULL;

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.setInterval(0);
    timer.start();
}

int QtGCanvas::set_shader(QtGShaderBundle *shader, QtGDrawer *owner){
    GLuint sdi = shader->program()->programId();
    if (this->active_shader != sdi){
        if (this->active_drawer != NULL)
            this->active_drawer->deactivate();
        this->active_drawer = owner;

        GLuint outp = this->active_shader;
        this->active_shader = sdi;
        //        if(!shader->program()->isLinked())
        //            qDebug() << "relinking " << shader->program()->link();
        //        this->glUseProgram(sdi);

        glUseProgram(sdi);
        //        qDebug() << "switched shader to: " << sdi;
        //        if (!shader->program()->bind()){
        //            qDebug() << "program binding error: " << shader->program()->log();
        //        }
        return outp;
    }
    return -1;
}

void QtGCanvas::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
    this->draggmode = true;
}

void QtGCanvas::mouseReleaseEvent(QMouseEvent *e)
{
    this->draggmode=false;
}

void QtGCanvas::mouseMoveEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(-diff.y(), -diff.x(), 0.0);

    //    // Accelerate angular speed relative to the length of the mouse sweep
    //    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = n;

    // Increase angular speed
    angularSpeed = n.length();
}
