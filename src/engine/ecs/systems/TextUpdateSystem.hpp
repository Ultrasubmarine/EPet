//
//  TextUpdateSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 03.10.2026.
//

#ifndef TextUpdateSystem_hpp
#define TextUpdateSystem_hpp

#include "ISystem.hpp"
#include "CommonComponents.hpp"

class IRender;
class ResourceManager;

class TextUpdateSystem : public ISystem
{
    SYSTEM_BODY(TextUpdateSystem)
public:
    void Start() override;
    void Update(double dt) override;
    
private:
    
    void UpdateText();
    void UpdateFont();
    void UpdateFontSetting();
    void UpdateRenderTexture();
    
    ResourceManager* _resourceManager;
};

#endif /* TextUpdateSystem_hpp */
