//
//  PetInfo.hpp
//  EPet
//
//  Created by marina porkhunova on 17.12.2023.
//

#ifndef PetStats_hpp
#define PetStats_hpp

#include <stdio.h>
#include <string>

#include "Singleton.hpp"

class PetInfo : public Singleton<PetInfo>
{
    //_hangry = 0;
    //_happy = 0;
    //_year
    std::string _avatar;
protected:
    PetInfo() = default;
    ~PetInfo() = default;
    
public:

    const std::string& GetAvatar() const { return _avatar;};
    void SetAvatar(std::string& avatar);
    
    friend Singleton<PetInfo>;
    
    //TODO: add functions Save() Load()
};
#endif /* PetStats_hpp */
