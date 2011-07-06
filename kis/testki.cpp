#include "testki.h"
#include <iostream>

PlayerAction TestKI::DoThink(WorldMapView const &vvView, WorldEntityInformation const uEntityInformation)
{
    std::cout<<"[testki] DoThink called."<<std::endl;
    return DoNothing;
}
