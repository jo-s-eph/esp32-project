#ifndef SPOTIFY_AUTH_H
#define SPOTIFY_AUTH_H

#include <Arduino.h>

String getCurrentPlay(String accessToken);
int addTrackToLiked(String accessToken, const char* trackUri);

#endif
