/***************************************************************
 * FILE NAME   : mth_def.h
 * PURPOSE     : Vector 4D class module.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include <algorithm>
#include <format>

#include "mth_def.h"

/* Math namespace */
namespace mth
{
  /* Forward declaration */
  template<typename Type>
    class vec2;
  template<typename Type>
    class vec3;

  /* Vector 4D */
  template<typename Type>
    class vec4
    {
      static_assert(std::is_arithmetic_v<Type>, "Number type is needed in vec4");
    public:
      Type X, Y, Z, W;

      /* Class default constructor */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4( void ) = default;

      /* Class constructor.
       * ARGUMENTS:
       *   - vector coordinates:
       *       const Type A;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4( const Type A ) noexcept : X(A), Y(A), Z(A), W(A)
      {
      } /* End of 'vec4' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - vector coordinates:
       *       const Type A, B, C, D;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4( const Type A, const Type B, const Type C, const Type D ) noexcept
        : X(A), Y(B), Z(C), W(D)
      {
      } /* End of 'vec4' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - 2d vector:
       *       const vec2<Type> &V;
       *   - numbers:
       *       const Type C = 0, D = 0;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4( const vec2<Type> &V, const Type C = 0, const Type D = 0 ) noexcept
        : X(V.X), Y(V.Y), Z(C), W(D)
      {
      } /* End of 'vec4' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - 3d vector:
       *       const vec3<Type> &V;
       *   - numbers:
       *       const Type D = 0;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4( const vec3<Type> &V, const Type D = 0 ) noexcept
        : X(V.X), Y(V.Y), Z(V.Z), W(D)
      {
      } /* End of 'vec4' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - 4d vector:
       *       const vec4<Type> &V;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4( const vec4<Type> &V ) noexcept : X(V.X), Y(V.Y), Z(V.Z), W(V.W)
      {
      } /* End of 'vec4' constructor */

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

      /* Add two 4D vectors function.
       * ARGUMENTS:
       *   - vector to be added:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 operator+( const vec4 &V ) const noexcept
      {
        return vec4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
      } /* End of 'operator+' function */

      /* Add 4D vector to current function.
       * ARGUMENTS:
       *   - vector to be added:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 & operator+=( const vec4 &V ) noexcept
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        W += V.W;
        return *this;
      }  /* End of 'operator+=' function */

      /* Subtract two 4D vectors function.
       * ARGUMENTS:
       *   - vector to be subtracted:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 operator-( const vec4 &V ) const noexcept
      {
        return vec4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
      } /* End of 'operator-' function */

      /* Subtract 4D vector from current function.
       * ARGUMENTS:
       *   - vector to be subtracted:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 & operator-=( const vec4 &V ) noexcept
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        W -= V.W;
        return *this;
      } /* End of 'operator-=' function */

      /* Negate vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 operator-( void ) const noexcept
      {
        return vec4(-X, -Y, -Z, -W);
      } /* End of 'operator-' function */

      /* Vector component-wise multiplication function.
       * ARGUMENTS:
       *   - vector to be multiplied:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 operator*( const vec4 &V ) const noexcept
      {
        return vec4(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
      } /* End of 'operator*' function */

      /* Vector component-wise multiplication function.
       * ARGUMENTS:
       *   - vector to be multiplied:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 & operator*=( const vec4 &V ) noexcept
      {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;
        W *= V.W;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector-number multiplication function.
       * ARGUMENTS:
       *   - number to be multiplied:
       *       const Type N;
       * RETURNS:
       *   (vec4) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 operator*( const Type N ) const noexcept
      {
        return vec4(X * N, Y * N, Z * N, W * N);
      } /* End of 'operator*' function */

      /* Vector-number multiplication function.
       * ARGUMENTS:
       *   - number to be multiplied:
       *       const Type N;
       * RETURNS:
       *   (vec4 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 & operator*=( const Type N ) noexcept
      {
        X *= N;
        Y *= N;
        Z *= N;
        W *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector component-wise division function.
       * ARGUMENTS:
       *   - vector to be divided by:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 operator/( const vec4 &V ) const
      {
        return vec4(X / V.X, Y / V.Y, Z / V.Z, W / V.W);
      } /* End of 'operator/' function */

      /* Vector component-wise division function.
       * ARGUMENTS:
       *   - vector to be divided by:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 & operator/=( const vec4 &V )
      {
        X /= V.X;
        Y /= V.Y;
        Z /= V.Z;
        W /= V.W;
        return *this;
      } /* End of 'operator/=' function */

      /* Vector-number division function.
       * ARGUMENTS:
       *   - number to be divided by:
       *       const Type N;
       * RETURNS:
       *   (vec4) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 operator/( const Type N ) const
      {
        return vec4(X / N, Y / N, Z / N, W / N);
      } /* End of 'operator/' function */

