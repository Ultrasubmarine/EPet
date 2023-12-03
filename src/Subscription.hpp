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


/// Use Signal<...Args> - to subject witch broadcast signal. <...Args> - parameters to your callback function
/// Use Signal<...Args>::Subscription - in your listener to subscribe on signal
/// Use Signal<void> - if your callback has no parameters

//TODO think about memory
template<typename...Args>
class Signal
{
public:
    class Subscription
    {
        std::function<void(Args...)> _callBack;
        Signal<Args...> *_signal;
    public:
        Subscription(std::function<void(Args...)>  callBack): _callBack(callBack){};
        
        void Call(Args...args) const {_callBack(args...);};
        void Reset() { _signal->Unsubscribe(this);};
    };
private:
    std::list<const Subscription*> _subscribers;
public:
    void Broadcast(Args... data);
    
    Signal<Args...>::Subscription* Subscribe(std::function<void(Args...)>  callBack);
    void Unsubscribe(const Signal<Args...>::Subscription *subscriber);
};

template<typename ...Args>
void Signal<Args...>::Broadcast(Args... data)
{
    for(const auto& s: _subscribers)
    {
        s->Call(data...);
    };
};

template<typename ...Args>
typename Signal<Args...>::Subscription* Signal<Args...>::Subscribe(std::function<void(Args...)>  callBack)
{
    auto s = new Signal<Args...>::Subscription(callBack);
    _subscribers.push_back(s);
    return s;
};

template<typename ...Args>
void Signal<Args...>::Unsubscribe(const Signal<Args...>::Subscription *subscriber)
{
    _subscribers.remove(subscriber);
    delete subscriber;
};


//empty functions realization.
//this code breaks a DRY rule. but template couldn't create subscription for function() witn no parameters without it
template<>
class Signal<void>
{
public:
    class Subscription
    {
        std::function<void()> _callBack;
        Signal<void> *_signal;
    public:
        Subscription(std::function<void()>  callBack): _callBack(callBack){};
        
        void Call() const {_callBack();};
        void Reset() { _signal->Unsubscribe(this);};
    };
private:
    std::list<const Subscription*> _subscribers;
public:
    void Broadcast()
    {
        for(const auto& s: _subscribers)
        {
            s->Call();
        };
    };
    
    Signal<void>::Subscription* Subscribe(std::function<void()>  callBack)
    {
        auto s = new Signal<void>::Subscription(callBack);
        _subscribers.push_back(s);
        return s;
    };
    
    void Unsubscribe(const Signal<void>::Subscription *subscriber)
    {
        _subscribers.remove(subscriber);
        delete subscriber;
    };
};
#endif /* Subscription_hpp */
