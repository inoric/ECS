//
//  resourcemanager.cpp
//  MightyCPP
//
//  Created by Dino Pejakovic on 12/06/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#include <ecs/resource.h>

std::unordered_map<std::string, Resource *> ResourceManager::m_resources = std::unordered_map<std::string, Resource *>();

Resource::Resource() {

}

Resource::~Resource() {

}

Resource *Resource::load(const std::string &path) {
    return nullptr;
};

std::string Resource::path() const {
    return m_path;
}
