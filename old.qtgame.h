#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include <QObject>
#include <QApplication>

class QtGame : public QObject
{
    Q_OBJECT
public:
    explicit QtGame(QObject *parent = 0);
    virtual void init(QApplication qapp, OGLCanvas oglcanv) = 0;
    virtual void update() = 0;
    virtual void quit();

signals:

public slots:

};

#endif // ABSTRACTGAME_H
