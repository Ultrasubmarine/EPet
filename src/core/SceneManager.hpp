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
#define FEED_SCENE "food"

class Scene;

class SceneManager: public Singleton<SceneManager>
{
    Scene* _currentScene;
    
    Signal<Scene*> OnCreate;
    Signal<Scene*> OnDestroy;
    
    void DeleteScene();    
public:
    void Init();
    
    void LoadScene(std::string id);
    Scene* GetCurrentScene() {return _currentScene;};
};
#endif /* SceneManager_hpp */
