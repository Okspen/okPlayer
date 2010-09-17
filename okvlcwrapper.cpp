#include "okvlcwrapper.h"

okVLCWrapper::okVLCWrapper()
{
	const char * const vlc_args[] = {
				   "-I", "dummy", /* Don't use any interface */
				   "--ignore-config", /* Don't use VLC's config */
                   "--plugin-path=plugins",
                   "--novideo"};


	/* Load the VLC engine */
    inst = libvlc_new (5, vlc_args);

	/* Create a media player playing environement */
	player = libvlc_media_player_new(inst);
	currentFile = 0;

	fileSet = false;

	timer.setInterval(500);
	timer.start();
	connect(&timer, SIGNAL(timeout()), this, SLOT(emitTick()));
}

okVLCWrapper::~okVLCWrapper()
{
	/* Stop playing */
	libvlc_media_player_stop(player);
	if(currentFile != 0) libvlc_media_release(currentFile);
	/* Free the media_player */
	libvlc_media_player_release(player);

	libvlc_release(inst);
}

void okVLCWrapper::setFile(const QString &path)
{
    if((filePath == path) || !QFile::exists(path)) return;
    if(currentFile != 0) libvlc_media_release(currentFile);

    currentFile = libvlc_media_new_path(inst, path.toUtf8().data());
    libvlc_media_player_set_media(player, currentFile);

	fileSet = true;
}

void okVLCWrapper::play()
{
	libvlc_media_player_play(player);
}

void okVLCWrapper::pause()
{
	libvlc_media_player_pause(player);
}

void okVLCWrapper::stop()
{
	libvlc_media_player_stop(player);
}

void okVLCWrapper::setVolume(int newVol)
{
	libvlc_audio_set_volume(player, newVol);
}

void okVLCWrapper::setPosition(int newPos)
{
	libvlc_media_player_set_position(player, newPos*0.001);
}

int okVLCWrapper::getVolume()
{
	return libvlc_audio_get_volume(player);
}

void okVLCWrapper::emitTick()
{
	emit tick();
	if(libvlc_media_player_get_state(player) == libvlc_Ended)
	{
		emit finished();
	}
}

qint64 okVLCWrapper::getLength()
{
    return libvlc_media_player_get_length(player);
}

double okVLCWrapper::getPosition()
{
	return libvlc_media_player_get_position(player);
}

bool okVLCWrapper::isPlaying()
{
	return libvlc_media_player_is_playing(player);
}

bool okVLCWrapper::isPaused()
{
	return (libvlc_media_player_get_state(player) == libvlc_Paused);
}

bool okVLCWrapper::isStopped()
{
	return (libvlc_media_player_get_state(player) == libvlc_Paused);
}

bool okVLCWrapper::isEnded()
{
	return (libvlc_media_player_get_state(player) == libvlc_Ended);
}

bool okVLCWrapper::isFileSet()
{
	return fileSet;
}
