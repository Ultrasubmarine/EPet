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

class TextSystem : public ISystem
{
    SYSTEM_BODY(TextSystem)
public:
    void Init() override;
    void Update(double dt) override;
    
private:
    
    ResourceManager* _resourceManager;
};

#endif /* TextSystem_hpp */
