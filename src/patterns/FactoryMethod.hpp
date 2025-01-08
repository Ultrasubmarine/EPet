//
//  FactoryMethod.hpp
//  Labirint
//
//  Created by marina porkhunova on 07.02.2023.
//

#ifndef FactoryMethod_hpp
#define FactoryMethod_hpp

#include <stdio.h>
#include <unordered_map>
/// Facroty
/// @arg TKey - me
template<typename TKey, typename TBase, typename...TCreateMethodArgs>
class FactoryMethod
{
     using TCreateMethod = TBase*(*)(TCreateMethodArgs...);
public:
    
    bool Register(TKey k, TCreateMethod createFunc);
    TBase* Create(TKey k,TCreateMethodArgs... args);
    
    ~FactoryMethod() { _theMap.clear(); };
protected:
    std::unordered_map<TKey,TBase*(*)(TCreateMethodArgs...)> _theMap;
};

template<typename Key, typename TBase, typename...TCreateMethodArgs>
bool FactoryMethod<Key, TBase, TCreateMethodArgs...>::Register(Key k, TCreateMethod createFunc)
{
    if(_theMap.find(k) != _theMap.end())
        return false;
    
    _theMap[k] = createFunc;
    return true;
}

template<typename Key, typename TBase, typename...TCreateMethodArgs>
TBase* FactoryMethod<Key, TBase, TCreateMethodArgs...>::Create(Key k, TCreateMethodArgs... args)
{
    if(auto it = _theMap.find(k); it != _theMap.end())
    {
        return it->second(args...);
    }
 
    return nullptr;
}

//template<typename Key, typename TBase, typename...TCreateMethodArgs>
//std::unordered_map<Key, TBase*(*)(TCreateMethodArgs...)>& FactoryMethod<Key, TBase, TCreateMethodArgs...>::TheMap()
//{
//    std::unordered_map<Key, TBase*(*)(TCreateMethodArgs...)> _creators{};
//    return _creators;
//}

#endif /* FactoryMethod_hpp */
