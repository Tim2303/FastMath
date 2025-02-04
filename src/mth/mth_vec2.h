/***************************************************************
 * FILE NAME   : mth_vec2.h
 * PURPOSE     : Vector 2D class module.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include <format>

#include "mth_def.h"

/* Math namespace */
namespace mth
{
  /* Forward declaration */
  template<typename Type>
    class vec3;
  template<typename Type>
    class vec4;

  /* Vector 2D */
  template<typename Type>
    class vec2
    {
      static_assert(std::is_arithmetic_v<Type>, "Number type is needed in vec2");
    public:
      Type X, Y;

      /* Class default constructor */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2( void ) = default;

      /* Class constructor.
       * ARGUMENTS:
       *   - vector coordinates:
       *       const Type A;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2( const Type A ) noexcept : X(A), Y(A)
      {
      } /* End of 'vec2' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - vector coordinates:
       *       const Type A, B;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2( const Type A, const Type B ) noexcept : X(A), Y(B)
      {
      } /* End of 'vec2' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - 2d vector:
       *       const vec2<Type> &V;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2( const vec2<Type> &V ) noexcept : X(V.X), Y(V.Y)
      {
      } /* End of 'vec2' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - 3d vector:
       *       const vec3<Type> &V;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2( const vec3<Type> &V ) noexcept : X(V.X), Y(V.Y)
      {
      } /* End of 'vec2' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - 4d vector:
       *       const vec4<Type> &V;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2( const vec4<Type> &V ) noexcept : X(V.X), Y(V.Y)
      {
      } /* End of 'vec2' constructor */

      /* Vector pointer cast function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type *) result pointer.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr operator Type*( void ) const noexcept
      {
        return &X;
      } /* End of 'operator Type*' function */

      /* Vector component getter function.
       * ARGUMENTS:
       *   - index:
       *       const int Ind;
       * RETURNS:
       *   (Type) component.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type operator[]( const int Ind ) const
      {
        return *(&X + Ind);
      } /* End of 'operator[]' function */

      /* Vector component setter function.
       * ARGUMENTS:
       *   - index:
       *       const int Ind;
       * RETURNS:
       *   (Type &) reference to the component.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type & operator[]( const int Ind )
      {
        return *(&X + Ind);
      } /* End of 'operator[]' function */

      /* Add two 2D vectors function.
       * ARGUMENTS:
       *   - vector to be added:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 operator+( const vec2 &V ) const noexcept
      {
        return vec2(X + V.X, Y + V.Y);
      } /* End of 'operator+' function */

      /* Add 2D vector to current function.
       * ARGUMENTS:
       *   - vector to be added:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 & operator+=( const vec2 &V ) noexcept
      {
        X += V.X;
        Y += V.Y;
        return *this;
      }  /* End of 'operator+=' function */

      /* Subtract two 2D vectors function.
       * ARGUMENTS:
       *   - vector to be subtracted:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 operator-( const vec2 &V ) const noexcept
      {
        return vec2(X - V.X, Y - V.Y);
      } /* End of 'operator-' function */

      /* Subtract 2D vector from current function.
       * ARGUMENTS:
       *   - vector to be subtracted:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 & operator-=( const vec2 &V ) noexcept
      {
        X -= V.X;
        Y -= V.Y;
        return *this;
      } /* End of 'operator-=' function */

      /* Negate vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 operator-( void ) const noexcept
      {
        return vec2(-X, -Y);
      } /* End of 'operator-' function */

      /* Vector component-wise multiplication function.
       * ARGUMENTS:
       *   - vector to be multiplied:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 operator*( const vec2 &V ) const noexcept
      {
        return vec2(X * V.X, Y * V.Y);
      } /* End of 'operator*' function */

      /* Vector component-wise multiplication function.
       * ARGUMENTS:
       *   - vector to be multiplied:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 & operator*=( const vec2 &V ) noexcept
      {
        X *= V.X;
        Y *= V.Y;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector-number multiplication function.
       * ARGUMENTS:
       *   - number to be multiplied:
       *       const Type N;
       * RETURNS:
       *   (vec2) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 operator*( const Type N ) const noexcept
      {
        return vec2(X * N, Y * N);
      } /* End of 'operator*' function */

      /* Vector-number multiplication function.
       * ARGUMENTS:
       *   - number to be multiplied:
       *       const Type N;
       * RETURNS:
       *   (vec2 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 & operator*=( const Type N ) noexcept
      {
        X *= N;
        Y *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector component-wise division function.
       * ARGUMENTS:
       *   - vector to be divided by:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 operator/( const vec2 &V ) const
      {
        return vec2(X / V.X, Y / V.Y);
      } /* End of 'operator/' function */

      /* Vector component-wise division function.
       * ARGUMENTS:
       *   - vector to be divided by:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 & operator/=( const vec2 &V )
      {
        X /= V.X;
        Y /= V.Y;
        return *this;
      } /* End of 'operator/=' function */

      /* Vector-number division function.
       * ARGUMENTS:
       *   - number to be divided by:
       *       const Type N;
       * RETURNS:
       *   (vec2) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 operator/( const Type N ) const
      {
        return vec2(X / N, Y / N);
      } /* End of 'operator/' function */

