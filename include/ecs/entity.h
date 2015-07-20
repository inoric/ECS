//
//  entity.h
//  MightyCPP
//
//  Created by Dino Pejakovic on 31/05/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <string>

#include <ecs/world.h>

typedef uint64_t entity_id_t;

class Entity {
    friend class World;
public:
    ~Entity();
    
    entity_id_t Id();
    
    template <typename T>
    void addComponent(const T &component) {
        this->m_world->addComponentToEntity(this->m_id, component);
    }
    
    template <typename T>
    T *getComponent() {
        return this->m_world->getComponentForEntity<T>(this->m_id);
    }
    
    bool isValid() {
        return this->m_world->entityExists(this->m_id);
    }
    
    std::string toJSON();
    
    
private:
    Entity(entity_id_t id, World *world);
    World *m_world;
    entity_id_t m_id;
};

#endif // ENTITY_H
