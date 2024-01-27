//
//  RequestQueue.hpp
//  EPet
//
//  Created by marina porkhunova on 11.12.2023.
//

#ifndef RequestQueue_hpp
#define RequestQueue_hpp

#include <stdio.h>
#include <vector>

enum class RequestType
{
    Poop,
    Hangry,
    Sick
};

class RequestList
{
    std::vector<RequestType> _requests;
    
public:
    bool AddRequest(RequestType type); //return true if success
    bool RemoveRequest(RequestType type); //return true if success
    
    const std::vector<RequestType>& GetAllRequests() const { return _requests;};
    int GetRequestsAmount(RequestType type) const;
    
    //Debug function
    void Print();
};
#endif /* RequestQueue_hpp */
