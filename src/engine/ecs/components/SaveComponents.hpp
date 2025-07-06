//
//  SaveComponents.h
//  EPet
//
//  Created by marina porkhunova on 13.04.2025.
//

#ifndef SaveComponents_hpp
#define SaveComponents_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "Logging.hpp"
#include "registry.hpp"
#include "json.hpp"

using data = nlohmann::json;

#define SAVE_FUNCTION_PARAMS entt::registry& registry, entt::entity entity, data& saveData
using saveFunction = void(SAVE_FUNCTION_PARAMS);

class ComponentSaver
{
private:
    static std::unordered_map<std::string, std::function<saveFunction>>& GetSavers()
    {
        static std::unordered_map<std::string, std::function<saveFunction>> _Savers;
        return _Savers;
    };
    
    static void RegisterSaver(std::string typeId, std::function<saveFunction> saveFunction)
    {
        if(const auto it = GetSavers().find(typeId); it != GetSavers().end())
        {
            LOG_ERROR("ComponentSaver::RegisterSaver: Component saver ["<<typeId<<"] already exist. Saver registration was ignored");
            return;
        }
        GetSavers()[typeId] = saveFunction;
        LOG_MESSAGE("ComponentSaver::RegisterSaver: Component saver ["<<typeId<<"] registred");
    };
    
    template <typename T>
    friend void GenerateSaveFunction(const char* typeId, std::function<void(T&, data&)> saver);
   
    friend void Save(const char* typeId, SAVE_FUNCTION_PARAMS);
    friend void SaveAllComponentInEntity(entt::registry& registry, entt::entity entity, data& saveData);
};

/// function for component registration
template<class T>
void GenerateSaveFunction(const char* typeId, std::function<void(T&, data&)> saver)
{
    static std::function<saveFunction> f =
    [saver](SAVE_FUNCTION_PARAMS)
    {
       if(auto comp = registry.try_get<T>(entity))
        {
            saver(*comp, saveData);
        }
    };
    
    ComponentSaver::RegisterSaver(typeId, f);
}

/// function for saving a component
void Save(const char* typeId, SAVE_FUNCTION_PARAMS)
{
    if(auto it = ComponentSaver::GetSavers().find(typeId); it != ComponentSaver::GetSavers().end())
    {
        it->second(registry, entity, saveData);
        
        if(!saveData.empty())
        {
            saveData["id"] = typeId;
        }
    }
    else
    {
        LOG_ERROR("Load: Component saver ["<<typeId<<"] didn't find. Saving component canceled");
    }
}

void SaveAllComponentInEntity(SAVE_FUNCTION_PARAMS)
{
    for(auto it : ComponentSaver::GetSavers())
    {
        data obj;
        Save(it.first.c_str(), registry, entity, obj);

        if(!obj.empty())
        {
            saveData["components"].push_back(obj);
        }
    }
}

#endif /* SaveComponents_h */
