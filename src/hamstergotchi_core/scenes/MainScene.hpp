//
//  MainScene.hpp
//  EPet
//
//  Created by marina porkhunova on 11.03.2024.
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "Scene.hpp"

class MainScene : public Scene
{
public:    
    MainScene(std::string& id);
    ~MainScene() override;
    
    void Update(double dt) override;
    void Render() override; // TODO: temp place and temp virtual
    
private:
    bool _moveRignt = true;
    std::string _tab =" ";
    std::string _size ="";
    
    void CalculateAnimation();
};
#endif /* MainScene_hpp */
