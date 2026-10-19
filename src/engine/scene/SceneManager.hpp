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

class SceneManager
{
    Scene* _currentScene;
    
    Signal<Scene*> OnCreate;
    Signal<Scene*> OnDestroy;
    
    entt::registry _registry;

public:
    
    SceneManager();
    ~SceneManager();
    
    void LoadScene(std::string id);
    void SaveScene(); // current
    
    Scene* GetCurrentScene() {return _currentScene;};
    entt::registry& GetRegistry() {return _registry;};
    
    void Update(double dt);
    
private:
    void DeleteScene();
};

#endif /* SceneManager_hpp */
