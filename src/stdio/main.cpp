//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "FluxMain.h"

int main()
{
  FluxMain flux_main = FluxMain();
  while(true)
  {
    flux_main.loop();
  }
}
