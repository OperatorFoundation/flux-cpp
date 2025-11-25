//
// Created by Dr. Brandon Wiley on 11/24/25.
//

#ifndef ONDA_MACOS_CLOCK_H
#define ONDA_MACOS_CLOCK_H


#include <clock.h>
#include <chrono>
#include <thread>

class macOSClock : public Clock
{
  public:
    macOSClock();
    ~macOSClock();

    int now() override;
    void wait(int durationInMilliseconds) override; // In milliseconds
    void waitMicroseconds(int durationInMicroseconds) override; // In microseconds

  private:
    std::chrono::steady_clock::time_point startTime;
};

#endif //ONDA_MACOS_CLOCK_H