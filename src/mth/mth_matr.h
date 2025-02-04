/***************************************************************
 * FILE NAME   : mth_matr.h
 * PURPOSE     : Matrix 4x4 class module.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_matr_h_
#define __mth_matr_h_

#include <vector>

#include "mth_def.h"

/* Math namespace */
namespace mth
{
  /* Forward declaration */
  template<typename Type>
    class tensor;

  /* Matrix class */
  template<typename Type>
    class matr
    {
      template<typename Type2>
        friend class camera;

    private:
      Type A[4][4] = {};

      /* Get matrix 3x3 determ function.
       * ARGUMENTS:
       *   - parameters of matrix to determ:
       *       const Type A11, ..., A33;
       * RETURNS:
       *   (Type) result determinant of matrix 3x3.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static Type Determ3x3(
        const Type A11, const Type A12, const Type A13,
        const Type A21, const Type A22, const Type A23,
        const Type A31, const Type A32, const Type A33 ) noexcept
      {
        return
          A11 * (A22 * A33 - A23 * A32) +
          A12 * (A23 * A31 - A21 * A33) +
          A13 * (A21 * A32 - A22 * A31);
      } /* End of 'Determ3x3' function */

      /* Get matrix 4x4 deteminant function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result determinant.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Determ4x4( void ) const noexcept
      {
        return
          +A[0][0] * Determ3x3(A[1][1], A[1][2], A[1][3],
                            A[2][1], A[2][2], A[2][3],
                            A[3][1], A[3][2], A[3][3]) +
          -A[0][1] * Determ3x3(A[1][0], A[1][2], A[1][3],
                            A[2][0], A[2][2], A[2][3],
                            A[3][0], A[3][2], A[3][3]) +
          +A[0][2] * Determ3x3(A[1][0], A[1][1], A[1][3],
                            A[2][0], A[2][1], A[2][3],
                            A[3][0], A[3][1], A[3][3]) +
          -A[0][3] * Determ3x3(A[1][0], A[1][1], A[1][2],
                            A[2][0], A[2][1], A[2][2],
                            A[3][0], A[3][1], A[3][2]);
      } /* End of 'Determ4x4' function */

    public:
      /* Class default constructor.
       * ARGUMENTS: None.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr matr( void ) = default;

      /* Get matrix array function.
       * ARGUMENTS:
       *   - matrix array pointer:
       *      const UINT N;
       * RETURNS:
       *   (const Type *) pointer to array.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr const Type * operator[]( const UINT N ) const noexcept
      {
        return A[N];
      } /* End of 'operator[]' function */

      /* Get matrix array function.
       * ARGUMENTS:
       *   - matrix array pointer:
       *      const UINT N;
       * RETURNS:
       *   (Type *) pointer to array.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type * operator[]( const UINT N ) noexcept
      {
        return A[N];
      } /* End of 'operator[]' function */

      /* Matrix constructor by 16 numbers.
       * ARGUMENTS:
       *   - matrix parameters:
       *      const Type a00, a01, ..., a33;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr matr(
        const Type a00, const Type a01, const Type a02, const Type a03,
        const Type a10, const Type a11, const Type a12, const Type a13,
        const Type a20, const Type a21, const Type a22, const Type a23,
        const Type a30, const Type a31, const Type a32, const Type a33 ) noexcept
      {
        A[0][0] = a00;
        A[0][1] = a01;
        A[0][2] = a02;
        A[0][3] = a03;
        A[1][0] = a10;
        A[1][1] = a11;
        A[1][2] = a12;
        A[1][3] = a13;
        A[2][0] = a20;
        A[2][1] = a21;
        A[2][2] = a22;
        A[2][3] = a23;
        A[3][0] = a30;
        A[3][1] = a31;
        A[3][2] = a32;
        A[3][3] = a33;
      } /* End of 'matr' function */

      /* Matrix constructor by 16 numbers array.
       * ARGUMENTS:
       *   - matrix parameters:
       *      const Type Arr[];
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr matr( const Type Arr[] ) noexcept
      {
        memcpy(A, Arr, 16 * sizeof(Type));
      } /* End of 'matr' function */

      /* Matrix constructor by 2-dimensional array.
       * ARGUMENTS:
       *   - matrix parameters:
       *      const Type Arr[4][4];
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr matr( const Type Arr[4][4] ) noexcept
      {
        memcpy(A, Arr, 16 * sizeof(Type));
      } /* End of 'matr' function */

