#include "../qtgshaderbundle.h"

void ShaderBundle::_shader_add(const char* fname, QGLShader::ShaderTypeBit type){
    if (!this->prog->addShaderFromSourceFile(type, QString::fromUtf8(fname))){
        qDebug() << "shader compile error: "<< fname << this->prog->log();
    }
}


ShaderBundle::ShaderBundle(QGLContext* ctxt, const char *fragmentfn, const char *vertexfn, const char *geometryfn){

    this->context = ctxt;
    this->prog = new QGLShaderProgram(this->context);
    this->fragmentfn = fragmentfn;
    this->vertexfn = vertexfn;
    this->geometryfn = geometryfn;

    _shader_add(vertexfn, QGLShader::Vertex);
    if (geometryfn != NULL){
        _shader_add(geometryfn, QGLShader::Geometry);
    }
    _shader_add(fragmentfn, QGLShader::Fragment);
    if (! this->prog->link())
        qDebug() << "shader link error:" << fragmentfn << ": "<< this->prog->log();
}

QGLShaderProgram *ShaderBundle::program()
{
    return this->prog;
}




