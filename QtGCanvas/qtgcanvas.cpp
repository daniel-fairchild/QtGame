#include <QDebug>
#include <QFile>
#include <QMouseEvent>

#include "qtgdrawer.h"
#include "qtgcanvas.h"


void QtGCanvas::keyPressEvent(QKeyEvent *e){
    //    _kb_read(e->key(), 0, 255, 255, &kbd);
    //    if(e->key() == Qt::Key_Space)
    //        kbd.buttons |= B_A;

    //    if(e->key() == Qt::Key_Shift)
    //        kbd.buttons |= B_B;
    if(e->key() == Qt::Key_Escape){
        this->should_exit = true;
    }

}

void QtGCanvas::keyReleaseEvent(QKeyEvent *e){
    //    _kb_read(e->key(), 128, 0, 128, &kbd);
    //    if(e->key() == Qt::Key_Space)
    //        kbd.buttons &= ~B_A;

    //    if(e->key() == Qt::Key_Shift)
    //        kbd.buttons &= ~B_B;
}

void QtGCanvas::paintGL(){

    if (this->should_reset)
        this->_reset();

    if (this->should_exit){
        this->gfx_src->quit();
        this->close();
        return;
    }
    gRender();
}

QtGCanvas::QtGCanvas(QtGfxSource *agame, QGLFormat *format, QWidget *parent) : QGLWidget(parent)
{
    if (format == NULL){
        QGLFormat glFormat;
        glFormat.setDoubleBuffer(true);
        glFormat.setSwapInterval(1);
        glFormat.setSampleBuffers(false);
        this->setFormat(glFormat);
    }
    else {
        const QGLFormat tf = *format;
        this->setFormat(tf);
    }

    this->gfx_src = agame;
    this->active_shader = 0xDEADBEEF;
    this->active_drawer = NULL;

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.setInterval(0);
    timer.start();

    this->should_reset = false;
    this->should_exit = false;
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

static inline float _suborto(float world, int scrnpix, int mdlpix){
    //        return 2.0* mdlpix / (world * scrnpix);
    return 2.0* mdlpix / (world * scrnpix);
}

QVector2D QtGCanvas::ortoPixProj(ortoPixProj_t *proj)
{
    return QVector2D (
                _suborto(proj->coord_width, this->width(), proj->pix_width),
                _suborto(proj->coord_height, this->height(), proj->pix_height));
}

int QtGCanvas::pix_width()
{
    return this->width() * devicePixelRatio();
}

int QtGCanvas::pix_height()
{
    return this->height() * devicePixelRatio();
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
