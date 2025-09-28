#pragma once

#include <chrono>
#include <sys/time.h>
#include <time.h>

class Time
{
public:
  static time_t milliseconds()
  {
    struct timeval timeNow;
    gettimeofday(&timeNow, NULL);
    return (timeNow.tv_sec * 1000) + (timeNow.tv_usec / 1000);
  }
};