//
//  util.h
//  MightyCPP
//
//  Created by Dino Pejakovic on 31/05/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#ifndef UTIL_H
#define UTIL_H

#include <string>

#include <fstream>
#include <streambuf>

template<typename ... ARGS>
std::string stringFormat(const std::string& format, ARGS ... args){
    size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size);
}

template <typename TO, typename FROM>
TO string_cast(const FROM &str) {
    return TO(str.begin(), str.end());
}

uint32_t nextPowerOfTwo(uint32_t n);

std::string fileToString(const std::string &path);

#endif // UTIL_H
