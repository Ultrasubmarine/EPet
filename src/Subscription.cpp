//
//  Subscription.cpp
//  EPet
//
//  Created by marina porkhunova on 03.12.2023.
//

#include "Subscription.hpp"
#include <list>

Subscription::Subscription(std::function<void()> c) : _callBack(c)
{
}

void Subscription::Reset()
{
    _signal->Unsubscribe(this);
}

void Subscription::Call() const
{
    _callBack();
}


void Signal::Broadcast()
{
    for(const auto& s: _subscribers)
    {
        s->Call();
    }
}

Subscription* Signal::Subscribe(std::function<void()>  callBack)
{
    auto s = new Subscription(callBack);
    _subscribers.push_back(s);
    return s;
}

void Signal::Unsubscribe(const Subscription *subscriber)
{
    _subscribers.remove(subscriber);
    delete subscriber;
}
