#include "qtgshaderbundle.h"
#include <locale.h>

#include <QtCore/QFile>
#include <QGLShader>

QtGShaderBundle::QtGShaderBundle(const char *fragmentfn, const char *vertexfn, const char *geometryfn){

    this->fragmentfn = fragmentfn;
    this->vertexfn = vertexfn;
    this->geometryfn = geometryfn;
    this->prog = NULL;
}

QGLShaderProgram *QtGShaderBundle::program(){
    return this->prog;
}

static inline QString _readfile(const char* fname){
    QString fn = QString::fromUtf8(fname);
    QFile file(fn);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Could not open " << fn;
        return QString("");
    }
    QTextStream in(&file);
    return in.readAll();
}

static inline bool _shader_add(const char* fname,
                               QGLShader::ShaderTypeBit type,
                               QGLShaderProgram* prog){


#ifdef GL_ES_VERSION_2_0
    QString shdsrc("#version 100\n\nprecision highp float;");
#else
    QString shdsrc("#version 120\n");
#endif
    shdsrc.append(_readfile(fname));
    if (!prog->addShaderFromSourceCode(type, shdsrc)){
        qDebug() << "shader compile error: "<< fname << prog->log();
        return false;
    }
    return true;
}

bool QtGShaderBundle::compile(QGLContext* context){
    // Override system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    //    if (this->prog != NULL){
    //        this->prog->release();
    //        delete this->prog;
    //    }

    this->prog = new QGLShaderProgram(context);

    if (!_shader_add(vertexfn, QGLShader::Vertex, this->prog))
        return false;

    if (geometryfn != NULL){
        if (!_shader_add(geometryfn, QGLShader::Geometry, this->prog))
            return false;
    }
    if (!_shader_add(fragmentfn, QGLShader::Fragment, this->prog))
        return false;

    if (!this->prog->link()){
        qDebug() << "shader link error:" << fragmentfn << ": "<< this->prog->log();
        return false;
    }

    if (!this->prog->bind()){
        qDebug() << "shader bind error:" << fragmentfn << ": "<< this->prog->log();
        return false;
    }
    // Restore system locale
    setlocale(LC_ALL, "");

    return true;
}
