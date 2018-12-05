//
//  mymap.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 05/12/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef mymap_hpp
#define mymap_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
//--------------------------------------------------------------------------------------
//template class pair for map
template <class Key, class Data>
class __pair {
private:
    Key first;
    Data second;
public:
    __pair(Key &__x, Data &__y): first(__x), second(__y){};
};
//--------------------------------------------------------------------------------------
//template iterator for map
template <class T>
class MyMapIt{
private:
    T * current;
public:
    MyMapIt(): current(nullptr){};
    MyMapIt(T *object): current(object){};
    
    const T& operator *( ) const;
    MyMapIt& operator ++( );
    MyMapIt operator ++(int);
    int operator !=(const MyMapIt &) const;
    int operator ==(const MyMapIt &) const;
};
//===-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-===
template <class T>
const T& MyMapIt<T>::operator *( ) const{
    return *current;
}

template <class T>
MyMapIt<T> & MyMapIt<T>::operator ++( ){
    current++;
    return *this;
}

template <class T>
MyMapIt<T> MyMapIt<T>::operator ++(int){
    MyMapIt<T> res(*this);
    ++current;
    return res;
}
    
template <class T>
int MyMapIt<T>::operator !=(const MyMapIt<T> &it) const{
    return current != it.current;
}

template <class T>
int MyMapIt<T>::operator ==(const MyMapIt<T> &it) const{
    return current == it.current;
}
//--------------------------------------------------------------------------------------
//template map
template <class Key, class T>
class MyMap{
private:
    static const int QUANT = 30;
    int occup;
    std::pair<Key, T> * array;
    typedef std::pair<const Key, T> __pair;
    friend class MyMapIt<__pair>;
public:
    MyMap(): occup(0), array(new __pair[QUANT]){}
    
    typedef MyMapIt<__pair> Myiterator;
    
    std::pair<Myiterator, bool> __insert(__pair &value);
    
    void __clear();
    
    Myiterator __erase(Myiterator position);
    Myiterator __erase(Myiterator first, Myiterator last);
    
    Myiterator __begin() const;
    Myiterator __end() const;
    
    Myiterator find(const Key& __key);
};
//===-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-===
template <class k, class t>
MyMapIt<std::pair<const k, t>> MyMap<k ,t>::__begin() const{
    return MyMapIt(this->array[0].first);
}

template <class k, class t>
MyMapIt<std::pair<const k, t>> MyMap<k, t>::__end() const{
    return MyMapIt(this->array[occup].first);
}
    
template <class k, class t>
void MyMap<k, t>::__clear(){
    delete [] array;
    occup = 0;
}

template <class k, class t>
MyMapIt<std::pair<const k, t>> MyMap<k, t>::find(const k& __key){
    // бинарный поиск
}

template <class k, class t>
std::pair<MyMapIt<std::pair<const k, t>>, bool> MyMap<k, t>::__insert(std::pair<const k, t> &value){
    this->stable_sort(array[0].first, array[occup].first);
}

template <class k, class t>
MyMapIt<std::pair<const k, t>> MyMap<k, t>::__erase(MyMapIt<std::pair<const k, t>> position){
    
}

template <class k, class t>
MyMapIt<std::pair<const k, t>> MyMap<k, t>::__erase(MyMapIt<std::pair<const k, t>> first, MyMapIt<std::pair<const k, t>> last){
    
}
//--------------------------------------------------------------------------------------



#endif /* mymap_hpp */
