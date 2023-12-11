//
//  RequestQueue.cpp
//  EPet
//
//  Created by marina porkhunova on 11.12.2023.
//

#include "RequestList.hpp"


bool RequestList::AddRequest(RequestType type)
{
    _requests.push_back(type);
    return true;
}

bool RequestList::RemoveRequest(RequestType type)
{
    auto it = std::find(_requests.begin(), _requests.end(), type);
    if(it != _requests.end())
    {
        _requests.erase(it);
        return true;
    }
    return false;
}

#include <iostream>
void RequestList::Print()
{
    if(_requests.empty())
    {
        std::cout<<"requests list is empty\n";
        return;
    }
    
    std::cout<<"requests list:\n";
    for(auto& r: _requests)
    {
        switch (r)
        {
            case RequestType::Poop:
                std::cout<<"    poop\n";
                break;
            case RequestType::Hangry:
                std::cout<<"    hangry\n";
            default:
                std::cout<<"    ???\n";
                break;
        }
    }
}
    
