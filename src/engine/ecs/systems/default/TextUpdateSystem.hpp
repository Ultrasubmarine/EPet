//  TextSystem.hpp
//  EPet
//
//  Создано по аналогии с RenderSystem.hpp
//

#ifndef TextSystem_hpp
#define TextSystem_hpp

#include "ISystem.hpp"
#include "CommonComponents.hpp"

class IRender;
class ResourceManager;

class TextUpdateSystem : public ISystem
{
    SYSTEM_BODY(TextUpdateSystem)
public:
    void Init() override;
    void Update(double dt) override;
    
private:
    
    void UpdateText();
    void UpdateFont();
    void UpdateRenderTexture();
    
    ResourceManager* _resourceManager;
};

#endif /* TextSystem_hpp */
