//
//  View.cpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#include <iostream>

#include "View.hpp"
#include "PetInfo.hpp"

void View::Draw()
{
    //tmp
    std::cout << PetInfo::Instance().GetAvatar();
};
