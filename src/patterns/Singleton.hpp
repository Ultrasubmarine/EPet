//
//  Singleton.hpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#ifndef Singletone_hpp
#define Singletone_hpp

#include <stdio.h>

//Lazy initialization
template <class T>
class Singleton
{
public:
    static T& Instance();
    static void Destroy();
    
protected:
    Singleton() = default;
    ~Singleton() = default;
    
    static T *_instance;
};

template<class T>
T& Singleton<T>::Instance()
{
    if(!_instance)
    {
        _instance = new T();
    }
    return *_instance;
}

template<class T>
void Singleton<T>::Destroy()
{
    if(!_instance)
    {
        delete _instance;
        _instance = nullptr;
    }
}

template<class T>
T* Singleton<T>::_instance = nullptr;
#endif /* Singletone_hpp */
