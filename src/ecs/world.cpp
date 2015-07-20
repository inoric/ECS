//
//  world.cpp
//  MightyCPP
//
//  Created by Dino Pejakovic on 31/05/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#include <ecs/world.h>
#include <ecs/entity.h>

#include <ecs/json.h>
#include <ecs/util.h>

World::World() {
    
}

World::~World() {
    
}

Entity World::createEntity() {
    if (!this->m_unused_ids.empty()) {
        entity_id_t id = *this->m_unused_ids.begin();
        this->m_unused_ids.erase(id);
        return Entity(id, this);
    } else {
        return Entity(++this->m_id_counter, this);
    }
};

void World::destroyEntity(entity_id_t entity) {
    this->m_unused_ids.insert(entity);
    for (auto &it : this->m_components) {
        if (it.second.size() >= entity) {
            delete it.second[entity];
            it.second[entity] = nullptr;
        }
    }
};

bool World::entityExists(entity_id_t entity) {
    return entity && entity <= this->m_id_counter && m_unused_ids.find(entity) == m_unused_ids.end();
};

size_t World::entityCount() {
    return m_id_counter - this->m_unused_ids.size();
};

std::unordered_set<entity_id_t> World::entitiesWithComponents(std::type_index first, std::vector<std::type_index> others) {
    std::unordered_set<entity_id_t> matched_entities;
    
    auto first_type_entities = this->m_components.find(first);
    if (first_type_entities != this->m_components.end()) {
        for (auto entity : first_type_entities->second) {
            matched_entities.insert(entity.first);
        }
    }
    
    for (auto type : others) {
        auto entities_with_component = this->m_components.find(type);
        if (entities_with_component != this->m_components.end()) {
            std::unordered_set<entity_id_t> matched_entities2 = matched_entities;
            for (auto entity = matched_entities.begin(); entity != matched_entities.end(); ++entity) {
                if (entities_with_component->second.find(*entity) == entities_with_component->second.end()) {
                    matched_entities2.erase(*entity);
                }
            }
            matched_entities = matched_entities2;
        } else {
            matched_entities.clear();
        }
    }
    
    return matched_entities;
}

JSON World::entityToJSON(entity_id_t entity) {
    JSON json = {
        {"components", {}}
    };
    component::ComponentRegistry *registry_instance = component::ComponentRegistry::getInstance();
    for (auto type : this->m_components) {
        auto component = type.second.find(entity);
        if (component != type.second.end()) {
            std::string name = registry_instance->getComponentName(component->second);
            json["components"][name] = component->second->toJSON();
        }
    }
    
    return json;
}

Entity World::entityFromId(entity_id_t id) {
    return Entity(id, this);
}
