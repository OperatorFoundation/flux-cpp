//
// Created by Dr. Brandon Wiley on 11/4/25.
//

#ifndef EDEN_KEYBOARD_H
#define EDEN_KEYBOARD_H

#include <string>

#define EXPORT

class EXPORT Keyboard
{
  public:
    virtual ~Keyboard() = default;

    virtual bool availableForReading() = 0;
    virtual std::string read() = 0;
    virtual void update() = 0;
};

#endif //EDEN_KEYBOARD_H