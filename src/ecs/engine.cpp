//
//  engine.cpp
//  MightyCPP
//
//  Created by Dino Pejakovic on 31/05/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#include <ecs/engine.h>

#include <stdio.h>

void Engine::update(float dt) {
    for (System *system : this->m_systems) {
        if (system != nullptr) {
            system->update(dt, *this);
        }
    }
}

bool Engine::init() {
    for (System *system : this->m_systems) {
        if (system != nullptr) {
            if (!system->init(*this)) {
                fprintf(stderr, "Error initializing systems.\n");
                return false;
            }
        }
    }
    
    return true;
}

void Engine::setShouldStop() {
    m_should_stop = true;
}

bool Engine::shouldStop() {
    return m_should_stop;
}
