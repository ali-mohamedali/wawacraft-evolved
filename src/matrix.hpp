#ifndef MATRIX_H
#define MATRIX_H

#include "libs.hpp"
#include "vector.hpp"

namespace math{
  template<typename type, unsigned int columns, unsigned int rows>
  class matrix{
  public:
    matrix();
    matrix(type[rows*columns]);

    void set(unsigned int, unsigned int, type);

    unsigned int rows_get();
    unsigned int columns_get();
    
    type get(unsigned int, unsigned int);

    matrix add(const matrix&);
    matrix subtract(const matrix&);
    matrix product(const matrix&);
    matrix scale(type);
    matrix<type, rows, columns> transpose();

    math::vector<type, columns> product(const math::vector<type, columns>&);

    type* address();
    type& operator[](const unsigned int&);

    matrix operator+(const matrix&);
    matrix operator-(const matrix&);
    matrix operator*(const matrix<type, columns, rows>&);
    math::vector<type, columns> operator*(const math::vector<type, columns>&);
    matrix operator*(type);
  private:
    type data[rows*columns];
  };

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, columns, rows>::matrix()
  {
    for(int x=0; x<rows*columns; x++){
      data[x]=0;
    }
  }

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, columns, rows>::matrix(type g_init[rows*columns])
  {
    for(int i=0; i<rows*columns; i++){
      data[i]=g_init[i];
    }
  }

  template<typename type, unsigned int columns, unsigned int rows>
  void matrix<type, columns, rows>::set(unsigned int i, unsigned int j, type value)
  {
    data[(j%rows)*columns+(i%columns)]=value;
  }

  template<typename type, unsigned int columns, unsigned int rows>
  unsigned int matrix<type, columns, rows>::rows_get()
  {
    return rows;
  }

  template<typename type, unsigned int columns, unsigned int rows>
  unsigned int matrix<type, columns, rows>::columns_get()
  {
    return columns;
  }

  template<typename type, unsigned int columns, unsigned int rows>
  type matrix<type, columns, rows>::get(unsigned int i, unsigned int j)
  {
    return data[((j%rows)*columns)+(i%columns)];
  }

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, columns, rows> matrix<type, columns, rows>::add(const matrix<type, columns, rows>& lhs)
  {
    matrix<type, columns, rows> accumulate;
    
    if(lhs.rows_get()==rows && lhs.columns_get()==columns){
      for(int j=0; j<rows; j++){
	for(int i=0; i<columns; i++){
	  accumulate.set(i, j, data[i+j*columns]+lhs[i+j*columns]);
	}
      }
    }

    return accumulate;
  }

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, columns, rows> matrix<type, columns, rows>::subtract(const matrix<type, columns, rows>& lhs)
  {
    matrix<type, columns, rows> accumulate;
    
    if(lhs.rows_get()==rows && lhs.columns_get()==columns){
      for(int j=0; j<rows; j++){
	for(int i=0; i<columns; i++){
	  accumulate.set(i, j, data[i+j*columns]-lhs[i+j*columns]);
	}
      }
    }

    return accumulate;
  }

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, columns, rows> matrix<type, columns, rows>::product(const matrix<type, columns, rows>& lhs)
  {
    matrix<type, columns, rows> accumulate;
    
    if(lhs.rows_get()==columns){
      for(int j=0; j<rows; j++){
	for(int i=0; i<lhs.columns_get(); i++){
	  std::vector<type> a;
	  for(int x=0; x<columns; x++){
	    a.push_back(data[j*columns+x]);
	  }

	  std::vector<type> b;
	  for(int y=0; y<lhs.rows_get(); y++){
	    b.push_back(lhs.get(i, y));
	  }
	  
	  math::vector<type, columns> row_vec(a);
	  math::vector<type, columns> column_vec(b);
	  accumulate.set(i, j, row_vec.dot(column_vec));
	}
      }
    }

    return accumulate;
  }

  template<typename type, unsigned int columns, unsigned int rows>
  math::vector<type, columns> matrix<type, columns, rows>::product(const math::vector<type, columns>& lhs)
  {
    math::vector<type, columns> accumulate;

    if(rows==columns && columns==lhs.size()){
      for(int j=0; j<rows; j++){
	std::vector<type> row;
	for(int i=0; i<columns; i++){
	  row.push_back(data[j*columns+i]);
	}

	math::vector<type, columns> row_vec(row);
	accumulate[j]=lhs.dot(row_vec);
      }
    }

    return accumulate;
  }

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, columns, rows> matrix<type, columns, rows>::scale(type lambda)
  {
    matrix<type, columns, rows> accumulate;

    for(int j=0; j<rows; j++){
      for(int i=0; i<columns; i++){
	accumulate.set(i, j, data[i+j*columns]*lambda);
      }
    }

    return accumulate;
  }

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, rows, columns> matrix<type, columns, rows>::transpose()
  {
    matrix<type, rows, columns> transposed;

    for(int j=0; j<rows; j++){
      for(int i=0; i<columns; i++){
        transposed.set(j, i, data[i+j*columns]);
      }
    }

    return transposed;
  }

  template<typename type, unsigned int columns, unsigned int rows>
  type* matrix<type, columns, rows>::address()
  {
    return data;
  }
  
  template<typename type, unsigned int columns, unsigned int rows>
  type& matrix<type, columns, rows>::operator[](const unsigned int& index)
  {
    return data[index];
  }

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, columns, rows> matrix<type, columns, rows>::operator+(const matrix<type, columns, rows>& lhs)
  {
    return add(lhs);
  }

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, columns, rows> matrix<type, columns, rows>::operator-(const matrix<type, columns, rows>& lhs)
  {
    return subtract(lhs);
  }

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, columns, rows> matrix<type, columns, rows>::operator*(const matrix<type, columns, rows>& lhs)
  {
    return product(lhs);
  }

  template<typename type, unsigned int columns, unsigned int rows>
  math::vector<type, columns> matrix<type, columns, rows>::operator*(const math::vector<type, columns>& lhs)
  {
    return product(lhs);
  }

  template<typename type, unsigned int columns, unsigned int rows>
  matrix<type, columns, rows> matrix<type, columns, rows>::operator*(type lhs)
  {
    return scale(lhs);
  }
}

#endif 
