/***************************************************************
 * FILE NAME   : mth_quat.h
 * PURPOSE     : Quaternions class module.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_quat_h_
#define __mth_quat_h_

#include "mth_def.h"

/* Math namespace */
namespace mth
{
  /* Forward declaration */
  template<typename Type>
    class vec3;
  template<typename Type>
    class vec4;
  template<typename Type>
    class matr;
  template<typename Type>
    class tensor;

  /* Quaternion class */
  template<typename Type>
    class quat
    {
      static_assert(std::is_arithmetic_v<Type>, "Number type is needed in quat");

    public:
      union
      {
        struct
        { // Four numbers implementation
          Type X, Y, Z;
        };
        struct
        { // Number and vec3 implementation
          vec3<Type> Vec;
        };
      }; /* End of 'quat' union */
      Type W;

      /* Class default constructor */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat( void ) = default;

      /* Class constructor.
       * ARGUMENTS:
       *   - number:
       *       const Type A;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat( const Type A ) noexcept : X(A), Y(A), Z(A), W(A)
      {
      } /* End of 'quat' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - numbers:
       *       const Type A, B, C, D;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat( const Type A, const Type B, const Type C, const Type D ) noexcept : X(A), Y(B), Z(C), W(D)
      {
      } /* End of 'quat' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - number:
       *       const Type A;
       *   - vector:
       *       const vec3<Type> &V;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat( const Type A, const vec3<Type> &V ) noexcept : X(V.X), Y(V.Y), Z(V.Z), W(A)
      {
      } /* End of 'quat' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - vector 4D:
       *       const vec4<Type> &V;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat( const vec4<Type> &V ) noexcept : X(V.X), Y(V.Y), Z(V.Z), W(V.W)
      {
      } /* End of 'quat' function */

      /* Get quaternion number function.
       * ARGUMENTS:
       *   - number index:
       *       const UINT Ind;
       * RETURNS:
       *   (Type) quaternion number.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type operator[]( const UINT Ind ) const noexcept
      {
        return *(&X + Ind);
      } /* End of 'operator[]' function */

      /* Get quaternion number reference function.
       * ARGUMENTS:
       *   - number index:
       *       const UINT Ind;
       * RETURNS:
       *   (Type &) quaternion number reference.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type & operator[]( const UINT Ind ) noexcept
      {
        return *(&X + Ind);
      } /* End of 'operator[]' function */

      /* Get sum of two quats function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat) new quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat operator+( const quat &Q ) const noexcept
      {
        return quat(X + Q.X, Y + Q.Y, Z + Q.Z, W + Q.W);
      } /* End of 'operator+' function */

      /* Add quat to current function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat &) quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat & operator+=( const quat &Q ) noexcept
      {
        X += Q.X;
        Y += Q.Y;
        Z += Q.Z;
        W += Q.W;
        return *this;
      } /* End of 'operator+=' function */

      /* Get sub of two quats function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat) new quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat operator-( const quat &Q ) const noexcept
      {
        return quat(X - Q.X, Y - Q.Y, Z - Q.Z, W - Q.W);
      } /* End of 'operator-' function */

      /* Subtract quat from current function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat &) quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat & operator-=( const quat &Q ) noexcept
      {
        X -= Q.X;
        Y -= Q.Y;
        Z -= Q.Z;
        W -= Q.W;
        return *this;
      } /* End of 'operator-=' function */

      /* Get negative quat function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (quat) new quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat operator-( void ) const noexcept
      {
        return quat(-X, -Y, -Z, -W);
      } /* End of 'operator-' function */

      /* Get multiplication of two quats function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat) new quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat operator*( const quat &Q ) const noexcept
      {
        return quat(W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y,
                    W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X,
                    W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W,
                    W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z);
      } /* End of 'operator*' function */

      /* Multiply by quat function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat &) quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat & operator*=( const quat &Q ) noexcept
      {
        const quat q = *this;

        X = q.W * Q.X + q.X * Q.W + q.Y * Q.Z - q.Z * Q.Y;
        Y = q.W * Q.Y - q.X * Q.Z + q.Y * Q.W + q.Z * Q.X;
        Z = q.W * Q.Z + q.X * Q.Y - q.Y * Q.X + q.Z * Q.W;
        W = q.W * Q.W - q.X * Q.X - q.Y * Q.Y - q.Z * Q.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* Get multiplication with number function.
       * ARGUMENTS:
       *   - number:
       *       const Type Q;
       * RETURNS:
       *   (quat) new quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat operator*( const Type Q ) const noexcept
      {
        return quat(X * Q, Y * Q, Z * Q, W * Q);
      } /* End of 'operator*' function */

