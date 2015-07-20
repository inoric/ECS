//
//  event.h
//  MightyCPP
//
//  Created by Dino Pejakovic on 12/06/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <functional>
#include <unordered_map>
#include <typeindex>

#include <iostream>

class EventDispatcher {
public:
    EventDispatcher();
    virtual ~EventDispatcher();
    
    template <typename EVENT_TYPE>
    using callback_type = std::function<void(const EVENT_TYPE &ev, EventDispatcher *sender)>;
    
    template <typename EVENT_TYPE>
    void trigger(const EVENT_TYPE &event) {
        auto listeners = this->m_listeners.find(typeid(EVENT_TYPE));
        if (listeners != this->m_listeners.end()) {
            for (void *listener : listeners->second) {
                if (listener != nullptr) {
                    callback_type<EVENT_TYPE> *type = static_cast<callback_type<EVENT_TYPE>*>(listener);
                    (*type)(event, this);
                }
            }
        }
    }
    
    template <typename EVENT_TYPE>
    void on(callback_type<EVENT_TYPE> callback) {
        this->m_listeners[typeid(EVENT_TYPE)].push_back(new callback_type<EVENT_TYPE>(callback));
    }
    
private:
    std::unordered_map<std::type_index, std::vector<void *>> m_listeners;
    
};

#endif // EVENT_H
