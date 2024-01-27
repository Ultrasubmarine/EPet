//
//  View.hpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#ifndef View_hpp
#define View_hpp

#include <stdio.h>

class View
{
public:
    void Draw();
    void Update();
    
    // tmp simple animation
private:
    bool _moveRignt = true;
    std::string _tab =" ";
    std::string _size ="";
    
    void CalculateAnimation();    
};
#endif /* View_hpp */