      /* Matrix constructor by initializer list.
       * ARGUMENTS:
       *   - matrix parameters:
       *      const std::vector<Type> &List;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr matr( const std::vector<Type> &List ) noexcept
      {
        memcpy(A, List.data(), 16 * sizeof(Type));
      } /* End of 'matr' function */

      /* Matr constructor by 2-dimensional array.
       * ARGUMENTS:
       *   - matrix parameters:
       *      const Type a[4][4];
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      template<typename Type1>
        constexpr matr( const matr<Type1> &M ) noexcept
        {
          if constexpr (std::is_same_v<Type, Type1>)
            memcpy(A, M.A, 16 * sizeof(Type));
          else
          {
            A[0][0] = static_cast<Type>(M.A[0][0]);
            A[0][1] = static_cast<Type>(M.A[0][1]);
            A[0][2] = static_cast<Type>(M.A[0][2]);
            A[0][3] = static_cast<Type>(M.A[0][3]);
            A[1][0] = static_cast<Type>(M.A[1][0]);
            A[1][1] = static_cast<Type>(M.A[1][1]);
            A[1][2] = static_cast<Type>(M.A[1][2]);
            A[1][3] = static_cast<Type>(M.A[1][3]);
            A[2][0] = static_cast<Type>(M.A[2][0]);
            A[2][1] = static_cast<Type>(M.A[2][1]);
            A[2][2] = static_cast<Type>(M.A[2][2]);
            A[2][3] = static_cast<Type>(M.A[2][3]);
            A[3][0] = static_cast<Type>(M.A[3][0]);
            A[3][1] = static_cast<Type>(M.A[3][1]);
            A[3][2] = static_cast<Type>(M.A[3][2]);
            A[3][3] = static_cast<Type>(M.A[3][3]);
          }
        } /* End of 'matr' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - tensor to get matrix from:
       *       const tensor<Type> &T;
       */
      constexpr matr( const tensor<Type> &T ) noexcept
      {
        // 0
        A[0][0] = T[0][0];
        A[0][1] = T[0][1];
        A[0][2] = T[0][2];
        // 1
        A[1][0] = T[1][0];
        A[1][1] = T[1][1];
        A[1][2] = T[1][2];
        // 2
        A[2][0] = T[2][0];
        A[2][1] = T[2][1];
        A[2][2] = T[2][2];
        // 3
        A[3][3] = 1;
      } /* End of 'matr' function */

      /* Deteminant matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result determinant.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type operator!( void ) const noexcept
      {
        return Determ4x4();
      } /* End of 'operator!' function */

      /* Multiply matrix and vector function.
       * ARGUMENTS:
       *   - vector to multiply:
       *       const vec4<Type> &V;
       * RETURNS:
       *   (vec4<Type>) multiplied vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec4<Type> operator*( const vec4<Type> &V ) const noexcept
      {
        return vec4<Type>(
          A[0][0] * V[0] + A[1][0] * V[1] + A[2][0] * V[2] + A[3][0] * V[3],
          A[0][1] * V[0] + A[1][1] * V[1] + A[2][1] * V[2] + A[3][1] * V[3],
          A[0][2] * V[0] + A[1][2] * V[1] + A[2][2] * V[2] + A[3][2] * V[3],
          A[0][3] * V[0] + A[1][3] * V[1] + A[2][3] * V[2] + A[3][3] * V[3]);
      } /* End of 'operator*' function */

