#include "qtgsound.h"
#include "qdebug.h"

QtGSound::QtGSound(QObject* parent)
{
    _parent = parent;
}

int QtGSound::load(const char *fname)
{
    QSoundEffect* tmp = new QSoundEffect(_parent);

    QUrl qrl = QUrl::fromLocalFile(fname);
    tmp->setSource(qrl);
    tmp->setLoopCount(1);
    _sfx.append(tmp);

    tmp->setVolume(1.0f);
    tmp->setLoopCount(1);
    tmp->stop();
    //    while (tmp.status() != QSoundEffect::Ready)
    //        qDebug() << tmp->status();

    return _sfx.length()-1;
}

void QtGSound::play(int ref, float volume, float pos)
{
    QSoundEffect* tmp = _sfx[ref];
    tmp->setVolume(volume);
    tmp->play();
}
