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
/// Use Signal<> - if your callback has no parameters

//TODO: think about memory
template<typename...Args>
class Signal
{
    class _Subscription
    {
        std::function<void(Args...)> _callBack;
        Signal<Args...> *_signal;
    public:

        _Subscription(std::function<void(Args...)>  callBack, Signal<Args...> *signal): _callBack(callBack),
                                                                                        _signal(signal) {};
        void Call(Args...args) const {_callBack(args...);};
        void Reset() { _signal->Unsubscribe(this);};
    };

    std::list<std::shared_ptr<_Subscription>> _subscribers;
public:
    using Subscription = std::weak_ptr<_Subscription>;
    
    ~Signal();
    void Broadcast(Args... data);
    
    Signal<Args...>::Subscription Subscribe(std::function<void(Args...)> callBack);
    void Unsubscribe(Signal<Args...>::Subscription subscriber);
    void Unsubscribe(Signal<Args...>::_Subscription *subscriber);
};

template<typename ...Args>
void Signal<Args...>::Broadcast(Args... data)
{
    //cycle with the ability to unsubscribe inside Call()
    for (auto it = _subscribers.begin(); it != _subscribers.end(); )
    {
        auto currenteIt = it;
        it++;
        (*currenteIt)->Call(data...);
    }
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
    if(auto& ptr = subscriber.lock())
    {
        this->Unsubscribe(subscriber.lock());
    }
};

template<typename ...Args>
void Signal<Args...>::Unsubscribe(Signal<Args...>::_Subscription *subscriber)
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

#endif /* Subscription_hpp */
