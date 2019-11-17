#pragma once
/* 
Wrapper for Boost graph vertex. The private member vertex_d
*/
#include <vector>
#include "definitions.h"


class Vertex
{
public:

    Vertex(const Posb& posb, vertex_d d, bool free);
    ~Vertex();

    const Posb& getPosb() const;

    void setPredecessor(Vertex* p);

    Vertex* getPredecessor();

    //void setDescriptor(vertex_d d);
    const vertex_d& getDescriptor() const;


    void setToFree();

    bool isFree() const;


private:

    bool _isFree;

    // boost graph vertex descriptor. 
    vertex_d _vertex_d;

    Vertex* _predecessor = nullptr;

    Posb _posb;
};

