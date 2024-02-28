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

#include "Singleton.hpp"
#include "Subscription.hpp"

#define DEFAULT_SCENE "default"
class Scene;

class SceneManager: public Singleton<SceneManager>
{
    Scene* _currentScene;
    
    Signal<> OnCreate;
    Signal<> OnDestroy;
    
    void DeleteScene();    
public:
    void Init();
    
    void LoadScene(std::string id, std::string nextId = std::string(DEFAULT_SCENE));
    
    Scene* GetCurrentScene() {return _currentScene;};
};
#endif /* SceneManager_hpp */
