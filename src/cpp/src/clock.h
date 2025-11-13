//
// Created by Dr. Brandon Wiley on 5/26/25.
//

#ifndef CLOCK_H
#define CLOCK_H

#define EXPORT

class EXPORT Clock
{
  public:
    virtual ~Clock() = default;

    virtual int now() = 0; // In milliseconds
    virtual void wait(int durationInMilliseconds) = 0; // In milliseconds
    virtual void waitMicroseconds(int durationInMicroseconds) = 0; // In microseconds
};

#endif //CLOCK_H
