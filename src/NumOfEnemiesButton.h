#pragma once
/*
  Tells the controller how many enemies need to be in the level.
*/
#include "ControllerButton.h"

class NumOfEnemiesButton : public ControllerButton
{
public:
    NumOfEnemiesButton(const Posf& pos, size_t numOfEnemies, ControllerProxy& controller);

    virtual ~NumOfEnemiesButton();

    void action() const override;

    // hides when 2 players button is chosen.
    virtual void draw(GraphicWindow& window) override;

    void turnOFF3EnemiesButton();

    void turnOn3EnemiesButton();

private:
    size_t _numOfEnemies;

    // menu needs to turn off 3 enemies button..
    // due to lack of time this is my solution
    bool _active = true;
};
