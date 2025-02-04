/***************************************************************
 * FILE NAME   : mth_rand.h
 * PURPOSE     : Random generators class module.
 * LAST UPDATE : 04.02.2025
 ***************************************************************/

#ifndef __mth_rand_h_
#define __mth_rand_h_

#include "mth_def.h"

#include "mth_matr.h"

/* Math namespace */
namespace mth
{
  /* Forward declaration */
  template<typename Type>
    class vec3;
  template<typename Type>
    class matr;

  /* Random namespace */
  namespace random
  {
    /* Random number from min to max.
     * ARGUMENTS:
     *   - min and max value number:
     *       const DBL Min, Max;
     * RETURNS:
     *   (DBL) number result.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    template<typename Type = DBL>
      inline Type RandomRange( const Type Min, const Type Max ) noexcept
      {
        return (static_cast<Type>(rand()) / RAND_MAX * (Max - Min)) + Min;
      } /* End of 'RandomRange' function */

    /* Normal distribution random number.
     * ARGUMENTS:
     *   - mathematical expecation:
     *       const DBL Mean;
     *   - despersion:
     *       const DBL Dev;
     * RETURNS:
     *   (DBL) number result.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    template<typename Type = DBL>
      inline Type GaussianDistribution( const Type Mean, const Type Dev ) noexcept
      {
        Type u, v, s;
        do
        {
           u = RandomRange(-1, 1);
           v = RandomRange(-1, 1);
           s = (u * u) + (v * v);
        } while (s > 1 || s == 0);

        Type r = static_cast<Type>(sqrt(-2.0 * log(s) / s));
        return r * v * Dev + Mean;
      } /* End of 'GaussianDistribution' function */

  } /* end of 'random' namespace */

  /* Random generator class */
  class random_generator
  {
  private:
    int Size;         // Size random number array
    DBL *RndNumUni;   // Array random number uniform
    int IndU = 0;     // Index current uniform random number in array
    DBL *RndNumGauss; // Array random number gauss
    int IndG = 0;     // Index current gauss random number in array

  public:
    /* Class default constructor */
    random_generator( void ) = default;

    /* Class destructor.
     * ARGUMENTS: None.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    ~random_generator( void ) noexcept
    {
      delete RndNumGauss;
      delete RndNumUni;
    } /* End of '~random_generator' function */

    /* Create random numbers array function.
     * ARGUMENTS:
     *   - size of array:
     *       const int N;
     * RETURNS: None.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    void Create( int N ) noexcept
    {
      Size = N;
      RndNumUni = new DBL[N];
      RndNumGauss = new DBL[N];

      for (int i = 0; i < N; i++)
        RndNumUni[i] = static_cast<DBL>(rand()) / RAND_MAX;

      for (int i = 0; i < N; i++)
        RndNumGauss[i] = random::GaussianDistribution(0, 1);
    } /* End of 'Create' function */

    /* Get gauss random number in array.
     * ARGUMENTS:
     *   - mathematical expecation:
     *       const DBL Mean;
     *   - despresion:
     *       const DBL Dev;
     * RETURNS: 
     *   (DBL) number result.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    DBL GetG( const DBL Mean, const DBL Dev ) noexcept
    {
      const DBL x = RndNumGauss[IndG] * Dev + Mean;
      IndG = (IndG + 1) % Size;
      return x;
    } /* End of 'GetG' function */

    /* Get random number in array.
     * ARGUMENTS:
     *   - min and max value number:
     *       const DBL Min, Max;
     * RETURNS:
     *   (DBL) number result.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    DBL GetU( const DBL Min, const DBL Max ) noexcept
    {
      const DBL x = RndNumUni[IndU] * (Max - Min) + Min;
      IndU = (IndU + 1) % Size;
      return x;
    } /* End of 'GetU' function */

    /* Get random point on sphere.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3<DBL>) point result.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    vec3<DBL> RandomPointOnSphere( void ) noexcept
    {
      const DBL
        phi = GetU(-PI, PI),
        h = GetU(-1.0f, 1.0f);

      return vec3<DBL>(sqrt(1 - h * h) * cos(phi), h, sqrt(1 - h * h) * sin(phi));
    } /* End of 'RandomPointOnSphere' function */

