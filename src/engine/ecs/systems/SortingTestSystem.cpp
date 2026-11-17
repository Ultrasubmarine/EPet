//
//  SortingTestSystem.cpp
//  EPet
//
//  Created by marina porkhunova on 16.11.2026.
//

#include "SortingTestSystem.hpp"

#include <sstream>

#include "CommonComponents.hpp"
#include "Logger.hpp"

SYSTEM_CPP(SortingTestSystem);

void SortingTestSystem::Update(double dt)
{
    _time += dt;
    
    // 0: start state
    if(_step == 0) {
        LogDrawOrder("start");
        _step++;
    }
    // 3 sec: nymph from layer 1 to 4 - above hamster (layer 3)
    else if(_step == 1 && _time >= 3.0) {
        for(auto [ent, image] : _registry.view<Image>().each())
        {
            if(image.resoursesId == "Nymph_idle/Nymph_idle - 1") {
                Sorting::SetLayer(_registry, ent, 4);
            }
        }
        _step++;
    }
    else if(_step == 2) {
        LogDrawOrder("after SetLayer");
        _step++;
    }
    // 6 sec: add image that is already loaded + image that is not loaded yet
    else if(_step == 3 && _time >= 6.0) {
        AddImage("Field", 2, IPoint(60, 100));
        AddImage("Hamster_idle/Hamster_adult - 2", 6, IPoint(110, 120));
        LOG_MESSAGE("Sorting test: 2 images added");
        _step++;
    }
    else if(_step == 4) {
        LogDrawOrder("after add");
        _step++;
    }
    // 9 sec: remove one of start images
    else if(_step == 5 && _time >= 9.0) {
        RemoveImage("Hamster_idle/Hamster_adult - 1");
        _step++;
    }
    else if(_step == 6) {
        LogDrawOrder("after remove");
        _step++;
    }
}

entt::entity SortingTestSystem::AddImage(const std::string& imageId, int layer, IPoint position)
{
    auto ent = _registry.create();
    _registry.emplace<Transform>(ent, position);
    _registry.emplace<Sorting>(ent, layer);
    _registry.emplace<Image>(ent, imageId);
    _registry.emplace<RendererObject>(ent);
    return ent;
}

void SortingTestSystem::RemoveImage(const std::string& imageId)
{
    for(auto [ent, image] : _registry.view<Image>().each())
    {
        if(image.resoursesId == imageId) {
            _registry.destroy(ent);
            LOG_MESSAGE("Sorting test: image [" << imageId << "] removed");
            return;
        }
    }
    LOG_WARNING("Sorting test: image [" << imageId << "] not found");
}

void SortingTestSystem::LogDrawOrder(const char* step)
{
    // same view as in RenderSystem
    std::ostringstream order;
    for(auto [ent, sorting, transform, rObj] : _registry.view<Sorting, Transform, RendererObject>().each())
    {
        const auto* image = _registry.try_get<Image>(ent);
        order << "[" << (image ? image->resoursesId : "?") << " layer " << sorting.GetLayer() << (rObj.resource ? "" : " NO TEXTURE") << "] ";
    }
    LOG_MESSAGE("Sorting test [" << step << "]. Draw order: " << order.str());
}
