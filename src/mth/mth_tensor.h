/***************************************************************
 * FILE NAME   : mth_tensor.h
 * PURPOSE     : Tensor class module.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_tensor_h_
#define __mth_tensor_h_

#include "mth_def.h"

/* Math namespace */
namespace mth
{
  /* Forward declaration */
  template<typename Type>
    class vec3;

  /* Matrix 3x3 representation type */
  template<typename Type>
    class tensor
    {
      static_assert(std::is_arithmetic_v<Type>, "Number type is needed in tensor");

      template<typename Type2>
        friend class matr;
    private:
      Type A[3][3] = {};

    public:

      /* Class default constructor */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor( void ) = default;

      /* Tensor constructor by 9 numbers.
       * ARGUMENTS:
       *   - matrix parameters:
       *      const Type A00, A01, ..., A22;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor( const Type A00, const Type A01, const Type A02,
              const Type A10, const Type A11, const Type A12,
              const Type A20, const Type A21, const Type A22 ) noexcept
      {
        A[0][0] = A00;
        A[0][1] = A01;
        A[0][2] = A02;
        A[1][0] = A10;
        A[1][1] = A11;
        A[1][2] = A12;
        A[2][0] = A20;
        A[2][1] = A21;
        A[2][2] = A22;
      } /* End of 'tensor' function */

      /* Tensor constructor by 2-dimensional array.
       * ARGUMENTS:
       *   - tensor parameters:
       *      const Type a[3][3];
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor( const Type a[3][3] ) noexcept
      {
        A[0][0] = a[0][0];
        A[0][1] = a[0][1];
        A[0][2] = a[0][2];
        A[1][0] = a[1][0];
        A[1][1] = a[1][1];
        A[1][2] = a[1][2];
        A[2][0] = a[2][0];
        A[2][1] = a[2][1];
        A[2][2] = a[2][2];
      } /* End of 'tensor' function */

      /* Tensor copy constructor.
       * ARGUMENTS:
       *   - copy tensor:
       *      const tensor &T;
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor( const tensor &T ) noexcept
      {
        A[0][0] = T.A[0][0];
        A[0][1] = T.A[0][1];
        A[0][2] = T.A[0][2];
        A[1][0] = T.A[1][0];
        A[1][1] = T.A[1][1];
        A[1][2] = T.A[1][2];
        A[2][0] = T.A[2][0];
        A[2][1] = T.A[2][1];
        A[2][2] = T.A[2][2];
      } /* End of 'tensor' function */

      /* Add to tensor function.
       * ARGUMENTS:
       *   - source tensor:
       *       const tensor &T;
       * RETURNS:
       *   (tensor) result tensor.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor operator+( const tensor &T ) const noexcept
      {
        return tensor(
          A[0][0] + T.A[0][0], A[0][1] + T.A[0][1], A[0][2] + T.A[0][2],
          A[1][0] + T.A[1][0], A[1][1] + T.A[1][1], A[1][2] + T.A[1][2],
          A[2][0] + T.A[2][0], A[2][1] + T.A[2][1], A[2][2] + T.A[2][2]);
      } /* End of 'operator+' function */

      /* Multiply to number function.
       * ARGUMENTS:
       *   - number to multiply by:
       *       const Type T;
       * RETURNS:
       *   (tensor<Type>) result tensor.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor<Type> operator*( const Type T ) const noexcept
      {
        return tensor<Type>(
          A[0][0] * T, A[0][1] * T, A[0][2] * T,
          A[1][0] * T, A[1][1] * T, A[1][2] * T,
          A[2][0] * T, A[2][1] * T, A[2][2] * T);
      } /* End of 'operator*' function */

      /* Multiply tensors function.
       * ARGUMENTS:
       *   - tensor to multiply:
       *       const tensor &m;
       * RETURNS:
       *   (tensor) result tensor.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor operator*( const tensor &m ) const noexcept
      {
        return tensor{
          A[0][0] * m.A[0][0] + A[0][1] * m.A[1][0] + A[0][2] * m.A[2][0],
          A[0][0] * m.A[0][1] + A[0][1] * m.A[1][1] + A[0][2] * m.A[2][1],
          A[0][0] * m.A[0][2] + A[0][1] * m.A[1][2] + A[0][2] * m.A[2][2],
          A[1][0] * m.A[0][0] + A[1][1] * m.A[1][0] + A[1][2] * m.A[2][0],
          A[1][0] * m.A[0][1] + A[1][1] * m.A[1][1] + A[1][2] * m.A[2][1],
          A[1][0] * m.A[0][2] + A[1][1] * m.A[1][2] + A[1][2] * m.A[2][2],
          A[2][0] * m.A[0][0] + A[2][1] * m.A[1][0] + A[2][2] * m.A[2][0],
          A[2][0] * m.A[0][1] + A[2][1] * m.A[1][1] + A[2][2] * m.A[2][1],
          A[2][0] * m.A[0][2] + A[2][1] * m.A[1][2] + A[2][2] * m.A[2][2]
        };
      } /* End of 'operator*' function */

