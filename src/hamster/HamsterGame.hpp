//
//  HamsterGame.hpp
//  EPet
//
//  Created by marina porkhunova on 23.09.2026.
//

#ifndef HamsterGame_hpp
#define HamsterGame_hpp

#include "Singleton.hpp"
#include "HamsterAnimationDictionary.hpp"

class ResourceManager;

/// holder for specific systems in tamagotchi game
class HamsterGame final: public Singleton<HamsterGame>
{
public:
    bool Init(ResourceManager* resourceManager);

    HamsterAnimationDictionary& GetAnimationDictionary() { return _animationDictionary; }

private:
    HamsterAnimationDictionary _animationDictionary;
};

#endif /* HamsterGame_hpp */
