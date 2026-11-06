#include "tempo.h"

double obterTempo() {
#ifdef _WIN32

    LARGE_INTEGER frequencia;
    LARGE_INTEGER tempo;

    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&tempo);

    return (double)tempo.QuadPart / frequencia.QuadPart;

#else

    struct timespec tempo;

    clock_gettime(CLOCK_MONOTONIC, &tempo);

    return tempo.tv_sec + tempo.tv_nsec / 1000000000.0;

#endif
}