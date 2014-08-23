#ifndef SHADERBUNDLE_H
#define SHADERBUNDLE_H

#include <QString>
#include <QtOpenGL/QGLShaderProgram>

class QtGShaderBundle
{
public:
    QtGShaderBundle(const char* fragmentfn,
                    const char* vertexfn,
                    const char* geometryfn=NULL);

    QGLShaderProgram* program();

    bool compile(QGLContext* context);

protected:
    const char* fragmentfn;
    const char* geometryfn;
    const char* vertexfn;
    QGLShaderProgram* prog;

private:
};

#endif // SHADERBUNDLE_H
