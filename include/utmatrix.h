﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  void SetValueToVector(const ValType& val);
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << '\t';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) :Size(s), StartIndex(si)
{
  if (si < 0 || si + s> MAX_VECTOR_SIZE)
    throw exception();
  if (s < 0 || s > MAX_VECTOR_SIZE) 
    throw exception();
  pVector = new ValType [Size];
  for (size_t i = 0 ;i < Size; i++)
  {
    pVector[i] = 0;
  }

} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
  Size = v.Size;
  StartIndex = v.StartIndex;
  pVector = new ValType[Size];
  for (size_t i = 0; i < Size; i++)
  {
    pVector[i] = v.pVector[i];
  }
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
  if (pVector != nullptr)
    pVector = nullptr;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
  if (pos -StartIndex >= Size || pos-StartIndex < 0)
    throw exception();
  return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
  if (v.Size != Size)
    return false;
  for (size_t i = 0; i < v.Size; i++)
  {
    if (v.pVector[i] != pVector[i])
      return false;
  }
  return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
  if (v == *this)
    return false;
  return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{//
  if (*this == v)
    return *this;
  if (v.Size != Size)
  {
    if (pVector != nullptr)
      pVector = nullptr;
    Size = v.Size;
    pVector = new ValType[Size];
  }
  StartIndex = v.StartIndex;
  for (size_t i = 0; i < Size; i++)
  {
    pVector[i] = v.pVector[i];
  }
  return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
  TVector<ValType>temp(*this);
  for (size_t i = 0; i < Size; i++)
  {
    temp.pVector[i] += val;
  }
  return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
  TVector<ValType>temp(*this);
  for (size_t i = 0; i < Size; i++)
  {
    temp.pVector[i] -= val;
  }
  return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
  TVector<ValType>temp(*this);
  for (size_t i = 0; i < Size; i++)
  {
    temp.pVector[i] *= val;
  }
  return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
  if (Size != v.Size)
    throw exception();
  TVector<ValType>temp(*this);
  for (size_t i = 0; i < Size; i++)
  {
    temp.pVector[i] =temp.pVector[i]+ v.pVector[i];
  }
  return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
  if (Size != v.Size)
    throw exception();
  TVector<ValType>temp(*this);
  for (size_t i = 0; i < Size; i++)
  {
    temp.pVector[i] = temp.pVector[i] - v.pVector[i];
  }
  return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
  if (Size != v.Size)
    throw exception();
  ValType ans =pVector[0] * v.pVector[0];
  for (size_t i = 1; i < Size; i++)
  {
    ans += pVector[i] * v.pVector[i];
  }
  return ans;
} /*-------------------------------------------------------------------------*/

template<class ValType>
inline void TVector<ValType>::SetValueToVector(const ValType& val)
{
  for (size_t i = 0; i < Size; i++)
  {
    pVector[i] = val;
  }
}


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
  
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << "\n";
    return out;
  }

};
template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{ 
  if(s> MAX_MATRIX_SIZE|| s<0)
    throw exception();
  for (int i = 0; i < s; i++)
    pVector[i] = TVector<ValType>(s - i, i);
} /*-------------------------------------------------------------------------*/


template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}//?

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
  if (Size != mt.Size)
    return false;
  for (size_t i = 0; i < Size; i++)
  {
    if (pVector[i] != mt.pVector[i])
      return false;
  }
  return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
  if (*this == mt)
    return false;
  return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
  if (this == &mt)
    return *this;
  if (pVector != nullptr)
    delete[]pVector;
  TVector<TVector<ValType>>::operator=(mt);
  return *this;
  
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
  TVector<TVector<ValType>>temp(*this);
  temp = temp + mt;
  return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
  TVector<TVector<ValType>>temp(*this);
  temp = temp - mt;
  return temp;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