      /* Get matrixes multiplication function.
       * ARGUMENTS:
       *   - matrix to multiply:
       *       const matr &m;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr matr operator*( const matr &m ) const noexcept
      {
        return matr{
          // 0
          A[0][0] * m.A[0][0] + A[0][1] * m.A[1][0] + A[0][2] * m.A[2][0] + A[0][3] * m.A[3][0],
          A[0][0] * m.A[0][1] + A[0][1] * m.A[1][1] + A[0][2] * m.A[2][1] + A[0][3] * m.A[3][1],
          A[0][0] * m.A[0][2] + A[0][1] * m.A[1][2] + A[0][2] * m.A[2][2] + A[0][3] * m.A[3][2],
          A[0][0] * m.A[0][3] + A[0][1] * m.A[1][3] + A[0][2] * m.A[2][3] + A[0][3] * m.A[3][3],
          // 1
          A[1][0] * m.A[0][0] + A[1][1] * m.A[1][0] + A[1][2] * m.A[2][0] + A[1][3] * m.A[3][0],
          A[1][0] * m.A[0][1] + A[1][1] * m.A[1][1] + A[1][2] * m.A[2][1] + A[1][3] * m.A[3][1],
          A[1][0] * m.A[0][2] + A[1][1] * m.A[1][2] + A[1][2] * m.A[2][2] + A[1][3] * m.A[3][2],
          A[1][0] * m.A[0][3] + A[1][1] * m.A[1][3] + A[1][2] * m.A[2][3] + A[1][3] * m.A[3][3],
          // 2
          A[2][0] * m.A[0][0] + A[2][1] * m.A[1][0] + A[2][2] * m.A[2][0] + A[2][3] * m.A[3][0],
          A[2][0] * m.A[0][1] + A[2][1] * m.A[1][1] + A[2][2] * m.A[2][1] + A[2][3] * m.A[3][1],
          A[2][0] * m.A[0][2] + A[2][1] * m.A[1][2] + A[2][2] * m.A[2][2] + A[2][3] * m.A[3][2],
          A[2][0] * m.A[0][3] + A[2][1] * m.A[1][3] + A[2][2] * m.A[2][3] + A[2][3] * m.A[3][3],
          // 3
          A[3][0] * m.A[0][0] + A[3][1] * m.A[1][0] + A[3][2] * m.A[2][0] + A[3][3] * m.A[3][0],
          A[3][0] * m.A[0][1] + A[3][1] * m.A[1][1] + A[3][2] * m.A[2][1] + A[3][3] * m.A[3][1],
          A[3][0] * m.A[0][2] + A[3][1] * m.A[1][2] + A[3][2] * m.A[2][2] + A[3][3] * m.A[3][2],
          A[3][0] * m.A[0][3] + A[3][1] * m.A[1][3] + A[3][2] * m.A[2][3] + A[3][3] * m.A[3][3]
        };
      } /* End of 'operator*' function */

      /* Multiply matrix function.
       * ARGUMENTS:
       *   - matrix to multiply:
       *       const matr &m;
       * RETURNS:
       *   (matr) result matrix.
       */
      constexpr matr<Type> & operator*=( const matr<Type> &m ) noexcept
      {
        const matr<Type> s = *this;

        // 0
        A[0][0] = s.A[0][0] * m.A[0][0] + s.A[0][1] * m.A[1][0] + s.A[0][2] * m.A[2][0] + s.A[0][3] * m.A[3][0],
        A[0][1] = s.A[0][0] * m.A[0][1] + s.A[0][1] * m.A[1][1] + s.A[0][2] * m.A[2][1] + s.A[0][3] * m.A[3][1],
        A[0][2] = s.A[0][0] * m.A[0][2] + s.A[0][1] * m.A[1][2] + s.A[0][2] * m.A[2][2] + s.A[0][3] * m.A[3][2],
        A[0][3] = s.A[0][0] * m.A[0][3] + s.A[0][1] * m.A[1][3] + s.A[0][2] * m.A[2][3] + s.A[0][3] * m.A[3][3],
        // 1
        A[1][0] = s.A[1][0] * m.A[0][0] + s.A[1][1] * m.A[1][0] + s.A[1][2] * m.A[2][0] + s.A[1][3] * m.A[3][0],
        A[1][1] = s.A[1][0] * m.A[0][1] + s.A[1][1] * m.A[1][1] + s.A[1][2] * m.A[2][1] + s.A[1][3] * m.A[3][1],
        A[1][2] = s.A[1][0] * m.A[0][2] + s.A[1][1] * m.A[1][2] + s.A[1][2] * m.A[2][2] + s.A[1][3] * m.A[3][2],
        A[1][3] = s.A[1][0] * m.A[0][3] + s.A[1][1] * m.A[1][3] + s.A[1][2] * m.A[2][3] + s.A[1][3] * m.A[3][3],
        // 2
        A[2][0] = s.A[2][0] * m.A[0][0] + s.A[2][1] * m.A[1][0] + s.A[2][2] * m.A[2][0] + s.A[2][3] * m.A[3][0],
        A[2][1] = s.A[2][0] * m.A[0][1] + s.A[2][1] * m.A[1][1] + s.A[2][2] * m.A[2][1] + s.A[2][3] * m.A[3][1],
        A[2][2] = s.A[2][0] * m.A[0][2] + s.A[2][1] * m.A[1][2] + s.A[2][2] * m.A[2][2] + s.A[2][3] * m.A[3][2],
        A[2][3] = s.A[2][0] * m.A[0][3] + s.A[2][1] * m.A[1][3] + s.A[2][2] * m.A[2][3] + s.A[2][3] * m.A[3][3],
        // 3
        A[3][0] = s.A[3][0] * m.A[0][0] + s.A[3][1] * m.A[1][0] + s.A[3][2] * m.A[2][0] + s.A[3][3] * m.A[3][0],
        A[3][1] = s.A[3][0] * m.A[0][1] + s.A[3][1] * m.A[1][1] + s.A[3][2] * m.A[2][1] + s.A[3][3] * m.A[3][1],
        A[3][2] = s.A[3][0] * m.A[0][2] + s.A[3][1] * m.A[1][2] + s.A[3][2] * m.A[2][2] + s.A[3][3] * m.A[3][2],
        A[3][3] = s.A[3][0] * m.A[0][3] + s.A[3][1] * m.A[1][3] + s.A[3][2] * m.A[2][3] + s.A[3][3] * m.A[3][3];

        return *this;
      } /* End of 'operator*=' function */

