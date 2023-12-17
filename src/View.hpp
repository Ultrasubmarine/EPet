//
//  View.hpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#ifndef View_hpp
#define View_hpp

#include <stdio.h>

class RequestList;

class View
{
    RequestList *_requestList;
    
public:
    View(RequestList *requestList):_requestList(requestList) {};
    void Draw();
    
};
#endif /* View_hpp */
