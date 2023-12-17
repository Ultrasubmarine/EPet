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
    void Update();
    
// tmp simple animation
private:
    bool _moveRignt = true;
    std::string _tab =" ";
    
    void CalculateAnimation();
    
};
#endif /* View_hpp */
