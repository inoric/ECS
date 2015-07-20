//
//  system.h
//  MightyCPP
//
//  Created by Dino Pejakovic on 12/06/15.
//  Copyright (c) 2015 Dino Pejakovic. All rights reserved.
//

#ifndef SYSTEM_H
#define SYSTEM_H

class Engine;

class System {
public:
    System();
    virtual bool init(Engine &engine) = 0;
    virtual ~System();
    virtual void update(float dt, Engine &engine) = 0;
};

#endif // SYSTEM_H
