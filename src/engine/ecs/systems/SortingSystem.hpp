//
//  SortingSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 03.10.2026.
//

#ifndef SortingSystem_hpp
#define SortingSystem_hpp

#include "ISystem.hpp"
#include "CommonComponents.hpp"

class IRender;
class ResourceManager;

class SortingSystem : public ISystem
{
    SYSTEM_BODY(SortingSystem)
public:
    
    void OnSystemsLoaded() override;
    void OnComponentsLoaded() override;
    
    void Start() override;
    void DeInit() override;
    
    void Update(double dt) override;
 
private:
    void UpdateObjectsSorting();
    void OnSortingChanged(entt::registry& registry, entt::entity entity);
    
    void OnSpecialComponentAdded(entt::registry& registry, entt::entity entity);
};

#endif /* SortingSystem_hpp */
