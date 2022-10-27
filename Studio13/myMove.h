

#ifndef MYMOVE_H
#define MYMOVE_H


template <typename T>
typename std::remove_reference<T>::type&& myMove(T&& t){
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}



#endif