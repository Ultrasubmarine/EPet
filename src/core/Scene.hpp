//
//  Scene.hpp
//  EPet
//
//  Created by marina porkhunova on 28.02.2024.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include <string>

struct Objects
{
    
};

class Scene
{
    const std::string _id;
    std::string _nextSceneId;
    
    std::vector<Objects> _objects;
    
public:
    Scene(std::string& id, std::string& nextSceneId);
    ~Scene();
        
  //  virtual void Update();
    
    const std::string& GetSceneId() { return _id;} const;
    const std::string& GetNextSceneId() { return _nextSceneId;} const;    
};

#endif /* Scene_hpp */
