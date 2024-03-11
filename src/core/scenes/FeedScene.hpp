//
//  FeedingScene.hpp
//  EPet
//
//  Created by marina porkhunova on 11.03.2024.
//

#ifndef FeedingScene_hpp
#define FeedingScene_hpp

#include <stdio.h>
#include "Scene.hpp"

class FeedScene : public Scene
{
    const int _foodId;
    std::vector<Objects> _objects;
     
public:
    
    FeedScene(std::string& id, int foodId);
    ~FeedScene() override;
    
    void Start() override;
    void Update(double dt) override;
    void Render() override; // TODO: temp place and temp virtual
  
private:
    double _animationTime = 5;
    
    double _mouthTime = 0.6;
    double _currentMouthTime = 0;
    bool _bigMouth = true;
    
};
#endif /* FeedingScene_hpp */
