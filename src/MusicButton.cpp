#include "MusicButton.h"
#include "GraphicObjectsManager.h"
#include "AudioManager.h"

MusicButton::MusicButton(const Posf& pos, MusicAction action) : Button(pos), _action(action)
{
    switch (action) {
        case MusicButton::VOLUME_UP:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(VOL_UP_BUTTON_T));
            break;
        case MusicButton::VOLUME_DOWN:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(VOL_DOWN_BUTTON_T));

            break;
        case MusicButton::STOP:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(MUSIC_OFF_BUTTON_T));

            break;
        case MusicButton::PLAY:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(MUSIC_ON_BUTTON_T));

            break;
        case MusicButton::FX_ON:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(FX_ON_BUTTON_T));

            break;
        case MusicButton::FX_OFF:
            _sprite.setTexture(GraphicObjectsManager::getInstance().getTexture(FX_OFF_BUTTON_T));

            break;
        default:
            break;
    }

    // set the button size to the size of the texture which contains a text..
    _sprite.setSize(Posf(
        float(_sprite.getSprite().getTextureRect().width * 0.8),
        float(_sprite.getSprite().getTextureRect().height * 0.8)));
}

MusicButton::~MusicButton()
{}

void MusicButton::action() const
{
    switch (_action) {
        case MusicButton::VOLUME_UP:
            AudioManager::getInstance().volumeUp();

            break;
        case MusicButton::VOLUME_DOWN:
            AudioManager::getInstance().volumeDown();

            break;
        case MusicButton::STOP:
            AudioManager::getInstance().stopSoundTrack();

            break;
        case MusicButton::PLAY:
            AudioManager::getInstance().playSoundTrack();

            break;
        case MusicButton::FX_ON:
            AudioManager::getInstance().FXon();

            break;
        case MusicButton::FX_OFF:
            AudioManager::getInstance().FXoff();

            break;
        default:
            break;
    }
}