      /* Vector-number division function.
       * ARGUMENTS:
       *   - number to divide by:
       *       const Type N;
       * RETURNS:
       *   (vec4 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 & operator/=( const Type N )
      {
        X /= N;
        Y /= N;
        Z /= N;
        W /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Vector dot product function.
       * ARGUMENTS:
       *   - vector to multiply:
       *       const vec4 &V;
       * RETURNS:
       *   (Type) result number.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type operator&( const vec4 &V ) const noexcept
      {
        return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
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
        return X * X + Y * Y + Z * Z + W * W;
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
          return sqrtf(X * X + Y * Y + Z * Z + W * W);
        else
          return sqrt(X * X + Y * Y + Z * Z + W * W);
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
          return sqrtf(X * X + Y * Y + Z * Z + W * W);
        else
          return sqrt(X * X + Y * Y + Z * Z + W * W);
      } /* End of 'operator!' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4 &) normalized vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 & Normalize( void ) noexcept
      {
        if (X == 0 && Y == 0 && Z == 0 && W == 0)
          return *this;
        return *this /= Length();
      } /* End of 'Normalize' function */

      /* Get normalized vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) normalized vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 Normalizing( void ) const noexcept
      {
        if (X == 0 && Y == 0 && Z == 0 && W == 0)
          return vec4(0);
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
        return max(max(X, Y), max(Z, W));
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
        return min(min(X, Y), min(Z, W));
      } /* End of 'MinC' function */

      /* Get distance between vectors' ends function.
       * ARGUMENTS:
       *   - vector evaluate with:
       *       const vec4 &V;
       * RETURNS:
       *   (Type) result distance.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Distance( const vec4 &V ) const noexcept
      {
        return !(*this - V);
      } /* End of 'Distance' function */

      /* Vectors linear interpolation function.
       * ARGUMENTS:
       *   - vectors to lerp with:
       *       const vec4 &V;
       *   - lerp coefficient:
       *       const Type T;
       * RETURNS:
       *   (vec4) lerp result.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 Lerp( const vec4 &V, const Type T ) const noexcept
      {
        return vec4(
          std::lerp(X, V.X, T),
          std::lerp(Y, V.Y, T),
          std::lerp(Z, V.Z, T),
          std::lerp(W, V.W, T));
      } /* End of 'Lerp' function */

      /* Maximal vector function.
       * ARGUMENTS:
       *   - vector to compare:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) max result.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 Max( const vec4 &V ) const noexcept
      {
        return vec4(max(V.X, X), max(V.Y, Y), max(V.Z, Z), max(W, V.W));
      } /* End of 'Max' function */

      /* Minimal vector function.
       * ARGUMENTS:
       *   - vector to compare:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) min result.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 Min( const vec4 &V ) const noexcept
      {
        return vec4(min(V.X, X), min(V.Y, Y), min(V.Z, Z), min(W, V.W));
      } /* End of 'Min' function */

      /* Vector ceiling function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result ceiled.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 Ceil( void ) const noexcept
      {
        return vec4(std::ceil(X), std::ceil(Y), std::ceil(Z), std::ceil(W));
      } /* End of 'Ceil' function */

      /* Vector flooring function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result floored.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4 Floor( void ) const noexcept
      {
        return vec4(std::floor(X), std::floor(Y), std::floor(Z), std::floor(W));
      } /* End of 'Floor' function */

      /* Get vector volume function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result volume.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Volume( void ) const noexcept
      {
        return X * Y * Z * W;
      } /* End of 'Volume' function */

      /* Create color DWORD function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (DWORD) 4 byte color.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr DWORD CreateColor( void ) const noexcept
      {
        return ((DWORD)(((BYTE)(std::clamp<Type>(Z, 0, 1) * 255) |
               ((WORD)((BYTE)(std::clamp<Type>(Y, 0, 1) * 255)) << 8)) |
               (((DWORD)(BYTE)(std::clamp<Type>(X, 0, 1) * 255)) << 16)) |
               (((DWORD)(BYTE)(std::clamp<Type>(W, 0, 1) * 255)) << 24));
      } /* End of 'CreateColor' function */

      /* Get random {0~1} vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) random vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static vec4 Rnd0( void ) noexcept
      {
        return vec4(
          static_cast<DBL>(rand()) / RAND_MAX,
          static_cast<DBL>(rand()) / RAND_MAX,
          static_cast<DBL>(rand()) / RAND_MAX,
          static_cast<DBL>(rand()) / RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Get random {-1~1} vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) random vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static vec4 Rnd1( void ) noexcept
      {
        return vec4(
          static_cast<DBL>(rand()) / RAND_MAX * 2 - 1,
          static_cast<DBL>(rand()) / RAND_MAX * 2 - 1,
          static_cast<DBL>(rand()) / RAND_MAX * 2 - 1,
          static_cast<DBL>(rand()) / RAND_MAX * 2 - 1);
      } /* End of 'Rnd1' function */

      /* Get random vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) random vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static vec4 Rnd( void ) noexcept
      {
        return vec4(rand(), rand(), rand(), rand());
      } /* End of 'Rnd' function */

#ifndef __CUDA__
      /* Convert to string function.
       * ARGUMENTS: None
       * RETURNS:
       *   (std::string) result string.
       */
      constexpr std::string ToString( void ) const noexcept
      {
        return std::format("{} {} {} {}", X, Y, Z, W);
      } /* End of 'ToString' function */
#endif /* __CUDA__ */
    }; /* End of 'vec4' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec4_h_ */

/* END OF 'mth_vec4.h' FILE */
