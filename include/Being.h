#pragma once
#include <SFML/Graphics.hpp>
#include "Managers/GraphicManager.h"
#include <iostream>
#include <string>
#include "SOURCEDIR.h"

enum ID
{
    empty           =-1,
    player          = 0,
    archer          = 1,
    warrior         = 2,
    obstacle        = 3,
    level           = 4,
    alaska          = 5,
    vulcano         = 6,
    menu            = 7,
    button          = 8,
    projectile      = 9,
    ice		        =10,
    lava	        =11,
    ground	        =12,
    horse           =13
};


class Being
{
public:
    Being(ID id_ = empty);
    virtual ~Being();
    virtual void Draw() = 0;
    const ID getID() const; 
    virtual void Update() = 0;
private:
    const ID id;
protected:
    static Managers::GraphicManager* pGM;
};
