#ifndef __ULTRASONICWAVE__
#define __ULTRASONICWAVE__
#include "sys.h"


	 
void UltrasonicWave_Init(void);
void UltrasonicWave_StartMeasure(void);
float UltrasonicWave_Measure(void);
#endif