      /* Obtain identity matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) identity matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr Identity( void ) noexcept
      {
        return matr(
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1);
      } /* End of 'Identity' function */

      /* Inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) result inverse matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr matr Inverse( void ) const noexcept
      {
        const Type det = !(*this);
        if (det == 0)
          return Identity();

        matr r;
        /* Build adjoint matrix */
        r.A[0][0] =
        +Determ3x3(A[1][1], A[1][2], A[1][3],
                   A[2][1], A[2][2], A[2][3],
                   A[3][1], A[3][2], A[3][3]) / det;

        r.A[1][0] =
        -Determ3x3(A[1][0], A[1][2], A[1][3],
                   A[2][0], A[2][2], A[2][3],
                   A[3][0], A[3][2], A[3][3]) / det;

        r.A[2][0] =
        +Determ3x3(A[1][0], A[1][1], A[1][3],
                   A[2][0], A[2][1], A[2][3],
                   A[3][0], A[3][1], A[3][3]) / det;

        r.A[3][0] =
        -Determ3x3(A[1][0], A[1][1], A[1][2],
                   A[2][0], A[2][1], A[2][2],
                   A[3][0], A[3][1], A[3][2]) / det;

        r.A[0][1] =
        -Determ3x3(A[0][1], A[0][2], A[0][3],
                   A[2][1], A[2][2], A[2][3],
                   A[3][1], A[3][2], A[3][3]) / det;

        r.A[1][1] =
        +Determ3x3(A[0][0], A[0][2], A[0][3],
                   A[2][0], A[2][2], A[2][3],
                   A[3][0], A[3][2], A[3][3]) / det;

        r.A[2][1] =
        -Determ3x3(A[0][0], A[0][1], A[0][3],
                   A[2][0], A[2][1], A[2][3],
                   A[3][0], A[3][1], A[3][3]) / det;

        r.A[3][1] =
        +Determ3x3(A[0][0], A[0][1], A[0][2],
                   A[2][0], A[2][1], A[2][2],
                   A[3][0], A[3][1], A[3][2]) / det;

        r.A[0][2] =
        +Determ3x3(A[0][1], A[0][2], A[0][3],
                   A[1][1], A[1][2], A[1][3],
                   A[3][1], A[3][2], A[3][3]) / det;

        r.A[1][2] =
        -Determ3x3(A[0][0], A[0][2], A[0][3],
                   A[1][0], A[1][2], A[1][3],
                   A[3][0], A[3][2], A[3][3]) / det;

        r.A[2][2] =
        +Determ3x3(A[0][0], A[0][1], A[0][3],
                   A[1][0], A[1][1], A[1][3],
                   A[3][0], A[3][1], A[3][3]) / det;

        r.A[3][2] =
        -Determ3x3(A[0][0], A[0][1], A[0][2],
                   A[1][0], A[1][1], A[1][2],
                   A[3][0], A[3][1], A[3][2]) / det;

        r.A[0][3] =
        -Determ3x3(A[0][1], A[0][2], A[0][3],
                   A[1][1], A[1][2], A[1][3],
                   A[2][1], A[2][2], A[2][3]) / det;

        r.A[1][3] =
        +Determ3x3(A[0][0], A[0][2], A[0][3],
                   A[1][0], A[1][2], A[1][3],
                   A[2][0], A[2][2], A[2][3]) / det;

        r.A[2][3] =
        -Determ3x3(A[0][0], A[0][1], A[0][3],
                   A[1][0], A[1][1], A[1][3],
                   A[2][0], A[2][1], A[2][3]) / det;

