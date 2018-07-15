#include "delay.h"


void faz_delay(int n)
{
   volatile int d;
   for (d=0; d<n*3000; d++){}
}


