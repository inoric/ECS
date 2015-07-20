//
//  entity.cpp
//  MightyCPP
//
//  Created by Dino Pejakovic on 31/05/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#include <ecs/entity.h>

Entity::Entity(entity_id_t id, World *world) : m_id(id), m_world(world) {
    
}

entity_id_t Entity::Id() {
    return m_id;
}

std::string Entity::toJSON() {

    return this->m_world->entityToJSON(this->m_id);
}


Entity::~Entity() {
    
}
