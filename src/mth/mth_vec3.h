/***************************************************************
 * FILE NAME   : mth_def.h
 * PURPOSE     : Vector 3D class module.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include <format>

#include "mth_def.h"

/* Math namespace */
namespace mth
{
  /* Forward declaration */
  template<typename Type>
    class vec2;
  template<typename Type>
    class vec4;

  /* Vector 3D */
  template<typename Type>
    class vec3
    {
      static_assert(std::is_arithmetic_v<Type>, "Number type is needed in vec3");

    public:
      Type X, Y, Z;

      /* Class default constructor */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3( void ) = default;

      /* Class constructor.
       * ARGUMENTS:
       *   - vector coordinates:
       *       const Type A;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3( const Type A ) noexcept : X(A), Y(A), Z(A)
      {
      } /* End of 'vec3' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - vector coordinates:
       *       const Type A, B, C;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3( const Type A, const Type B, const Type C ) noexcept : X(A), Y(B), Z(C)
      {
      } /* End of 'vec3' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - 2d vector:
       *       const vec2<Type> &V;
       *   - number:
       *       const Type C = 0;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3( const vec2<Type> &V, const Type C = 0 ) noexcept : X(V.X), Y(V.Y), Z(C)
      {
      } /* End of 'vec3' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - 3d vector:
       *       const vec3<Type> &V;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3( const vec3<Type> &V ) noexcept : X(V.X), Y(V.Y), Z(V.Z)
      {
      } /* End of 'vec3' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - 4d vector:
       *       const vec4<Type> &V;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3( const vec4<Type> &V ) noexcept : X(V.X), Y(V.Y), Z(V.Z)
      {
      } /* End of 'vec3' constructor */

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

      /* Add two 3D vectors function.
       * ARGUMENTS:
       *   - vector to be added:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 operator+( const vec3 &V ) const noexcept
      {
        return vec3(X + V.X, Y + V.Y, Z + V.Z);
      } /* End of 'operator+' function */

      /* Add 3D vector to current function.
       * ARGUMENTS:
       *   - vector to be added:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 & operator+=( const vec3 &V ) noexcept
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        return *this;
      }  /* End of 'operator+=' function */

      /* Subtract two 3D vectors function.
       * ARGUMENTS:
       *   - vector to be subtracted:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 operator-( const vec3 &V ) const noexcept
      {
        return vec3(X - V.X, Y - V.Y, Z - V.Z);
      } /* End of 'operator-' function */

      /* Subtract 3D vector from current function.
       * ARGUMENTS:
       *   - vector to be subtracted:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 & operator-=( const vec3 &V ) noexcept
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        return *this;
      } /* End of 'operator-=' function */

      /* Negate vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 operator-( void ) const noexcept
      {
        return vec3(-X, -Y, -Z);
      } /* End of 'operator-' function */

      /* Vector component-wise multiplication function.
       * ARGUMENTS:
       *   - vector to be multiplied:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 operator*( const vec3 &V ) const noexcept
      {
        return vec3(X * V.X, Y * V.Y, Z * V.Z);
      } /* End of 'operator*' function */

      /* Vector component-wise multiplication function.
       * ARGUMENTS:
       *   - vector to be multiplied:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 & operator*=( const vec3 &V ) noexcept
      {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector-number multiplication function.
       * ARGUMENTS:
       *   - number to be multiplied:
       *       const Type N;
       * RETURNS:
       *   (vec3) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 operator*( const Type N ) const noexcept
      {
        return vec3(X * N, Y * N, Z * N);
      } /* End of 'operator*' function */

      /* Vector-number multiplication function.
       * ARGUMENTS:
       *   - number to be multiplied:
       *       const Type N;
       * RETURNS:
       *   (vec3 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 & operator*=( const Type N ) noexcept
      {
        X *= N;
        Y *= N;
        Z *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector component-wise division function.
       * ARGUMENTS:
       *   - vector to be divided by:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 operator/( const vec3 &V ) const
      {
        return vec3(X / V.X, Y / V.Y, Z / V.Z);
      } /* End of 'operator/' function */

      /* Vector component-wise division function.
       * ARGUMENTS:
       *   - vector to be divided by:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 & operator/=( const vec3 &V )
      {
        X /= V.X;
        Y /= V.Y;
        Z /= V.Z;
        return *this;
      } /* End of 'operator/=' function */

      /* Vector-number division function.
       * ARGUMENTS:
       *   - number to be divided by:
       *       const Type N;
       * RETURNS:
       *   (vec3) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 operator/( const Type N ) const
      {
        return vec3(X / N, Y / N, Z / N);
      } /* End of 'operator/' function */

      /* Vector-number division function.
       * ARGUMENTS:
       *   - number to divide by:
       *       const Type N;
       * RETURNS:
       *   (vec3 &) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 & operator/=( const Type N )
      {
        X /= N;
        Y /= N;
        Z /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Vector dot product function.
       * ARGUMENTS:
       *   - vector to multiply:
       *       const vec3 &V;
       * RETURNS:
       *   (Type) result number.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type operator&( const vec3 &V ) const noexcept
      {
        return X * V.X + Y * V.Y + Z * V.Z;
      } /* End of 'operator&' function */

      /* Get vector cross product function.
       * ARGUMENTS:
       *   - vector to cross with:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) crossed vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 operator%( const vec3 &V ) const noexcept
      {
        return vec3(
          Y * V.Z - Z * V.Y,
          -X * V.Z + Z * V.X,
          X * V.Y - Y * V.X);
      } /* End of 'operator%' function */

