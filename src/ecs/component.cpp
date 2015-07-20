//
//  component.cpp
//  MightyCPP
//
//  Created by Dino Pejakovic on 31/05/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#include <ecs/component.h>

Component::Component() {

}

JSON Component::toJSON() {
    return JSON();
}

Component *Component::fromJSON(const JSON&) {
    return new Component();
}

Component::~Component() {
    
}

namespace component {
    ComponentRegistry::ComponentRegistry() {
            
    }
    
    ComponentRegistry *ComponentRegistry::getInstance() {
        if (!m_instance) {
            m_instance = new ComponentRegistry();
        }
        
        return m_instance;
    }
    
    Component *ComponentRegistry::createComponentFromJSON(const std::string &component_name, const std::string &json) const {
        auto func = this->m_registered_components.find(component_name);
        if (func != this->m_registered_components.end()) {
            return (Component*)func->second(json);
        } else {
            return NULL;
        }
    }
    
    std::string ComponentRegistry::getComponentName(std::type_index typeindex) const {
        auto name = this->m_registered_components_names.find(typeindex);
        if (name != this->m_registered_components_names.end()) {
            return name->second;
        } else {
            return "";
        }
    }
    
    std::string ComponentRegistry::getComponentName(const Component *component) const {
        return this->getComponentName(typeid(*component));
    }
    
    ComponentRegistry *ComponentRegistry::m_instance = nullptr;
}
