#ifndef VECTOR_H
#define VECTOR_H

#include "libs.hpp"

namespace math{
  template<typename type, unsigned int dimension>
  class vector{
  public:
    vector();
    vector(type[dimension]);
    vector(std::vector<type>);

    void set(unsigned int, type);

    unsigned int size();
    
    type get(unsigned int);
    type magnitude();

    type dot(const vector<type, dimension>&);

    vector scale(type);
    vector add(const vector<type, dimension>&);
    vector subtract(const vector<type, dimension>&);
    vector cross(const vector<type, dimension>&);

    type operator*(const vector<type, dimension>&);

    vector operator*(type);
    vector operator+(const vector<type, dimension>&);
    vector operator-(const vector<type, dimension>&);
    vector operator^(const vector<type, dimension>&);
    vector operator~();

    vector norm();
    vector conjugate();

    type& operator[](const unsigned int&);
    
  private:
    type data[dimension];
  };

  template<typename type, unsigned int dimension>
  vector<type, dimension>::vector()
  {
    for(int i=0; i<dimension; i++){
      data[i]=0;
    }
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension>::vector(type g_init[dimension])
  {
    for(int i=0; i<dimension; i++){
      data[i]=g_init[i];
    }
  }
  
  template<typename type, unsigned int dimension>
  vector<type, dimension>::vector(std::vector<type> g_init)
  {
    for(int i=0; i<dimension; i++){
      data[i]=0;
    }
    
    for(int i=0; i<(g_init.size()) && i<dimension; i++){
      data[i]=g_init[i];
    }
  }

  template<typename type, unsigned int dimension>
  void vector<type, dimension>::set(unsigned int index, type value)
  {
    data[index%dimension]=value;
  }

  template<typename type, unsigned int dimension>
  unsigned int vector<type, dimension>::size()
  {
    return dimension;
  }

  template<typename type, unsigned int dimension>
  type vector<type, dimension>::get(unsigned int index)
  {
    return data[index%dimension];
  }

  template<typename type, unsigned int dimension>
  type vector<type, dimension>::magnitude()
  {
    type accumulate=0;
    for(int i=0; i<dimension; i++){
      accumulate+=std::pow(data[i], 2);
    }
    
    accumulate=(type)sqrt(accumulate);

    return accumulate;
  }

  template<typename type, unsigned int dimension>
  type vector<type, dimension>::dot(const vector<type, dimension>& lhs)
  {
    type accumulate=0;
    for(int i=0; (i<dimension && i<lhs.size()); i++){
      accumulate+=data[i]*lhs[i];
    }

    return accumulate;
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::scale(type lambda)
  {
    type accumulate[dimension];

    for(int i=0; i<dimension; i++){
      accumulate[i]=(lambda*data[i]);
    }

    return vector<type, dimension>(accumulate);
  }
  
  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::add(const vector<type, dimension>& lhs)
  {
    type accumulate[dimension];
    
    if(dimension==lhs.size()){
      for(int i=0; i<dimension; i++){
	accumulate[i]=(data[i]+lhs[i]);
      }
    }

    return vector<type, dimension>(accumulate);
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::subtract(const vector<type, dimension>& lhs)
  {
    return *this+lhs.conjugate();
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::cross(const vector<type, dimension>& lhs)
  {
    type accumulate[dimension];
    if(dimension==lhs.size()){
      for(int i=0; i<dimension; i++){
	accumulate[i]=(data[(i+1)%3]*lhs[(i+2)%3]-data[(i+2)%3]*lhs[(i+1)%3]);
      }
    }

    return vector<type, dimension>(accumulate);
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::norm()
  {
    type accumulate[dimension];
    
    for(int i=0; i<dimension; i++){
      accumulate[i]=(data[i]/magnitude());
    }

    return vector<type, dimension>(accumulate);
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::conjugate()
  {
    type accumulate[dimension];
    
    for(int i=0; i<dimension; i++){
      accumulate[i]=(-data[i]);
    }

    return vector<type, dimension>(accumulate);
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::operator*(type lambda)
  {
    return scale(lambda);
  }


  template<typename type, unsigned int dimension>
  type vector<type, dimension>::operator*(const vector<type, dimension>& lhs)
  {
    return dot(lhs);
  }

  template<typename type, unsigned int dimension>
  type& vector<type, dimension>::operator[](const unsigned int& index)
  {
    return data[index%dimension];
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::operator+(const vector<type, dimension>& lhs)
  {
    return add(lhs);
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::operator-(const vector<type, dimension>& lhs)
  {
    return subtract(lhs);
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::operator^(const vector<type, dimension>& lhs)
  {
    return cross(lhs);
  }

  template<typename type, unsigned int dimension>
  vector<type, dimension> vector<type, dimension>::operator~()
  {
    return norm();
  }
}

#endif
