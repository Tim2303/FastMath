/***************************************************************
 * FILE NAME   : mth_def.h
 * PURPOSE     : Default math declarations.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_def_h_
#define __mth_def_h_

#include <cmath>

/* Real numbers types */
typedef float FLT;
typedef double DBL;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef unsigned int UINT;

/* Project namespace */
namespace mth
{
  /* Constants definition */
  constexpr DBL PI = 3.14159265358979323846;
  constexpr DBL D2R = PI / 180.0;
  constexpr DBL R2D = 180.0 / PI;
} /* end of 'mth' namespace */

#endif /* __mth_def_h_ */

/* END OF 'mth_def.h' FILE */
