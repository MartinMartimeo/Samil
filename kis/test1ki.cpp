#include "test1ki.h"
#include <iostream>

Test1KI::Test1KI()
{
    
}

Test1KI::~Test1KI()
{
    
}

PlayerAction Test1KI::DoThink(WorldMapView const &vvView, WorldEntityInformation const uEntityInformation)
{
    std::cout<<"[test1ki] DoThink called."<<std::endl;
    return Move_N;
}

extern "C" AiInterface* create() {
    return new Test1KI;
}

extern "C" void destroy(AiInterface* p) {
    delete p;
}