        r.A[3][3] =
        +Determ3x3(A[0][0], A[0][1], A[0][2],
                   A[1][0], A[1][1], A[1][2],
                   A[2][0], A[2][1], A[2][2]) / det;

        return r;
      } /* End of 'Inverse' function */

      /* Matrix transpose function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr matr Transpose( void ) const noexcept
      {
        return matr{
          A[0][0], A[1][0],  A[2][0],  A[3][0],
          A[0][1], A[1][1],  A[2][1],  A[3][1],
          A[0][2], A[1][2],  A[2][2], A[3][2],
          A[0][3], A[1][3], A[2][3], A[3][3]
        };
      } /* End of 'Transpose' function */

      /* Get rotation by X matrix function.
       * ARGUMENTS:
       *   - angle in degrees:
       *       const Type AngleInDegree;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr RotateX( const Type AngleInDegree ) noexcept
      {
        const Type
          co = cos(D2R * AngleInDegree),
          si = sin(D2R * AngleInDegree);

        return matr(
          1, 0, 0, 0,
          0, co, si, 0,
          0, -si, co, 0,
          0, 0, 0, 1);
      } /* End of 'RotateX' function */

      /* Get rotation by Y matrix function.
       * ARGUMENTS:
       *   - angle in degrees:
       *       const Type AngleInDegree;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr RotateY( const Type AngleInDegree ) noexcept
      {
        const Type
          co = cos(D2R * AngleInDegree),
          si = sin(D2R * AngleInDegree);

        return matr(
          co, 0, -si, 0,
          0, 1, 0, 0,
          si, 0, co, 0,
          0, 0, 0, 1);
      } /* End of 'RotateY' function */

      /* Get rotation by Z matrix function.
       * ARGUMENTS:
       *   - angle in degrees:
       *       const Type AngleInDegree;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr RotateZ( const Type AngleInDegree ) noexcept
      {
        const Type
          co = cos(D2R * AngleInDegree),
          si = sin(D2R * AngleInDegree);

        return matr(
          co, si, 0, 0,
          -si, co, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1);
      } /* End of 'RotateZ' function */

      /* Get rotation by vector matrix function.
       * ARGUMENTS:
       *   - angle in degrees:
       *       const Type AngleInDegree;
       *   - vector to create rotation matrix:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr Rotate( const Type AngleInDegree, const vec3<Type> &V ) noexcept
      {
        const Type
          co = cos(D2R * AngleInDegree),
          si = sin(D2R * AngleInDegree);
  
        return matr(
          co + V.X * V.X * (1 - co), V.X * V.Y * (1 - co) + V.Z * si, V.X * V.Z * (1 - co) - V.Y * si, 0,
          V.X * V.Y * (1 - co) - V.Z * si, co + V.Y * V.Y * (1 - co), V.Z * V.Y * (1 - co) + V.X * si, 0,
          V.X * V.Z * (1 - co) + V.Y * si, V.Z * V.Y * (1 - co) - V.X * si, co + V.Z * V.Z * (1 - co), 0,
          0, 0, 0, 1);
      } /* End of 'Rotate' function */

      /* Matrix translating function.
       * ARGUMENTS:
       *   - vector to create matrix:
       *       const vec3<Type> &T;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr Translate( const vec3<Type> &T ) noexcept
      {
        return matr(
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          T[0], T[1], T[2], 1);
      } /* End of 'Translate' function */

      /* Matrix scaling function.
       * ARGUMENTS:
       *   - vector to create matrix:
       *       const vec3<Type> &S;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr Scale( const vec3<Type> &S ) noexcept
      {
        return matr(
          S[0], 0, 0, 0,
          0, S[1], 0, 0,
          0, 0, S[2], 0,
          0, 0, 0, 1);
      } /* End of 'Scale' function */

      /* Matrix scaling function.
       * ARGUMENTS:
       *   - vector to create matrix:
       *       const Type A;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr Scale( const Type A ) noexcept
      {
        return matr(
          A, 0, 0, 0,
          0, A, 0, 0,
          0, 0, A, 0,
          0, 0, 0, 1);
      } /* End of 'Scale' function */

      /* Transform vector as point function.
       * ARGUMENTS:
       *   - source vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3<Type> PointTransform( const vec3<Type> &V ) const noexcept
      {
        return vec3<Type>(
          (V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0] + A[3][0]),
          (V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1] + A[3][1]),
          (V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2] + A[3][2]));
      } /* End of 'PointTransform' function */

