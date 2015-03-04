#include "tagreader.h"

TagReader::TagReader(QObject *parent) :
    QObject(parent),
    m_cancel(false)
{
}

void TagReader::setList(QList<MediaInfo *> list)
{
    m_queue = list;
}

//void TagReader::readTags(MediaInfo *info)
//{
//    QUrl url = info->url();

//    if (!url.isLocalFile())
//        return;

//    QString path = url.toLocalFile();

//    QFileInfo fileInfo(path);
//    QString extension = fileInfo.suffix();

//    QString artist;
//    QString album;
//    QString title;

//    if (extension == "mp3") {
//        TagLib::MPEG::File *mpegFile = new TagLib::MPEG::File(path.toStdWString().c_str());
//        if (!mpegFile->isValid())
//            return;

//        TagLib::ID3v1::Tag *id3v1 = 0;
//        TagLib::ID3v2::Tag *id3v2 = 0;

//        TagLib::Tag *tag = mpegFile->tag();
//        if (tag == 0)
//            return;

//        id3v1 = mpegFile->ID3v1Tag();
//        id3v2 = mpegFile->ID3v2Tag();

//        artist = toQString(tag->artist(), id3v1, id3v2);
//        title = toQString(tag->title(), id3v1, id3v2);
//        album = toQString(tag->album(), id3v1, id3v2);

//        delete mpegFile;
//    } else {
//        TagLib::FileRef file(path.toStdWString().c_str());
//        if (file.isNull())
//            return;

//        TagLib::Tag *tag = file.tag();
//        if (tag == 0)
//            return;

//        artist = toQString(tag->artist());
//        title = toQString(tag->title());
//        album = toQString(tag->album());
//    }

//    info->setAlbum(album);
//    info->setArtist(artist);
//    info->setTitle(title);
//}

void TagReader::readTagsBASS(MediaInfo *info)
{
    QUrl url = info->url();

    if (!url.isLocalFile())
        return;

    QString path = url.toLocalFile();

    QFileInfo fileInfo(path);
    QString extension = fileInfo.suffix();

    QString artist;
    QString album;
    QString title;

    BASS::LocalStream bs(url, this);
    HSTREAM s = bs.handler();

    //qDebug() << TAGS_Read(s, "%IFV1(%TRCK,%TRCK. )%IFV2(%ARTI,%ICAP(%ARTI),no artist) - %IFV2(%TITL,%ICAP(%TITL) -,no title -)%IFV1(%ALBM, %IUPC(%ALBM))%IFV1(%YEAR, %(%YEAR%))");
    artist = TAGS_Read(s, "%UTF8(%ARTI)");
    album = TAGS_Read(s, "%UTF8(%ALBM)");
    title = TAGS_Read(s, "%UTF8(%TITL)");

    artist = artist.simplified();
    album = album.simplified();
    title = title.simplified();
    /*if (extension == "mp3") {
        BASS::LocalStream bs(url, this);
        HSTREAM s = bs.handler();
        TAG_ID3 *tag = (TAG_ID3*) BASS_ChannelGetTags(s, BASS_TAG_ID3);

        if (tag != NULL) {
            QTextCodec *codec = QTextCodec::codecForLocale();
            artist = codec->toUnicode(tag->artist).simplified();
            album = codec->toUnicode(tag->album).simplified();
            title = codec->toUnicode(tag->title).simplified();
        }

        qDebug() << artist;
        qDebug() << album;
        qDebug() << title;

        const char *tagid3v2 = BASS_ChannelGetTags(s, BASS_TAG_ID3V2);
        parseID3V2(tagid3v2);
        if (tagid3v2 != NULL) {
            qDebug() << tagid3v2;
        }

        if (BASS_ErrorGetCode() == BASS_ERROR_HANDLE)
            qDebug() << "wrong handler";
        if (BASS_ErrorGetCode() == BASS_ERROR_NOTAVAIL)
            qDebug() << "tag not available";

//        TAG_ID3 tag = (TAG_ID3) tags;
//        if (tag != NULL) {
//            artist = tag.artist;
//            album = tag.album;
//            title = tag.title;
//            qDebug() << "readTagsBass" << artist << album << title;
//        } else {
//
//        }
    }
    */

    info->setAlbum(album);
    info->setArtist(artist);
    info->setTitle(title);
}

/*void TagReader::parseID3V2(const char *id3v2)
{
    if (id3v2 == NULL)
        return;

    if (id3v2[0] == 'I'
        && id3v2[1] == 'D'
        && id3v2[2] == '3') {
        char * header = new char[10];
        memcpy(header, id3v2, 10);
        qDebug() << header << "version: 2" << (int) id3v2[3] << (int) id3v2[4];

        delete header;
    }
}
*/
//QString TagReader::toQString(const TagLib::String &str, TagLib::ID3v1::Tag *id3v1, TagLib::ID3v2::Tag *id3v2)
//{
//    if (str.isNull() || str.isEmpty())
//        return QString();

//    if (str.isLatin1() && str.isAscii())
//        //return QString::fromLatin1(str.to8Bit().c_str());
//        return QString::fromLatin1(str.toCString());

//    if (str.isLatin1() && !str.isAscii()) {
//        const char *raw = str.toCString();
//        QTextCodec *codec = 0;

//        bool id3v1Empty = true;
//        bool id3v2Empty = true;

//        if (id3v1 != 0)
//            id3v1Empty = id3v1->isEmpty();
//        if (id3v2 !=0)
//            id3v2Empty = id3v2->isEmpty();

//        //qDebug() << str.to8Bit().c_str() << id3v1Empty << id3v2Empty;

//        if (((id3v1Empty == false) && id3v2Empty)
//                || (id3v1Empty && (id3v2Empty == false))
//                || (id3v1Empty == false && id3v2Empty == false)) {
//            codec = QTextCodec::codecForLocale();
//            return codec->toUnicode(raw);
//        }

//        codec = QTextCodec::codecForName("ISO-8859-1");
//        return codec->toUnicode(raw);
//    }

//    //return QString::fromStdWString(str.toWString());
//    return TStringToQString(str);
//}

void TagReader::process()
{
    m_cancel = false;
    MediaInfo *info = 0;

    for (int i=0; i<m_queue.count() && !m_cancel; ++i) {
        info = m_queue.at(i);
        //readTags(info);
        readTagsBASS(info);
        emit processed(info);
    }

    emit finished();
}

void TagReader::cancel()
{
    m_cancel = true;
}
