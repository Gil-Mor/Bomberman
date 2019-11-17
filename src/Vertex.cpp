#include "Vertex.h"

Vertex::Vertex(const Posb& posb, vertex_d d, bool free) : _posb(posb), _vertex_d(d), _isFree(free)
{}

Vertex::~Vertex()
{}

const vertex_d& Vertex::getDescriptor() const
{
    return _vertex_d;
}

void Vertex::setToFree()
{
    _isFree = true;
}

bool Vertex::isFree() const
{
    return _isFree;
}

void Vertex::setPredecessor(Vertex* p)
{
    _predecessor = p;
}

Vertex* Vertex::getPredecessor()
{
    return _predecessor;
}

const Posb& Vertex::getPosb() const
{
    return _posb;
}
