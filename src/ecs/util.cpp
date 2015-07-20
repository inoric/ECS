//
//  util.cpp
//  MightyCPP
//
//  Created by Dino Pejakovic on 31/05/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#include <ecs/util.h>

std::string fileToString(const std::string &path) {
    std::ifstream t(path);
    std::string str = "";
    
    if (t.is_open()) {
        t.seekg(0, std::ios::end);
        str.reserve(t.tellg());
        t.seekg(0, std::ios::beg);
        
        str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    }
    
    return str;
}

uint32_t nextPowerOfTwo(uint32_t n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    
    return n;
}
