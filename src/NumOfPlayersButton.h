#pragma once
/*
Tells the controller how many players need to be in the level.
*/
#include "ControllerButton.h"

class NumOfPlayersButton : public ControllerButton
{
public:
    NumOfPlayersButton(const Posf& pos, size_t num, ControllerProxy& c);
    virtual ~NumOfPlayersButton();

    void action() const override;

private:
    // Given on construction.
    size_t _numOfPlayers;
};
