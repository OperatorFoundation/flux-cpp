//
// Created by Dr. Brandon Wiley on 11/20/25.
//

#ifndef ONDA_STDIO_LOGGER_H
#define ONDA_STDIO_LOGGER_H

#include <logger.h>

class StdioLogger : public Logger
{
  public:
    StdioLogger() = default;

  protected:
    void write(const char*) override;
};

#endif //ONDA_STDIO_LOGGER_H