#include "testki.h"

TestKI::TestKI()
{
    
}

TestKI::~TestKI()
{
    
}

PlayerAction TestKI::DoThink(WorldMapView const &vvView, WorldEntityInformation const uEntityInformation)
{
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