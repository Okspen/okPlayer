#ifndef LOCALSTREAM_H
#define LOCALSTREAM_H

#include "stream.h"

namespace BASS {
class LocalStream : public Stream
{
    Q_OBJECT
public:
    LocalStream(const QUrl &url, QObject *parent);
    ~LocalStream();

private:
    QFile   m_audioData;

    bool prepare();
    static void CALLBACK fileClose(void *user);
    static QWORD CALLBACK fileLen(void *user);
    static DWORD CALLBACK fileRead(void *buffer, DWORD length, void *user);
    static BOOL CALLBACK fileSeek(QWORD offset, void *user);
};
}

#endif // LOCALSTREAM_H
