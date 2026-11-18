//
//  ImageLoadSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 03.10.2026.
//

#ifndef ImageLoadSystem_hpp
#define ImageLoadSystem_hpp

#include "ISystem.hpp"
#include "CommonComponents.hpp"

class IRender;
class ResourceManager;

class ImageLoadSystem : public ISystem
{
    SYSTEM_BODY(ImageLoadSystem)
public:
    void Start() override;
    void Update(double dt) override;
    
private:
    
    ResourceManager* _resourceManager;
};

#endif /* ImageLoadSystem_hpp */
