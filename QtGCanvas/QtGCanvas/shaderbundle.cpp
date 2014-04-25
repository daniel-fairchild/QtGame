#include "shaderbundle.h"




void ShaderBundle::_shader_add(const char* fname, QGLShader::ShaderTypeBit type){
    if (!this->program->addShaderFromSourceFile(type, QString::fromUtf8(fname))){
        qDebug() << "shader compile error: "<< fname << this->program->log();
    }
}


ShaderBundle::ShaderBundle(QGLContext* ctxt, const char *fragmentfn, const char *vertexfn, const char *geometryfn){

    this->context = ctxt;
    this->program = new QGLShaderProgram(this->context);
    this->fragmentfn = fragmentfn;
    this->vertexfn = vertexfn;
    this->geometryfn = geometryfn;

    _shader_add(vertexfn, QGLShader::Vertex);
    if (geometryfn != NULL){
        _shader_add(geometryfn, QGLShader::Geometry);
    }
    _shader_add(fragmentfn, QGLShader::Fragment);
    if (! this->program->link())
        qDebug() << "shader link error:" << fragmentfn << ": "<< this->program->log();
}

QGLShaderProgram *ShaderBundle::get_program()
{
    return this->program;
}




