#ifndef TEMPO_H
#define TEMPO_H

#ifndef _WIN32
#define _POSIX_C_SOURCE 199309L
#endif

#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

double obterTempo();

#endif