      /* Multiply this tensor function.
       * ARGUMENTS:
       *   - tensor to multiply:
       *       const tensor &m;
       * RETURNS:
       *   (tensor &) result tensor.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor & operator*=( const tensor &m ) noexcept
      {
        const tensor s = *this;

        A[0][0] = s.A[0][0] * m.A[0][0] + s.A[0][1] * m.A[1][0] + s.A[0][2] * m.A[2][0];
        A[0][1] = s.A[0][0] * m.A[0][1] + s.A[0][1] * m.A[1][1] + s.A[0][2] * m.A[2][1];
        A[0][2] = s.A[0][0] * m.A[0][2] + s.A[0][1] * m.A[1][2] + s.A[0][2] * m.A[2][2];
        A[1][0] = s.A[1][0] * m.A[0][0] + s.A[1][1] * m.A[1][0] + s.A[1][2] * m.A[2][0];
        A[1][1] = s.A[1][0] * m.A[0][1] + s.A[1][1] * m.A[1][1] + s.A[1][2] * m.A[2][1];
        A[1][2] = s.A[1][0] * m.A[0][2] + s.A[1][1] * m.A[1][2] + s.A[1][2] * m.A[2][2];
        A[2][0] = s.A[2][0] * m.A[0][0] + s.A[2][1] * m.A[1][0] + s.A[2][2] * m.A[2][0];
        A[2][1] = s.A[2][0] * m.A[0][1] + s.A[2][1] * m.A[1][1] + s.A[2][2] * m.A[2][1];
        A[2][2] = s.A[2][0] * m.A[0][2] + s.A[2][1] * m.A[1][2] + s.A[2][2] * m.A[2][2];
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply tensor by vec3 function.
       * ARGUMENTS:
       *   - source vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr vec3<Type> operator*( const vec3<Type> &V ) const noexcept
      {
        return vec3<Type>(
          (V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0]),
          (V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1]),
          (V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2]));
      } /* End of 'operator*' function */

      /* Get tensor determ function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result determination of tensor 3x3.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type Determ3x3( void ) const noexcept
      {
        return
          A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]) +
          A[0][1] * (A[1][2] * A[2][0] - A[1][0] * A[2][2]) +
          A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
      } /* End of 'Determ3x3' function */

      /* Get tensor deteminant function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result determinant.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr Type operator!( void ) const noexcept
      {
        return Determ3x3();
      } /* End of 'operator!' function */

      /* Obtain identity tensor function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (tensor) identity transformation tensor.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static tensor Identity( void ) noexcept
      {
        return tensor(
          1, 0, 0,
          0, 1, 0,
          0, 0, 1);
      } /* End of 'Identity' function */

      /* Tensor transpose function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (tensor) result tensor.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor Transpose( void ) const noexcept
      {
        return tensor{
          A[0][0], A[1][0], A[2][0],
          A[0][1], A[1][1], A[2][1],
          A[0][2], A[1][2], A[2][2]
        };
      } /* End of 'Transpose' function */

      /* Inverse tensor function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (tensor) inversed tensor.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr tensor Inverse( void ) const noexcept
      {
        const Type det = !(*this);
        if (det == 0)
          return Identity();

        const Type RevDet = 1 / det;
        return tensor{
          (A[1][1] * A[2][2] - A[1][2] * A[2][1]) * RevDet,
          (A[0][2] * A[2][1] - A[0][1] * A[2][1]) * RevDet,
          (A[0][1] * A[1][2] - A[0][2] * A[1][1]) * RevDet,
          (A[1][2] * A[2][0] - A[1][0] * A[2][2]) * RevDet,
          (A[0][0] * A[2][2] - A[0][2] * A[2][0]) * RevDet,
          (A[0][2] * A[1][0] - A[0][0] * A[1][2]) * RevDet,
          (A[1][0] * A[2][1] - A[1][1] * A[2][0]) * RevDet,
          (A[0][1] * A[2][0] - A[0][0] * A[2][1]) * RevDet,
          (A[0][0] * A[1][1] - A[0][1] * A[1][0]) * RevDet
        };
      } /* End of 'Inverse' function */

      /* Get star tensor function.
       * ARGUMENTS:
       *   - source vector:
       *       const vec3<Type> &W;
       * RETURNS:
       *   (tensor) star tensor.
       */
#ifdef __CUDA__
      __host__ __device__
#endif /* __CUDA__ */
      constexpr static tensor<Type> Star( const vec3<Type> &W ) noexcept
      {
        return tensor<Type>(
          0, -W[2], W[1],
          W[2], 0, -W[0],
          -W[1], W[0], 0);
      } /* End of 'Star' function */

    }; /* End of 'tensor' class */
} /* end of 'mth' namespace */

#endif /* __mth_tensor_h_ */

/* END OF 'mth_tensor.h' FILE */
