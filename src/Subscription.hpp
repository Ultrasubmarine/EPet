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

class Signal;


template<class T>
class Subscription2
{
    std::function<void(T)> f;
};

//template<class T>
class Subscription
{
    std::function<void()> _callBack;
    Signal *_signal;
    
public:
    Subscription(std::function<void()> callBack);
    
    void Call() const;
    void Reset();
};


class Signal
{
    std::list<const Subscription*> _subscribers;
    Subscription2<int> s;
public:
    void Broadcast();
    
    Subscription* Subscribe(std::function<void()> callBack);
    void Unsubscribe(const Subscription *subscriber);
};
#endif /* Subscription_hpp */