      /* Multiply by number function.
       * ARGUMENTS:
       *   - number:
       *       const Type Q;
       * RETURNS:
       *   (quat &) quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat & operator*=( const Type Q ) noexcept
      {
        X *= Q;
        Y *= Q;
        Z *= Q;
        W *= Q;
        return *this;
      } /* End of 'operator*=' function */

      /* Get divide of two quats function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat) new quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat operator/( const quat &Q ) const noexcept
      {
        return (*this) * (quat(Q.W, -Q.Vec) / !Q);
      } /* End of 'operator/' function */

      /* Get div with number function.
       * ARGUMENTS:
       *   - number:
       *       const Type Q;
       * RETURNS:
       *   (quat) new quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat operator/( const Type Q ) const noexcept
      {
        return quat(X / Q, Y / Q, Z / Q, W / Q);
      } /* End of 'operator/' function */

      /* Get quaternion magnitude function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result magnitude.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type operator!( void ) const noexcept
      {
        return W * W + X * X + Y * Y + Z * Z;
      } /* End of 'operator!' function */

      /* Get normalized quaternion function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (quat) normalized quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat Normalized( void ) const noexcept
      {
        const Type sq = sqrt(!*this);
        return quat(X / sq, Y / sq, Z / sq, W / sq);
      } /* End of 'Normalized' function */

      /* Get rotate quaternion by angle function.
       * ARGUMENTS:
       *    - angle in radians:
       *        const Type Angle;
       * RETURNS:
       *   (quat) result quat.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr quat RotateQuat( const Type Angle ) const noexcept
      {
        return quat(cos(Angle / 2.0lf), Vec * sin(Angle / 2.0lf));
      } /* End of 'RotateQuat' function */

      /* Get rotate matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr<Type>) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr matr<Type> RotateMatr( void ) const noexcept
      {
        const Type
          X2 = 2 * X * X,
          Y2 = 2 * Y * Y,
          Z2 = 2 * Z * Z,
          XZ = 2 * X * Z,
          XY = 2 * X * Y,
          YZ = 2 * Y * Z,
          WX = 2 * W * X,
          WY = 2 * W * Y,
          WZ = 2 * W * Z;

        return matr<Type>(
          1 - Y2 - Z2, XY + WZ,     XZ - WY,     0,  // 1 string
          XY - WZ,     1 - X2 - Z2, YZ + WX,     0,  // 2 string
          XZ + WY,     YZ - WX,     1 - X2 - Y2, 0,  // 3 string
          0,           0,           0,           1); // 4 string
      } /* End of 'RotateMatr' function */

      /* Get rotate tensor function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (tensor<Type>) result tensor.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor<Type> RotateTensor( void ) const noexcept
      {
        const Type
          X2 = 2 * X * X,
          Y2 = 2 * Y * Y,
          Z2 = 2 * Z * Z,
          XY = 2 * X * Y,
          WZ = 2 * W * Z,
          WY = 2 * W * Y,
          XZ = 2 * X * Z,
          YZ = 2 * Y * Z,
          WX = 2 * W * X;

        return tensor<Type>(
          1 - Y2 - Z2, XY + WZ,     XZ - WY,      // 1 string
          XY - WZ,     1 - X2 - Z2, YZ + WX,      // 2 string
          XZ + WY,     YZ - WX,     1 - X2 - Y2); // 3 string
      } /* End of 'RotateTensor' function */

      /* Get interpolation between 2 quats function.
       * ARGUMENTS:
       *    - parameter from 0 to 1:
       *        const Type T;
       *    - 2 quats:
       *        const quat &Q1, &Q2;
       * RETURNS:
       *   (quat) result quaternion.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static quat SLerp( const Type T, const quat &Q1, const quat &Q2 ) noexcept
      {
        Type cos_a = Q1.W * Q2.W + Q1.X * Q2.X + Q1.Y * Q2.Y + Q1.Z * Q2.Z;
        quat a = Q1, b = Q2;
        if (cos_a < 0)
          cos_a = -cos_a, b = -b;

        const Type
          alpha = acos(cos_a),
          sin_a_rev = 1 / sin(alpha),
          sin_ta = sin(T * alpha),
          sin_1_ta = sin((1 - T) * alpha);

        return quat(
          (a.X * sin_1_ta + b.X * sin_ta) * sin_a_rev,
          (a.Y * sin_1_ta + b.Y * sin_ta) * sin_a_rev,
          (a.Z * sin_1_ta + b.Z * sin_ta) * sin_a_rev,
          (a.W * sin_1_ta + b.W * sin_ta) * sin_a_rev);
      } /* End of 'SLerp' function */

    }; /* End of 'quat' class */
} /* end of 'mth' namespace */

#endif /* __mth_quat_h_ */

/* END OF 'mth_quat.h' FILE */
