//
//  Scene.hpp
//  EPet
//
//  Created by marina porkhunova on 28.02.2024.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <string>
#include <vector>

class ISystem;

class Scene
{
protected:
    const std::string _id;
    
    std::vector<ISystem*> _allSystems;
    
    std::vector<ISystem*> _initSystems;
    std::vector<ISystem*> _updateSystems;
    std::vector<ISystem*> _deInitSystems;
    
public:
    Scene(std::string& id);
    ~Scene();
        
    void AddSystem(std::string& systemId);
    void AddEntity(std::string& systemId);
    
    void Start() {};
    void Destroy() {};
    
    void Update(double dt){};
    void Render(){}; // TODO: temp place
    
    //TODO:
    //void Serialize(json*);
    
    
    const std::string& GetSceneId() { return _id;} const;
};

#endif /* Scene_hpp */
