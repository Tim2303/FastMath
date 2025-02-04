/***************************************************************
 * FILE NAME   : mth_ray.h
 * PURPOSE     : Ray class module.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_ray_h_
#define __mth_ray_h_

#include "mth_def.h"

/* Math namespace */
namespace mth
{
  /* Forward declaration */
  template<typename Type>
    class vec3;

  /* Ray class */
  template<typename Type>
    class ray
    {
      static_assert(std::is_arithmetic_v<Type>, "Number type is needed in ray");

    public:
      vec3<Type>
        Org, // Ray origin
        Dir; // Ray normalized direction

      /* Class default constructor */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr ray( void ) = default;

      /* Class copying constructor.
       * ARGUMENTS:
       *   - ray to be copied:
       *       const ray &R;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr ray( const ray &R ) noexcept : Org(R.Org), Dir(R.Dir)
      {
      } /* End of 'ray' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - ray new origin and direction:
       *       const vec3<Type> &O, &D;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr ray( const vec3<Type> &O, const vec3<Type> &D ) noexcept : Org(O), Dir(D)
      {
        Dir.Normalize();
      } /* End of 'ray' function */

      /* Obtain ray point function.
       * ARGUMENTS:
       *   - ray point distance:
       *       const Type T;
       * RETURNS:
       *   (vec3<Type>) result point on ray.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3<Type> operator()( const Type T ) const noexcept
      {
        return Org + Dir * T;
      } /* End of 'operator()' function */

      /* Vector coordinate access by number function.
       * ARGUMENTS:
       *   - coordinate number (0 - 'x', 1 - 'y', 2 - 'z'):
       *       const int No;
       * RETURNS:
       *   (Type &) reference to coordinate.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type & operator[]( const int No )
      {
        return *(&Org.X + No);
      } /* End of 'operator[]' function */

      /* Distance to intersect with sphere find function.
       * ARGUMENTS:
       *   - center of the sphere:
       *       const vec3<Type> &Center;
       *   - radius of the sphere:
       *       const DBL Radius;
       * RETURNS:
       *   (DBL) distance to intersection.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr DBL intersect( const vec3<Type> &Center, const DBL Radius ) const noexcept
      {
        const DBL
          oc2 = (Center - Org) & (Center - Org),
          ok = (Center - Org) & Dir,
          h2 = Radius * Radius - (oc2 - ok * ok);
  
        if (oc2 < Radius * Radius)
          return ok + sqrtf(h2);
        if (ok < 0 || h2 < 0)
          return -1;
        return ok - sqrtf(h2);
      } /* End of 'intersect' function */

    }; /* End of 'ray' class */
} /* end of 'mth' namespace */

#endif /* __mth_ray_h_ */

/* END OF 'mth_ray.h' FILE */
