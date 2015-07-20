//
//  component.h
//  MightyCPP
//
//  Created by Dino Pejakovic on 31/05/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <ecs/json.h>

struct Component {
    Component();
    virtual ~Component();
    
    virtual JSON toJSON();
    static Component *fromJSON(const JSON& val);
};

namespace component {
    typedef std::unordered_map<std::string, std::function<void*(const std::string&)>> component_map_t;
    typedef std::unordered_map<std::type_index, std::string> component_name_map_t;
    class ComponentRegistry {
    public:
        static ComponentRegistry *getInstance();
        
        template <typename T>
        void registerComponent(const std::string &name) {
            m_registered_components[name] = T::fromJSON;
            m_registered_components_names[typeid(T)] = name;
        }
        
        Component *createComponentFromJSON(const std::string &component_name, const std::string &json) const;
        
        std::string getComponentName(std::type_index typeindex) const;
        
        template <typename T>
        std::string getComponentName() const {
            return this->getComponentName(typeid(T));
        }
        
        std::string getComponentName(const Component *component) const;
        
    private:
        ComponentRegistry();
        static ComponentRegistry *m_instance;
        component_map_t m_registered_components;
        component_name_map_t m_registered_components_names;
    };
    
    template <typename T>
    class ComponentRegistrator {
    public:
        ComponentRegistrator(const std::string &name) {
            ComponentRegistry::getInstance()->registerComponent<T>(name);
            
        }
    };
}




#define REGISTER_COMPONENT_NAMED(TYPE, NAME)                    \
    namespace component {                                       \
        namespace registrators {                                \
            ComponentRegistrator<TYPE> TYPE##Registrator(NAME); \
        }                                                       \
    }

#define REGISTER_COMPONENT(TYPE) REGISTER_COMPONENT_NAMED(TYPE, #TYPE)

#endif // COMPONENT_H