      /* Vector-number division function.
       * ARGUMENTS:
       *   - number to divide by:
       *       const Type N;
       * RETURNS:
       *   (vec2 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 & operator/=( const Type N )
      {
        X /= N;
        Y /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Vector dot product function.
       * ARGUMENTS:
       *   - vector to multiply:
       *       const vec2 &V;
       * RETURNS:
       *   (Type) result number.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type operator&( const vec2 &V ) const noexcept
      {
        return X * V.X + Y * V.Y;
      } /* End of 'operator&' function */

      /* Get vector squared length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) squared vector length.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Length2( void ) const noexcept
      {
        return X * X + Y * Y;
      } /* End of 'Length2' function */

      /* Get vector length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) squared vector length.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Length( void ) const noexcept
      {
        if constexpr (std::is_same_v<Type, FLT>)
          return sqrtf(X * X + Y * Y);
        else
          return sqrt(X * X + Y * Y);
      } /* End of 'Length' function */

      /* Vector length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector length.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type operator!( void ) const noexcept
      {
        if constexpr (std::is_same_v<Type, FLT>)
          return sqrtf(X * X + Y * Y);
        else
          return sqrt(X * X + Y * Y);
      } /* End of 'operator!' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2 &) normalized vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 & Normalize( void ) noexcept
      {
        if (X == 0 && Y == 0)
          return *this;
        return *this /= Length();
      } /* End of 'Normalize' function */

      /* Get normalized vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) normalized vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 Normalizing( void ) const noexcept
      {
        if (X == 0 && Y == 0)
          return vec2(0);
        return *this / Length();
      } /* End of 'Normalizing' function */

      /* Get vector maximal component function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) maximal component.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type MaxC( void ) const noexcept
      {
        return max(X, Y);
      } /* End of 'MaxC' function */

      /* Get vector minimal component function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) minimal component.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type MinC( void ) const noexcept
      {
        return min(X, Y);
      } /* End of 'MinC' function */

      /* Get distance between vectors' ends function.
       * ARGUMENTS:
       *   - vector evaluate with:
       *       const vec2 &V;
       * RETURNS:
       *   (Type) result distance.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Distance( const vec2 &V ) const noexcept
      {
        return !(*this - V);
      } /* End of 'Distance' function */

      /* Vectors linear interpolation function.
       * ARGUMENTS:
       *   - vectors to lerp with:
       *       const vec2 &V;
       *   - lerp coefficient:
       *       const Type T;
       * RETURNS:
       *   (vec2) lerp result.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 Lerp( const vec2 &V, const Type T ) const noexcept
      {
        return vec2(
          std::lerp(X, V.X, T),
          std::lerp(Y, V.Y, T));
      } /* End of 'Lerp' function */

      /* Maximal vector function.
       * ARGUMENTS:
       *   - vector to compare:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) max result.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 Max( const vec2 &V ) const noexcept
      {
        return vec2(max(V.X, X), max(V.Y, Y));
      } /* End of 'Max' function */

      /* Minimal vector function.
       * ARGUMENTS:
       *   - vector to compare:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) min result.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 Min( const vec2 &V ) const noexcept
      {
        return vec2(min(V.X, X), min(V.Y, Y));
      } /* End of 'Min' function */

      /* Vector ceiling function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result ceiled.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 Ceil( void ) const noexcept
      {
        return vec2(std::ceil(X), std::ceil(Y));
      } /* End of 'Ceil' function */

      /* Vector flooring function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result floored.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec2 Floor( void ) const noexcept
      {
        return vec2(std::floor(X), std::floor(Y));
      } /* End of 'Floor' function */

      /* Get shortest angle between vectors function.
       * ARGUMENTS:
       *   - second vector:
       *       const vec2 &V;
       * RETURNS:
       *   (Type) result angle.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Angle( const vec2 &V ) const noexcept
      {
        const Type MulLen2 = Length2() * V.Length2();
        if (MulLen2 == 0)
          return 0;

        const Type angle = acos((*this & V) / sqrt(MulLen2));
        return R2D * (((-X * V.Y + Y * V.X) < 0) ? -angle : angle);
      } /* End of 'Angle' function */

      /* Get vector square function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result square.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Square( void ) const noexcept
      {
        return X * Y;
      } /* End of 'Square' function */

      /* Get random {0~1} vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) random vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static vec2 Rnd0( void ) noexcept
      {
        return vec2(
          static_cast<DBL>(rand()) / RAND_MAX,
          static_cast<DBL>(rand()) / RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Get random {-1~1} vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) random vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static vec2 Rnd1( void ) noexcept
      {
        return vec2(
          static_cast<DBL>(rand()) / RAND_MAX * 2 - 1,
          static_cast<DBL>(rand()) / RAND_MAX * 2 - 1);
      } /* End of 'Rnd1' function */

      /* Get random vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) random vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static vec2 Rnd( void ) noexcept
      {
        return vec2(rand(), rand());
      } /* End of 'Rnd' function */

#ifndef __CUDA__
      /* Convert to string function.
       * ARGUMENTS: None
       * RETURNS:
       *   (std::string) result string.
       */
      constexpr std::string ToString( void ) const noexcept
      {
        return std::format("{} {}", X, Y);
      } /* End of 'ToString' function */
#endif /* __CUDA__ */

    }; /* End of 'vec2' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec2_h_ */

/* END OF 'mth_vec2.h' FILE */
