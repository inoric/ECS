//
//  world.h
//  MightyCPP
//
//  Created by Dino Pejakovic on 31/05/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <vector>

#include <ecs/json.h>
#include <ecs/component.h>

using JSON = nlohmann::json;


typedef uint64_t entity_id_t;

class Entity;

class World {
public:
    World();
    ~World();
    
    Entity createEntity();
    Entity entityFromId(entity_id_t id);
    void destroyEntity(entity_id_t entity);
    bool entityExists(entity_id_t entity);
    size_t entityCount();
    
    template <typename T>
    void addComponentToEntity(entity_id_t entity, const T &component) {
        static_assert(std::is_base_of<Component, T>::value, "Type not derived from Component.");
        
        auto it = this->m_components.find(typeid(T));
        if (it == this->m_components.end()) {
            this->m_components[typeid(T)] = std::unordered_map<entity_id_t, Component *>();
            it = m_components.find(typeid(T));
        }
        
        it->second[entity] = new T(component);
    };
    
    template <typename T>
    T *getComponentForEntity(entity_id_t entity) {
        auto components_of_type = this->m_components.find(typeid(T));
        if (components_of_type != this->m_components.end()) {
            auto component = components_of_type->second.find(entity);
            if (component != components_of_type->second.end()) {
                return dynamic_cast<T*>(component->second);
            }
        }
        
        return nullptr;
    }
    
    std::unordered_set<entity_id_t> entitiesWithComponents(std::type_index first, std::vector<std::type_index> others);
    
    template <typename T0, typename... T>
    std::unordered_set<entity_id_t> entitiesWithComponents() {
        return this->entitiesWithComponents(typeid(T0), {typeid(T)...});
    }
    
    JSON entityToJSON(entity_id_t entity);
    
private:
    std::unordered_map<std::type_index, std::unordered_map<entity_id_t, Component *>> m_components;
    std::unordered_set<entity_id_t> m_unused_ids;
    entity_id_t m_id_counter = 0;
};


#endif // WORLD_H
