#pragma once
/* 
Position on the board. row and column. 
*/

#include <ostream>

class Posb
{
public:
    Posb(int _i = -1, int _j = -1) : i(_i), j(_j) {};
    ~Posb() { };


    int i, j;



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