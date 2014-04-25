#ifndef SHADERBUNDLE_H
#define SHADERBUNDLE_H

#include <QString>
#include <QtOpenGL/QGLShaderProgram>

class ShaderBundle
{
public:
    ShaderBundle(QGLContext* ctxt, const char* fragmentfn, const char* vertexfn, const char* geometryfn=NULL);
    QGLShaderProgram* get_program();

protected:
    const char* fragmentfn;
    const char* geometryfn;
    const char* vertexfn;
    QGLShaderProgram* program;
    QGLContext* context;

private:
    void _shader_add(const char* fname, QGLShader::ShaderTypeBit type);
};

#endif // SHADERBUNDLE_H
