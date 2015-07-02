#pragma once
/* Some utility methods like Manhattan Distance and to ask
if position a is closer to position c then position b. 
*/
#include "definitions.h"

int ManhattanDistance(const Posb& a, const Posb& b);

bool AisclosertoCthenB(const Posb& a, const Posb& b, const Posb& c);
