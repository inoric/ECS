//
//  resourcemanager.h
//  MightyCPP
//
//  Created by Dino Pejakovic on 12/06/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <unordered_map>
#include <typeindex>

class Resource {
public:
    Resource();
    virtual ~Resource();
    
    static Resource *load(const std::string &path);
    
    virtual bool loadSuccessfull() = 0;
    
    std::string path() const;
    
private:
    std::string m_path;
};

class ResourceManager {
public:
    template <typename T>
    static void load(const std::string &path) {
        T *resource = T::load(path);
        
        m_resources[path] = resource;
    }
    
    template <typename T>
    static void add(const std::string &path, T *resource) {
        m_resources[path] = resource;
    }
    
    template <typename T>
    static T *get(const std::string &path) {
        auto resource = m_resources.find(path);
        
        if (resource != m_resources.end()) {
            return dynamic_cast<T*>(resource->second);
        }
        
        return nullptr;
    }
    
private:
    static std::unordered_map<std::string, Resource *> m_resources;
};



#endif // RESOURCE_H
