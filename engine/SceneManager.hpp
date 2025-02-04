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

#include "ISystem.hpp"
#include "FactoryMethod.hpp"


class Scene;
class ResourceManager;
class ISystem;

class SceneManager
{    
    ResourceManager* _resourceManager;
    Scene* _currentScene;
    
    Signal<Scene*> OnCreate;
    Signal<Scene*> OnDestroy;
    
    void DeleteScene();

public:
    
    SceneManager(ResourceManager* r);
    void LoadScene(std::string id);
    Scene* GetCurrentScene() {return _currentScene;};
};


#endif /* SceneManager_hpp */
