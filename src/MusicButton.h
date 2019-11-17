#pragma once
/*
  Button that controls the music. Calls methods in the 'AudioManager' Singleton.
*/
#include "Button.h"

class MusicButton : public Button
{
public:
    enum MusicAction {

        VOLUME_UP,
        VOLUME_DOWN,
        STOP,
        PLAY,

        FX_ON,
        FX_OFF

    };

    MusicButton(const Posf& pos, MusicAction action);
    ~MusicButton();

    void action() const override;

private:
    MusicAction _action;
};
