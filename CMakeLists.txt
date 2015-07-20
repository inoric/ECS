project(ECS)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

include_directories(. include)

set(SOURCES
    src/ecs/component.cpp
    src/ecs/engine.cpp
    src/ecs/entity.cpp
    src/ecs/event.cpp
    src/ecs/resource.cpp
    src/ecs/system.cpp
    src/ecs/util.cpp
    src/ecs/world.cpp
)

set (HEADERS
    deps/json.h
    include/ecs/component.h
    include/ecs/engine.h
    include/ecs/entity.h
    include/ecs/event.h
    include/ecs/json.h
    include/ecs/resource.h
    include/ecs/system.h
    include/ecs/util.h
    include/ecs/world.h
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