      /* Transform vector function.
       * ARGUMENTS:
       *   - source vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3<Type> VectorTransform( const vec3<Type> &V ) const noexcept
      {
        return vec3<Type>(
          (V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0]),
          (V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1]),
          (V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2]));
      } /* End of 'VectorTransform' function */

      /* Vector transform as 4x4 function.
       * ARGUMENTS:
       *   - source vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3<Type> Transform4x4( const vec3<Type> &V ) const noexcept
      {
        const DBL w = 1 / (V[0] * A[0][3] + V[1] * A[1][3] + V[2] * A[2][3] + A[3][3]);

        return vec3<Type>(
          (V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0] + A[3][0]) * w,
          (V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1] + A[3][1]) * w,
          (V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2] + A[3][2]) * w);
      } /* End of 'Transform4x4' function */

      /* Vector transform as normal function.
       * ARGUMENTS:
       *   - source vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3<Type> NormalTransform( const vec3<Type> &V ) const noexcept
      {
        const matr M = Inverse().Transpose();

        return vec3<Type>(
          (V[0] * M.A[0][0] + V[1] * M.A[1][0] + V[2] * M.A[2][0]),
          (V[0] * M.A[0][1] + V[1] * M.A[1][1] + V[2] * M.A[2][1]),
          (V[0] * M.A[0][2] + V[1] * M.A[1][2] + V[2] * M.A[2][2]));
      } /* End of 'NormalTransform' function */

      /* Create view matrix function.
       * ARGUMENTS:
       *   - view vectors:
       *       const vec3<Type> &Loc, &At, &Up1;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr View( const vec3<Type> &Loc, const vec3<Type> &At, const vec3<Type> &Up1 ) noexcept
      {
        const vec3<Type>
          Dir = (At - Loc).Normalize(),
          Right = (Dir % Up1).Normalize(),
          Up = Right % Dir;

        return matr(
          Right[0], Up[0], -Dir[0], 0,
          Right[1], Up[1], -Dir[1], 0,
          Right[2], Up[2], -Dir[2], 0,
          -Loc & Right, -Loc & Up, (Loc & Dir), 1);
      } /* End of 'View' function */

      /* Ortho matrix function.
       * ARGUMENTS:
       *   - numbers to ortho:
       *       const DBL Left, Right, Bottom, Top, Near, Far;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr Ortho(
        const DBL Left,   const DBL Right,
        const DBL Bottom, const DBL Top,
        const DBL Near,   const DBL Far )
      {
        return matr{
          2 / (Right - Left), 0, 0, 0,
          0, 2 / (Top - Bottom), 0, 0,
          0, 0, -2 / (Far - Near), 0,
          -(Left + Right) / (Right - Left), -(Top + Bottom) / (Top - Bottom), -(Far + Near) / (Far - Near), 1};
      } /* End of 'Ortho' function */

      /* Frustum matrix function.
       * ARGUMENTS:
       *   - left end:
       *       const Type Left;
       *   - right end:
       *       const Type Right;
       *   - bottom end:
       *       const Type Bottom;
       *   - top end:
       *       const Type Top;
       *   - near plane:
       *       const Type Near;
       *   - far plane:
       *       const Type Far;
       * RETURNS:
       *   (matr) result matrix.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static matr Frustum(
        const Type Left, const Type Right, const Type Top,
        const Type Bottom, const Type Near, const Type Far )
      {
        return matr{
          2 * Near / (Right - Left), 0, 0, 0,
          0, 2 * Near / (Top - Bottom), 0, 0,
          (Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom), (Far + Near) / (Near - Far), -1,
          0, 0, 2 * Near * Far / (Near - Far), 0};
      } /* End of 'Frustum' function */

#ifndef __CUDA__
      /* Convert matrix to string function.
       * ARGUMENTS: None
       * RETURNS:
       *   (std::string) result string.
       */
      constexpr std::string ToString( void ) const noexcept
      {
        return std::format("{} {} {} {}\n{} {} {} {}\n{} {} {} {}\n{} {} {} {}",
          A[0][0], A[0][1], A[0][2], A[0][3],
          A[1][0], A[1][1], A[1][2], A[1][3],
          A[2][0], A[2][1], A[2][2], A[2][3],
          A[3][0], A[3][1], A[3][2], A[3][3]);
      } /* End of 'ToString' function */
#endif /* __CUDA__ */

    }; /* End of 'matr' class */
} /* end of 'mth' namespace */

#endif /* __mth_matr_h_ */

/* END OF 'mth_matr.h' FILE */
