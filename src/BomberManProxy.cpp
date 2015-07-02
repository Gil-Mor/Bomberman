#include "BomberManProxy.h"
#include "BomberMan.h"

BomberManProxy::BomberManProxy(BomberMan& bomberMan)
    : _bomberMan(bomberMan)
{
}


BomberManProxy::~BomberManProxy()
{
}


void BomberManProxy::dynamiteExploded()
{
    _bomberMan.dynamiteExploded();
}
