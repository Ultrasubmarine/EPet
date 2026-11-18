//
//  SortingTestSystem.hpp
//  EPet
//
//  Created by marina porkhunova on 16.11.2026.
//

#ifndef SortingTestSystem_hpp
#define SortingTestSystem_hpp

#include <string>

#include "ISystem.hpp"
#include "Point.h"

// TODO: test only. Remove after sorting fix
class SortingTestSystem: public ISystem {
    SYSTEM_BODY(SortingTestSystem)
    
public:
    void Start() override {};
    void Update(double dt) override;
    
private:
    entt::entity AddImage(const std::string& imageId, int layer, IPoint position);
    void RemoveImage(const std::string& imageId);
    void LogDrawOrder(const char* step);
    
    double _time = 0.0; /// in seconds
    int _step = 0;
};

#endif /* SortingTestSystem_hpp */
