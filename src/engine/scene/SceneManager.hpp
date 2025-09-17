//
//  SceneManager.hpp
//  EPet
//
//  Created by marina porkhunova on 28.02.2024.
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>
#include <string>

#include "Subscription.hpp"
#include "registry.hpp" // TODO: think about place

class Scene;
class ResourceManager;

class SceneManager
{    
    ResourceManager* _resourceManager;
    Scene* _currentScene;
    
    Signal<Scene*> OnCreate;
    Signal<Scene*> OnDestroy;
    
    entt::registry _registry;

public:
    
    SceneManager(ResourceManager* r);
    ~SceneManager();
    
    void LoadScene(std::string id);
    void SaveScene(); // current
    
    Scene* GetCurrentScene() {return _currentScene;};
    
    void Update(double dt);
    
private:
    void DeleteScene();
};

#endif /* SceneManager_hpp */
