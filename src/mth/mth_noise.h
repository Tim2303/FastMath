/***************************************************************
 * FILE NAME   : mth_noise.h
 * PURPOSE     : Noise generators class module.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_noise_h_
#define __mth_noise_h_

#include "mth_def.h"

/* Math namespace */
namespace mth
{
  /* Noise class */
  template<typename Type>
    class noise
    {
      static_assert(std::is_arithmetic_v<Type>, "Number type is needed in noise");

    public:
      static const int TAB_BITS = 8;
      static const int TAB_SIZE = 1 << TAB_BITS;
      static const int TAB_MASK = TAB_SIZE - 1;

      Type TabNoise[TAB_SIZE][TAB_SIZE];

      /* Class default constructor.
       * ARGUMENTS: None.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr noise( void ) noexcept
      {
        for (int i = 0; i < TAB_SIZE; i++)
          for (int j = 0; j < TAB_SIZE; j++)
            TabNoise[j][i] = static_cast<Type>(rand()) / RAND_MAX;
      } /* End of 'noise' function */

      /* Get 1D noise function.
       * ARGUMENTS:
       *   - number to create noise:
       *       const Type X;
       * RETURNS:
       *   (Type) result noise.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Noise1D( const Type X ) const noexcept
      {
        int ix = floor(X), ix1;
        const Type fx = X - ix;

        ix &= TAB_MASK;
        ix1 = (ix + 1) & TAB_MASK;
        return TabNoise[0][ix] * (1 - fx) +
               TabNoise[0][ix1] * fx;
      } /* End of 'Noise1D' function */

      /* Noise 1D turb function.
       * ARGUMENTS:
       *   - number to create noise:
       *       const Type X;
       *   - number of octaves:
       *       const int Octaves;
       * RETURNS:
       *   (Type) result noise.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type NoiseTurb1D( const Type X, const int Octaves ) const noexcept
      {
         int i, frac = 1;
         Type val = 0;

         for (i = 0; i < Octaves; i++)
         {
           val += Noise1D(X) / frac;
           X = (X + 29.47) * 2;
           frac *= 2;
         }
         return val * (1 << (Octaves - 1)) / ((1 << Octaves) - 1);
      } /* End of 'NoiseTurb1D' function */

      /* Get 2D noise function.
       * ARGUMENTS:
       *   - noise arguments:
       *       const DBL X, Y;
       * RETURNS:
       *   (DBL) noise value.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr DBL Noise2D( const DBL X, const DBL Y ) const noexcept
      {
        int ix = int(floor(X)), ix1, iy = int(floor(Y)), iy1;
        DBL fx, fy;

        fx = X - ix;
        fx = (3 - 2 * fx) * fx * fx;
        fy = Y - iy;
        fy = (3 - 2 * fy) * fy * fy;
        ix &= TAB_MASK;
        ix1 = (ix + 1) & TAB_MASK;
        iy &= TAB_MASK;
        iy1 = (iy + 1) & TAB_MASK;

        return
          TabNoise[ix][iy] * (1 - fx) * (1 - fy) +
          TabNoise[ix1][iy] * fx * (1 - fy) +
          TabNoise[ix][iy1] * (1 - fx) * fy +
          TabNoise[ix1][iy1] * fx * fy;
      } /* End of 'Noise2D' function */

      /* Noise 2D turb function.
       * ARGUMENTS:
       *   - noise arguments:
       *       const DBL X, Y;
       *   - number of octaves:
       *       const int Octaves;
       * RETURNS:
       *   (DBL) turbulence value.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr DBL NoiseTurb2D( const DBL X, const DBL Y, const int Octaves ) const noexcept
      {
        int i, frac = 1;
        DBL val = 0;

        for (i = 0; i < Octaves; i++)
        {
          val += Noise2D(X, Y) / frac;
          X = (X + 29.47) * 2;
          Y = (Y + 18.102) * 2;
          frac *= 2;
        }
        return val * (1 << (Octaves - 1)) / ((1 << Octaves) - 1);
      } /* End of 'NoiseTurb2D' function */

    }; /* End of 'noise' class */
} /* end of 'mth' namespace */

#endif /* __mth_noise_h_ */

/* END OF 'mth_noise.h' FILE */
