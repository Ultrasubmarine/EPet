//
//  Subscription.hpp
//  EPet
//
//  Created by marina porkhunova on 03.12.2023.
//

#ifndef Subscription_hpp
#define Subscription_hpp

#include <stdio.h>
#include <list>
#include <functional>

template<typename T>
class Signal
{
public:
    class Subscription
    {
        std::function<void(T)> _callBack;
        Signal<T> _signal;
    public:
        Subscription(std::function<void(T)>  callBack): _callBack(callBack){};
        
        void Call(T data) const {_callBack(data);};
        void Reset() { _signal->Unsubscribe(this);};
    };
private:
    std::list<const Subscription*> _subscribers;
public:
    void Broadcast(T data);
    
    Signal<T>::Subscription* Subscribe(std::function<void(T)>  callBack);
    void Unsubscribe(const Signal<T>::Subscription *subscriber);
};



template<typename T>
void Signal<T>::Broadcast(T data)
{
    for(const auto& s: _subscribers)
    {
        s->Call(data);
    };
};

template<typename T>
typename Signal<T>::Subscription* Signal<T>::Subscribe(std::function<void(T)>  callBack)
{
    auto s = new Signal<T>::Subscription(callBack);
    _subscribers.push_back(s);
    return s;
};

template<typename T>
void Signal<T>::Unsubscribe(const Signal<T>::Subscription *subscriber)
{
    _subscribers.remove(subscriber);
    delete subscriber;
};
#endif /* Subscription_hpp */
