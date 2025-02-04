/***************************************************************
 * FILE NAME   : mth_solver.h
 * PURPOSE     : Equations solver module.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_solver_h_
#define __mth_solver_h_

#include "mth_def.h"

/* Math namespace */
namespace mth
{
  /* Solver class */
  class solver
  {
  public:
    /* Class default constructor */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    solver( void ) = default;

    /* Get number sign function.
     * ARGUMENTS:
     *   - number to check:
     *       const DBL X;
     * RETURNS:
     *   (int) sign result.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    template<typename Type>
      constexpr static int Sign( const Type X ) noexcept
      {
        return static_cast<int>(X > 0) - static_cast<int>(X < 0);
      } /* End of 'Sign' function */

    /* Square equation solver.
     * ARGUMENTS:
     *   - koefficent solver:
     *       const DBL A, B, C;
     *   - 2 number solver:
     *       DBL *S;
     * RETURNS: None.
     */
  #ifdef __CUDA__
    __host__ __device__
  #endif /* __CUDA__ */
    constexpr static void SquareSolver( const DBL A, const DBL B, const DBL C, DBL *S ) noexcept
    {
      if (A == 0)
      {
        if (B == 0)
          return;
        S[0] = S[1] = -C / B;
        return;
      }

      const DBL
        D = B * B - A * C * 4,
        Rev2a = 1 / (2 * A);
      if (D > 0)
      {
        const DBL SqrtD = sqrt(D);
        S[0] = (-B + SqrtD) * Rev2a;
        S[1] = (-B - SqrtD) * Rev2a;
      }
      else if (D == 0)
        S[0] = S[1] = -B * Rev2a;
    } /* End of 'SquareSolver' function */

    /* Cubic equation solver.
     * ARGUMENTS:
     *   - koefficent solver:
     *       const DBL A, B, C, D;
     *   - 3 number solver:
     *       DBL *S;
     * RETURNS: None.
     */
  #ifdef __CUDA__
    __host__ __device__
  #endif /* __CUDA__ */
    constexpr static void CubicSolver( const DBL A, const DBL B, const DBL C, const DBL D, DBL *S ) noexcept
    {
      constexpr DBL Rev2 = 1.0f / 2, Rev3 = 1.0f / 3;

      if (A == 0)
      {
        SquareSolver(B, C, D, S);
        S[2] = S[1];
      }

      const DBL
        p = (3 * A * C - B * B) / (3 * A * A), q = (2 * B * B * B - 9 *A * B * C + 27 * A * A * D) / (27 * A * A * A),
        DNew = (p * Rev3) * (p * Rev3) * (p * Rev3) + (q * Rev2) * (q * Rev2);

      if (DNew > 0)
      {
        const DBL
          gamma = sqrt(DNew),
          alpha = cbrt(-q * Rev2 + gamma),
          beta = cbrt(-q * Rev2 - gamma);

        S[0] = S[1] = S[2] = (alpha + beta) - (B / (3 * A));
      }
      else if (DNew == 0)
      {
        const DBL alpha = cbrt(-q * Rev2);

        S[0] = 2 * alpha - (B / (3 * A));
        S[1] = S[2] = (-alpha) - (B / (3 * A));
      }
      else if (DNew < 0)
      {
        const DBL
          r = sqrt(-(p * p * p) / 27),
          phi = acos(-q / (2 * r));

        S[0] = 2 * sqrt(-p * Rev3) * cos(phi * Rev3) - (B / (3 * A));
        S[1] = 2 * sqrt(-p * Rev3) * cos((phi + 2 * PI) * Rev3) - (B / (3 * A));
        S[2] = 2 * sqrt(-p * Rev3) * cos((phi + 4 * PI) * Rev3) - (B / (3 * A));
      }
    } /* End of 'CubicSolver' function */

  }; /* End of 'solver' class */
} /* end of 'mth' namespace */

#endif /* __mth_solver_h_ */

/* END OF 'mth_solver.h' FILE */
