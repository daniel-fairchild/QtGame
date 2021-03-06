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

    if(e->key() == Qt::Key_R){
        this->rotationAxis = QVector3D(0,0,0);
        this->angularSpeed = 0;
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

void QtGCanvas::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
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

QtGCanvas::~QtGCanvas()
{
    delete queman;
    delete gfx_src;
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

int QtGCanvas::pix_width()
{
    return this->width() * devicePixelRatio();
}

int QtGCanvas::pix_height(){
    return this->height() * devicePixelRatio();
}

#ifndef GL_TABLE_TOO_LARGE
#define GL_TABLE_TOO_LARGE                0x8031
#endif
#ifndef GL_INVALID_FRAMEBUFFER_OPERATION
#define GL_INVALID_FRAMEBUFFER_OPERATION                     0x0506
#endif

bool QtGCanvas::gl_error_test(const char *fname, int line){

    GLenum err = glGetError();
    if (err != GL_NO_ERROR){
        qDebug() << QString(fname)<< ":" << line;
        switch (err) {
        case GL_NO_ERROR:
            qDebug() << "GL_NO_ERROR";
            break;
        case GL_INVALID_ENUM:
            qDebug() << "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            qDebug() << "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            qDebug() << "GL_INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            qDebug() << "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            qDebug() << "GL_STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            qDebug() << "GL_OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            qDebug() << "GL_INVALID_FRAMEBUFFER_OPERATION​";
            break;
        case GL_TABLE_TOO_LARGE:
            qDebug() << "GL_TABLE_TOO_LARGE​";
            break;
        default:
            qDebug() << "UNKNOWN GL ERROR";
            break;
        }
        return true;
    }
    return false;
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
