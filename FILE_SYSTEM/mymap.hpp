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
#include "Library_Template.hpp"
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
    int cur_sz;
    std::pair<Key, T> * array;
    typedef std::pair<const Key, T> __pair;
    friend class MyMapIt<__pair>;
public:
    MyMap(): occup(0), cur_sz(QUANT), array(new __pair[QUANT]){}
    
    typedef MyMapIt<__pair> Myiterator;
    
    std::pair<Myiterator, bool> __insert(__pair &value);
    
    void __clear();
    
    bool __erase(Myiterator position);
    
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
    cur_sz = 0;
}

template <class k, class t>
MyMapIt<std::pair<const k, t>> MyMap<k, t>::find(const k& __key){
    MyMapIt __first(this->array[0].first);
    MyMapIt __last(this->array[occup].first);
    
    __first = std::lower_bound(__first, __last, __key);
    if (__first != __last && !(__key < __first->first))
        return __first;
    else
        return __last;
}

template <class k, class t>
std::pair<MyMapIt<std::pair<const k, t>>, bool> MyMap<k, t>::__insert(std::pair<const k, t> &value){
    if (occup < cur_sz){
        array[occup + 1].first = value.first;
        array[occup + 1].second = value.second;
        if (array[occup + 1].first == value.first && array[occup + 1].second == value.second){
            occup++;
            this->std::stable_sort(MyMapIt(this->array[0].first), MyMapIt(this->array[occup].first));
            
            return std::make_pair(MyMapIt(array[occup].first), true);
        }
        else
            return std::make_pair(MyMapIt(array[occup].first), false);
    }
    else{
        cur_sz += QUANT;
        array = ltmp::renew(array, cur_sz);
        
        array[occup + 1].first = value.first;
        array[occup + 1].second = value.second;
        if (array[occup + 1].first == value.first && array[occup + 1].second == value.second){
            occup++;
            this->std::stable_sort(MyMapIt(this->array[0].first), MyMapIt(this->array[occup].first));
            
            return std::make_pair(MyMapIt(array[occup].first), true);
        }
        else
            return std::make_pair(MyMapIt(array[occup].first), false);
    }
}

template <class k, class t>
bool MyMap<k, t>::__erase(MyMapIt<std::pair<const k, t>> position){
    if (cur_sz > 0){
        if(std::binary_search(MyMapIt(this->array[0].first), MyMapIt(this->array[occup].first), position->first)){
            int new_sz = occup - 1;
            std::pair<k, t> * tmp = new std::pair<k, t>[new_sz];
            std::pair<k, t> * swp = array;
            
            int i;
            for (i = 0; array[i].first < position->first; i++){
                tmp[i].first = array[i].first;
                tmp[i].second = array[i].second;
            }
            int j = i;
            for (i += 1; i < occup; i++){
                tmp[j].first = array[i].first;
                tmp[j].second = array[i].second;
                j++;
            }
            array = tmp;
            delete [] swp;
            
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
//--------------------------------------------------------------------------------------



#endif /* mymap_hpp */
