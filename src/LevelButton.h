#pragma once
/*
  Tells the controller which level to load.
*/
#include "ControllerButton.h"
class LevelButton : public ControllerButton
{
public:

    enum Levels
    {
        LEVEL_1,
        LEVEL_2,
        LEVEL_3,
        LEVEL_4,

        NUM_OF_LEVELS
    };
    LevelButton(const Posf& pos, Levels level, ControllerProxy& controller);
    ~LevelButton();

    virtual void action() const override;

private:
    Levels _level;
};

