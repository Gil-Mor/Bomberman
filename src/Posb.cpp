#include "Posb.h"

Posb operator+(const Posb& lhs, const Posb& rhs) {
    return Posb(lhs.i + rhs.i, lhs.j + rhs.j);
}

Posb operator-(const Posb& lhs, const Posb& rhs) {
    return Posb(lhs.i - rhs.i, lhs.j - rhs.j);
}

std::ostream& operator << (std::ostream& os, const Posb& pos) {
    os << pos.i << ", " << pos.j;
    return os;
}