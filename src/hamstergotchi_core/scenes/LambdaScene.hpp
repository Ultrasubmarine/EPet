//
//  LambdaScene.hpp
//  EPet
//
//  Created by marina porkhunova on 12.04.2024.
//

#ifndef LambdaScene_hpp
#define LambdaScene_hpp

#include <stdio.h>
#include <functional>

#include "Scene.hpp"

class LambdaScene : public Scene
{
    std::function<void()> _onStart;
    std::function<void(double)> _onUpdate;
    std::function<void()> _onDestroy;
    
public:
    LambdaScene(std::string& id, std::function<void()> startCallback = nullptr,
                                 std::function<void(double)> updateCallback = nullptr,
                                 std::function<void()> destroyCallback = nullptr);
    ~LambdaScene() override;
    
    void Start() override;
    void Update(double dt) override;
    void Render() override; // TODO: temp place and temp virtual
 
    double i = 0 ;
};
#endif /* LambdaScene_hpp */
