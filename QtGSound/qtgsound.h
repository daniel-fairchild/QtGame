#ifndef QTGSOUND_H
#define QTGSOUND_H

#include <qlist.h>
#include <QSoundEffect>
#include <QObject>

class QtGSound
{

public:
    QtGSound(QObject* parent = 0);

    int load(const char* fname);

    void play(int ref, float volume, float pos);



private:
    QList<QSoundEffect*> _sfx;
    QObject* _parent;
};

#endif // QTGSOUND_H
