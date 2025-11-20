//
// Created by Dr. Brandon Wiley on 11/20/25.
//

#include "stdio_logger.h"
#include <cstdio>

void StdioLogger::write(const char *cs)
{
  printf("%s\n", cs);
}

