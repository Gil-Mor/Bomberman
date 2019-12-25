#include "definitions.h"
#include "boardUtils.h"

int ManhattanDistance(const Posb& a, const Posb& b)
{
    return int(abs(a.i - b.i)) + int(abs(a.j - b.j));
}

bool AisclosertoCthenB(const Posb& a, const Posb& b, const Posb& c)
{
    return ManhattanDistance(a, c) < ManhattanDistance(b, c);
}