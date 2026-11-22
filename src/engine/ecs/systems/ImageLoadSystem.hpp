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
    void OnSystemsLoaded() override;
    void Start() override;
    void DeInit() override;
    void Update(double dt) override;
    
private:
    void LoadImage(Image& image, RendererObject& obj);
    void OnImageChanged(entt::registry& registry, entt::entity entity);
    
    ResourceManager* _resourceManager = nullptr;
};

#endif /* ImageLoadSystem_hpp */