      /* Set vector cross product function.
       * ARGUMENTS:
       *   - vector to cross with:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) crossed vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 & operator%=( const vec3 &V ) noexcept
      {
        const vec3 Saved = *this;

        X = Saved.Y * V.Z - Saved.Z * V.Y;
        Y = -Saved.X * V.Z + Saved.Z * V.X;
        Z = Saved.X * V.Y - Saved.Y * V.X;
        return *this;
      } /* End of 'operator%' function */

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
        return X * X + Y * Y + Z * Z;
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
          return sqrtf(X * X + Y * Y + Z * Z);
        else
          return sqrt(X * X + Y * Y + Z * Z);
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
          return sqrtf(X * X + Y * Y + Z * Z);
        else
          return sqrt(X * X + Y * Y + Z * Z);
      } /* End of 'operator!' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3 &) normalized vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 & Normalize( void ) noexcept
      {
        if (X == 0 && Y == 0 && Z == 0)
          return *this;
        return *this /= Length();
      } /* End of 'Normalize' function */

      /* Get normalized vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) normalized vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 Normalizing( void ) const noexcept
      {
        if (X == 0 && Y == 0 && Z == 0)
          return vec3(0);
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
        return max(max(X, Y), Z);
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
        return min(min(X, Y), Z);
      } /* End of 'MinC' function */

      /* Get distance between vectors' ends function.
       * ARGUMENTS:
       *   - vector evaluate with:
       *       const vec3 &V;
       * RETURNS:
       *   (Type) result distance.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Distance( const vec3 &V ) const noexcept
      {
        return !(*this - V);
      } /* End of 'Distance' function */

      /* Vectors linear interpolation function.
       * ARGUMENTS:
       *   - vectors to lerp with:
       *       const vec3 &V;
       *   - lerp coefficient:
       *       const Type T;
       * RETURNS:
       *   (vec3) lerp result.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 Lerp( const vec3 &V, const Type T ) const noexcept
      {
        return vec3(
          std::lerp(X, V.X, T),
          std::lerp(Y, V.Y, T),
          std::lerp(Z, V.Z, T));
      } /* End of 'Lerp' function */

      /* Maximal vector function.
       * ARGUMENTS:
       *   - vector to compare:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) max result.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 Max( const vec3 &V ) const noexcept
      {
        return vec3(max(V.X, X), max(V.Y, Y), max(V.Z, Z));
      } /* End of 'Max' function */

      /* Minimal vector function.
       * ARGUMENTS:
       *   - vector to compare:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) min result.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 Min( const vec3 &V ) const noexcept
      {
        return vec3(min(V.X, X), min(V.Y, Y), min(V.Z, Z));
      } /* End of 'Min' function */

      /* Vector ceiling function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result ceiled.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 Ceil( void ) const noexcept
      {
        return vec3(std::ceil(X), std::ceil(Y), std::ceil(Z));
      } /* End of 'Ceil' function */

      /* Vector flooring function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result floored.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3 Floor( void ) const noexcept
      {
        return vec3(std::floor(X), std::floor(Y), std::floor(Z));
      } /* End of 'Floor' function */

      /* Get shortest angle between vectors function.
       * ARGUMENTS:
       *   - second vector:
       *       const vec3 &V;
       * RETURNS:
       *   (Type) result angle.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Angle( const vec3 &V ) const noexcept
      {
        const Type MulLen2 = Length2() * V.Length2();
        if (MulLen2 == 0)
          return 0;

        const Type angle = acos((*this & V) / sqrt(MulLen2));
        return R2D * (((-X * V.Z + Z * V.X) < 0) ? -angle : angle);
      } /* End of 'Angle' function */

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
        return X * Y * Z;
      } /* End of 'Volume' function */

      /* Get random {0~1} vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) random vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static vec3 Rnd0( void ) noexcept
      {
        return vec3(
          static_cast<DBL>(rand()) / RAND_MAX,
          static_cast<DBL>(rand()) / RAND_MAX,
          static_cast<DBL>(rand()) / RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Get random {-1~1} vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) random vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static vec3 Rnd1( void ) noexcept
      {
        return vec3(
          static_cast<DBL>(rand()) / RAND_MAX * 2 - 1,
          static_cast<DBL>(rand()) / RAND_MAX * 2 - 1,
          static_cast<DBL>(rand()) / RAND_MAX * 2 - 1);
      } /* End of 'Rnd1' function */

      /* Get random vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) random vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static vec3 Rnd( void ) noexcept
      {
        return vec3(rand(), rand(), rand());
      } /* End of 'Rnd' function */

      /* Get vector index in 3D array function.
       * ARGUMENTS:
       *   - size of 3D array:
       *       const vec3 &Size;
       * RETURNS:
       *   (int) index in 3D array.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr int Index3D( const vec3<int> &Size ) const noexcept
      {
        return Size.X * (static_cast<int>(Y) * Size.Z + static_cast<int>(Z)) + static_cast<int>(X);
      } /* End of 'Index3D' function */

#ifndef __CUDA__
      /* Convert to string function.
       * ARGUMENTS: None
       * RETURNS:
       *   (std::string) result string.
       */
      constexpr std::string ToString( void ) const noexcept
      {
        return std::format("{} {} {}", X, Y, Z);
      } /* End of 'ToString' function */
#endif /* __CUDA__ */

    }; /* End of 'vec3' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */
