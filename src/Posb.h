#pragma once
/* 
Position on the board. row and column. 
*/

#include <ostream>

class Posb
{
public:
    static size_t INVALID_POS;
    Posb(size_t _i = (size_t)(-1), size_t _j = (size_t)(-1)) : i(_i), j(_j) {};
    ~Posb() { };

    size_t i, j;

    Posb& operator+= (const Posb& other) {
        i += other.i;
        j += other.j;
        return *this;
    }

    Posb& operator-= (const Posb& other) {
        i -= other.i;
        j -= other.j;
        return *this;
    }


    bool operator == (const Posb& other) {
        return i == other.i && j == other.j;
    }

    bool operator != (const Posb& other) {
        return !(*this == other);
    }


};


std::ostream& operator << (std::ostream& os, const Posb& pos); 

Posb operator+(const Posb& lhs, const Posb& rhs);

Posb operator-(const Posb& lhs, const Posb& rhs);