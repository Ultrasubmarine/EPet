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

class SortingUpdateSystem : public ISystem
{
    SYSTEM_BODY(SortingUpdateSystem)
public:
    void Init() override;
    void Update(double dt) override;
    
    void UpdateObjectsSorting();
};

#endif /* TextSystem_hpp */
