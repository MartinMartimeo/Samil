#include "testki.h"
#include <iostream>

TestKI::TestKI()
{
    
}

TestKI::~TestKI()
{
    
}

PlayerAction TestKI::DoThink(WorldMapView const &vvView, WorldEntityInformation const uEntityInformation)
{
    std::cout<<"[testki] DoThink called."<<std::endl;
    return DoNothing;
}

unsigned int TestKI::GetRandomNumber()
{
    return 7;
}

extern "C" AiInterface* create() {
    return new TestKI;
}

extern "C" void destroy(AiInterface* p) {
    delete p;
}
