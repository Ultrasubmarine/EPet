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
    class _Subscription
    {
        std::function<void(Args...)> _callBack;
        Signal<Args...> *_signal;
    public:

        _Subscription(std::function<void(Args...)>  callBack, Signal<Args...>* signal): _callBack(callBack),
                                                                                        _signal(signal) {};
        void Call(Args...args) const {_callBack(args...);};
        void Reset() { _signal->Unsubscribe(this);};
    };
public:
    using Subscription = std::weak_ptr<_Subscription>;
    
    ~Signal();
private:
    std::list<std::shared_ptr<_Subscription>> _subscribers;
public:
    void Broadcast(Args... data);
    
    Signal<Args...>::Subscription Subscribe(std::function<void(Args...)> callBack);
    void Unsubscribe(Signal<Args...>::Subscription subscriber);
    void Unsubscribe(Signal<Args...>::_Subscription* subscriber);
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
typename Signal<Args...>::Subscription Signal<Args...>::Subscribe(std::function<void(Args...)> callBack)
{
    auto s = std::make_shared<Signal<Args...>::_Subscription>(callBack, this);
    _subscribers.push_back(s);
    return Signal<Args...>::Subscription(s);
};

template<typename ...Args>
void Signal<Args...>::Unsubscribe(const Signal<Args...>::Subscription subscriber)
{
    if(auto ptr = subscriber.lock())
    {
        this->Unsubscribe(subscriber.lock());
    }
};

template<typename ...Args>
void Signal<Args...>::Unsubscribe(Signal<Args...>::_Subscription* subscriber)
{
    auto it = std::find_if(_subscribers.begin(), _subscribers.end(),
                           [subscriber](auto& ptr){ return ptr.get() == subscriber; });

    if(it != _subscribers.end())
    {
        _subscribers.erase(it);
    }
}

template<typename ...Args>
Signal<Args...>::~Signal()
{
    _subscribers.clear();
};


//empty functions realization.
//this code breaks a DRY rule. but template couldn't create subscription for function() witn no parameters without it
template<>
class Signal<void>
{
public:
    class _Subscription
    {
        std::function<void()> _callBack;
        Signal<void> *_signal;
    public:

        _Subscription(std::function<void()>  callBack, Signal<void> *signal): _callBack(callBack),                                                                                                                                                           _signal(signal) {};
        void Call() const {_callBack();};
        void Reset() { };//_signal->Unsubscribe(this);};
    };
public:
    using Subscription = std::weak_ptr<_Subscription>;

private:
    std::list<std::shared_ptr<_Subscription>> _subscribers;
public:
    ~Signal()
    {
        _subscribers.clear();
    };

    void Broadcast()
    {
        for(const auto& s: _subscribers)
        {
            s->Call();
        };
    };

    Signal<void>::Subscription Subscribe(std::function<void()>  callBack)
    {
        auto s = std::make_shared<_Subscription>(callBack, this);
        _subscribers.push_back(s);
        return Signal<void>::Subscription(s);
    };

    void Unsubscribe(Signal<void>::Subscription subscriber)
    {
        if(auto s = subscriber.lock())
        {
            Unsubscribe(s);
        }
        
    };
    void Unsubscribe(Signal<void>::_Subscription* subscriber)
    {
        auto it = std::find_if(_subscribers.begin(), _subscribers.end(),
                               [subscriber](auto ptr){ return ptr.get() == subscriber; });

        if(it != _subscribers.end())
        {
            _subscribers.erase(it);
        }
    };
};
#endif /* Subscription_hpp */
