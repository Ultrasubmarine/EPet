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
protected:
    const std::string _id;
    std::vector<Objects> _objects;
    
public:
    Scene(std::string& id);
    virtual ~Scene();
        
    virtual void Start() {};
    virtual void Update(double dt){};
    virtual void Render(){}; // TODO: temp place and temp virtual
    
    const std::string& GetSceneId() { return _id;} const;
};

#endif /* Scene_hpp */
