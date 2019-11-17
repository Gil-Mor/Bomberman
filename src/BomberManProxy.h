#pragma once
/* BomberMan gives this to dynamites when he places them on the board
so that they can tell him they exploded, incrementing it's dynamite count.*/
class BomberMan;

class BomberManProxy
{
public:
    BomberManProxy(BomberMan& _bomberMan);
    ~BomberManProxy();

    void dynamiteExploded();

private:
    BomberMan& _bomberMan;
};
