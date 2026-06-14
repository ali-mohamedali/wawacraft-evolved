#ifndef QUAT_H
#define QUAT_H

#include "libs.hpp"
#include "matrix.hpp"

namespace math{
  template<typename type>
  class quat{
  public:
    quat();
    quat(type, type, type, type);

    static matrix<type, 4, 4> rotation_matrix(const quat&);
    
    void w_set(type);
    void i_set(type);
    void j_set(type);
    void k_set(type);

    quat scale(type);
    quat add(const quat&);
    quat subtract(const quat&);
    quat product(const quat&);
    
    quat conjugate();
    quat versor();
    quat inverse();
    
    type magnitude();
    type mpow2();
    
    type w_get();
    type i_get();
    type j_get();
    type k_get();

    quat operator+(const quat&);
    quat operator*(const quat&);
    quat operator/(const quat&);
    quat operator*(type);
    quat operator~();
    
  private:
    type w;
    type i;
    type j;
    type k;
  };

  template<typename type>
  quat<type>::quat()
  {
    w=i=j=k=0;
  }

  template<typename type>
  quat<type>::quat(type gw, type gi, type gj, type gk):
    w(gw),
    i(gi),
    j(gj),
    k(gk)
  {
    
  }

  template<typename type>
  void quat<type>::w_set(type n)
  {
    w=n;
  }

  template<typename type>
  void quat<type>::i_set(type n)
  {
    i=n;
  }

  template<typename type>
  void quat<type>::j_set(type n)
  {
    j=n;
  }

  template<typename type>
  void quat<type>::k_set(type n)
  {
    k=n;
  }

  template<typename type>
  quat<type> quat<type>::scale(type lambda)
  {
    quat<type> accumulate;
    accumulate.w_set(w*lambda);
    accumulate.i_set(i*lambda);
    accumulate.j_set(j*lambda);
    accumulate.k_set(k*lambda);

    return accumulate;
  }

  template<typename type>
  quat<type> quat<type>::add(const quat& lhs)
  {
    quat<type> accumulate;
    accumulate.w_set(w+lhs.w_get());
    accumulate.i_set(i+lhs.i_get());
    accumulate.j_set(j+lhs.j_get());
    accumulate.k_set(k+lhs.k_get());
    
    return accumulate;
  }

  template<typename type>
  quat<type> quat<type>::subtract(const quat& lhs)
  {
    quat<type> accumulate;
    accumulate.w_set(w-lhs.w_get());
    accumulate.i_set(i-lhs.i_get());
    accumulate.j_set(j-lhs.j_get());
    accumulate.k_set(k-lhs.k_get());
    
    return accumulate;
  }

  template<typename type>
  quat<type> quat<type>::product(const quat& lhs)
  {
    type w2=lhs.w_get();
    type i2=lhs.i_get();
    type j2=lhs.j_get();
    type k2=lhs.k_get();
    
    
    return quat<type>(
     (w*w2-i*i2-j*j2-k*k2),
     (w*i2+w2*i+j*k2-j2*k),
     (w*j2+w2*j+k*i2-k2*i),
     (w*k2+w2*k+i*j2-i2*j));
  }

  template<typename type>
  quat<type> quat<type>::conjugate()
  {
    return quat<type>(w, -i, -j, -k);
  }

  template<typename type>
  quat<type> quat<type>::versor()
  {
    type m=magnitude();
    m=(m==0 ? 1 : m);
    
    return quat<type>(w/m, i/m, j/m, k/m);
  }

  template<typename type>
  quat<type> quat<type>::inverse()
  {
    type m=-mpow2();
    m=(m==0 ? -1 : m);

    return quat<type>(-w/m, i/m, j/m, k/m); 
  }

  template<typename type>
  type quat<type>::magnitude()
  {
    return sqrt(mpow2());
  }

  template<typename type>
  type quat<type>::mpow2()
  {
    return w*w+i*i+j*j+k*k;
  }

  template<typename type>
  type quat<type>::w_get()
  {
    return w;
  }

  template<typename type>
  type quat<type>::i_get()
  {
    return i;
  }

  template<typename type>
  type quat<type>::j_get()
  {
    return j;
  }

  template<typename type>
  type quat<type>::k_get()
  {
    return k;
  }

  template<typename type>
  quat<type> quat<type>::operator+(const quat& lhs)
  {
    return add(lhs);
  }

  template<typename type>
  quat<type> quat<type>::operator*(const quat& lhs)
  {
    return product(lhs);
  }

  template<typename type>
  quat<type> quat<type>::operator/(const quat& lhs)
  {
    return product(lhs.inverse());
  }

  template<typename type>
  quat<type> quat<type>::operator*(type lambda)
  {
    return scale(lambda);
  }

  template<typename type>
  quat<type> quat<type>::operator~()
  {
    return conjugate();
  }

  template <typename type>
  matrix<type, 4, 4> quat<type>::rotation_matrix(const quat& g)
  {
    type w=g.w_get();
    type i=g.i_get();
    type j=g.j_get();
    type k=g.k_get();
    
    type accumulate[16]=
      {(w*w+i*i-j*j-k*k),
          2*(i*j)-2*(w*k),
	    2*(i*k)+2*(w*j),
	      0,
       2*(i*j)+2*(w*k),
         (w*w-i*i+j*j-k*k),
	   2*(j*k)-2*(w*i),
	     0,
       2*(i*k)-2*(w*j),
         2*(j*k)+2*(w*i),
	   (w*w-i*i-j*j+k*k),
	     0,
       0, 0, 0, 1};
    
    return matrix<type, 4, 4>(accumulate);
  }
}

#endif