    /* Uniform distribution random vector pointing in a directional angularly offset.
     * ARGUMENTS:
     *   - directional vector:
     *      const vec3<DBL> &Dir;
     *   - angularly offset in degree:
     *       const DBL Alpha;
     * RETURNS:
     *   (vec3<DBL>) vector result.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    vec3<DBL> RandomUniformDirect( const vec3<DBL> &Dir, const DBL Alpha ) noexcept
    {
      const vec3<DBL> uz(Dir.Normalizing());
      vec3<DBL> a;
      if (uz[1] == 0 && uz[2] == 0)
        a = vec3<DBL>(0, 1, 0);
      else
        a = vec3<DBL>(1, 0, 0);

      const vec3<DBL>
        ux((a % uz).Normalizing()),
        uy((uz % ux));
      const matr<DBL> Basis(
        ux[0], ux[1], ux[2], 0,
        uy[0], uy[1], uy[2], 0,
        uz[0], uz[1], uz[2], 0,
        0, 0, 0, 1);

      const DBL
        fi = sqrt(GetU(0, 1)) * D2R * Alpha,
        teta = GetU(-PI, PI);
      const vec3<DBL> v(cos(teta) * sin(fi), sin(teta) * sin(fi), cos(fi));

      return Basis.VectorTransform(v);
    } /* End of 'RandomUniformDirect' function */

    /* Gaussian distribution random vector pointing in a directional angularly offset.
     * ARGUMENTS:
     *   - directional vector:
     *      const vec3<DBL> &Dir;
     *   - angularly offset in degree:
     *       const DBL Alpha;
     * RETURNS:
     *   (vec3<DBL>) vector result.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    vec3<DBL> RandomGaussianDirect( const vec3<DBL> &Dir, const DBL Alpha ) noexcept
    {
      const vec3<DBL> uz(Dir.Normalizing());
      vec3<DBL> a;
      if (uz[1] == 0 && uz[2] == 0)
        a = vec3<DBL>(0, 1, 0);
      else
        a = vec3<DBL>(1, 0, 0);

      const vec3<DBL>
        ux((a % uz).Normalizing()),
        uy((uz % ux));
      const matr<DBL> Basis(
        ux[0], ux[1], ux[2], 0,
        uy[0], uy[1], uy[2], 0,
        uz[0], uz[1], uz[2], 0,
        0, 0, 0, 1);

      const DBL
        f = fabs(GetG(0, D2R * Alpha / 3)),
        teta = GetU(-PI, PI);
      const vec3<DBL> v(cos(teta) * sin(f), sin(teta) * sin(f), cos(f));

      return Basis.VectorTransform(v);
    } /* End of 'RandomGaussianDirect' function */

    /* Uniform distribution random point on disk.
     * ARGUMENTS:
     *   - position center disk:
     *      const vec3<DBL> Pos;
     *   - surface normal:
     *       const vec3<DBL> Norm;
     *   - radius disk:
     *       const DBL Rad;
     * RETURNS:
     *   (vec3<DBL>) vector result.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    vec3<DBL> RandomUniformPointOnDisk( const vec3<DBL> &Pos, const vec3<DBL> &Norm, const DBL Rad ) noexcept
    {
      const vec3<DBL> uz(Norm.Normalizing());
      vec3<DBL> a;
      if (uz[0] == 0 && uz[1] == 0)
        a = vec3<DBL>(0, 1, 0);
      else
        a = vec3<DBL>(1, 0, 0);

      const vec3<DBL>
        ux((a % uz).Normalizing()),
        uy((uz % ux));
      const DBL
        r = sqrt(GetU(0, 1)) * Rad,
        teta = GetU(-PI, PI);
      const vec3<DBL> v(r * cos(teta), sin(teta) * r, 0);

      return vec3<DBL>(v & ux, v & uy, v & uz) + Pos;
    } /* End of 'RandomUniformPointOnDisk' function */

    /* Gaussian distribution random point on disk.
     * ARGUMENTS:
     *   - position center disk:
     *      const vec3<DBL> Pos;
     *   - surface normal:
     *       const vec3<DBL> Norm;
     *   - radius disk:
     *       const DBL Rad;
     * RETURNS:
     *   (vec3<DBL>) vector result.
     */
#ifdef __CUDA__
    __host__ __device__
#endif /* __CUDA__ */
    vec3<DBL> RandomGaussianPointOnDisk( const vec3<DBL> &Pos, const vec3<DBL> &Norm, const DBL Rad ) noexcept
    {
      const vec3<DBL> uz(Norm.Normalizing());
      vec3<DBL> a;
      if (uz[0] == 0 && uz[1] == 0)
        a = vec3<DBL>(0, 1, 0);
      else
        a = vec3<DBL>(1, 0, 0);

      const vec3<DBL>
        ux((a % uz).Normalizing()),
        uy((uz % ux));
      const DBL
        f = GetG(0, Rad / 3),
        teta = GetU(-PI, PI);
      const vec3<DBL> v(f * cos(teta), sin(teta) * f, 0);
      return vec3<DBL>(v & ux, v & uy, v & uz) + Pos;
    } /* End of 'RandomGaussianPointOnDisk' function */

  }; /* End of 'random_generator' class */
} /* end of 'mth' namespace */

#endif /* __mth_rand_h_ */

/* END OF 'mth_rand.h' FILE */
