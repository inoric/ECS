//
//  engine.h
//  MightyCPP
//
//  Created by Dino Pejakovic on 31/05/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <unordered_map>
#include <typeindex>

#include <ecs/system.h>
#include <ecs/world.h>

class Engine {
public:
    template <typename T>
    void addSystem() {
        this->m_systems.push_back(new T());
        this->m_system_index[typeid(T)] = this->m_systems.size() - 1;
    }
    
    template <typename T>
    T *getSystem() {
        auto system_index = this->m_system_index.find(typeid(T));
        if (system_index != this->m_system_index.end()) {
            if (system_index->second < this->m_systems.size()) {
                return static_cast<T*>(this->m_systems[system_index->second]);
            }
        }
        
        return nullptr;
    }
    
    bool init();
    
    void update(float dt);
    void setShouldStop();
    bool shouldStop();
    
    World world;
private:
    std::vector<System *> m_systems;
    std::unordered_map<std::type_index, size_t> m_system_index;
    bool m_should_stop = false;
};

#endif // ENGINE_H
