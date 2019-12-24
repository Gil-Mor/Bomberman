#include "AudioManager.h"
#include <string>

using std::string;


const string FOLDER = "../sounds/";


AudioManager::AudioManager()
{

    _buffers.resize(NUM_OF_SOUNDS);
    for (auto& buffer : _buffers)
        buffer.reset(new sf::SoundBuffer);


    _buffers[APPLAUSE]->loadFromFile(FOLDER + "applause.wav");
    _buffers[EXPLOSION]->loadFromFile(FOLDER + "dynamite.wav");
    _buffers[LOSING_BOO]->loadFromFile(FOLDER + "losingBoo.wav");
    _buffers[TELEPORT]->loadFromFile(FOLDER + "teleport.wav");
    _buffers[DIE]->loadFromFile(FOLDER + "dying.wav");
    _buffers[COLLECT_BONUS]->loadFromFile(FOLDER + "collectBonus.wav");
    _buffers[GETTING_HIT]->loadFromFile(FOLDER + "gettingHit.wav");
    _buffers[DYNAMITE_TICK]->loadFromFile(FOLDER + "dynamiteTick.wav");




    _sounds.resize(NUM_OF_SOUNDS);
    for (auto& sound : _sounds)
        sound.reset(new sf::Sound);

    _sounds[APPLAUSE]->setBuffer(*_buffers[APPLAUSE].get());
    _sounds[EXPLOSION]->setBuffer(*_buffers[EXPLOSION].get());

    _sounds[LOSING_BOO]->setBuffer(*_buffers[LOSING_BOO].get());

    _sounds[TELEPORT]->setBuffer(*_buffers[TELEPORT].get());

    _sounds[DIE]->setBuffer(*_buffers[DIE].get());

    _sounds[COLLECT_BONUS]->setBuffer(*_buffers[COLLECT_BONUS].get());
    _sounds[COLLECT_BONUS]->setPitch(1.5);



    _sounds[GETTING_HIT]->setBuffer(*_buffers[GETTING_HIT].get());

    _sounds[DYNAMITE_TICK]->setBuffer(*_buffers[DYNAMITE_TICK].get());



    setFXVolumes();


    _soundTrack.reset(new sf::Music);
    _soundTrack->openFromFile(FOLDER + "Boogie Van.ogg");
    _soundTrack->setVolume(70);

}


AudioManager::~AudioManager()
{
}

void AudioManager::setFXVolumes()
{
    _sounds[DYNAMITE_TICK]->setVolume(70);
    _sounds[COLLECT_BONUS]->setVolume(40);
    _sounds[EXPLOSION]->setVolume(70);
    _sounds[TELEPORT]->setVolume(70);


}


void AudioManager::FXon()
{
    for (auto& sound : _sounds)
        sound->setVolume(100);

    setFXVolumes();
}

void AudioManager::FXoff()
{
    for (auto& sound : _sounds)
        sound->setVolume(0);
}


void AudioManager::volumeUp()
{
    float vol = _soundTrack->getVolume();

    if (vol > 90) {
    _soundTrack->setVolume(100);
    }
    else {
        _soundTrack->setVolume(vol + 10);

    }
}


void AudioManager::volumeDown()
{
    float vol = _soundTrack->getVolume();

    if (vol < 10) {
        _soundTrack->setVolume(0);
    }
    else {
        _soundTrack->setVolume(vol - 10);
    }
}


void AudioManager::stopSoundTrack()
{
    _soundTrack->pause();

}


void AudioManager::playSoundTrack()
{
    _soundTrack->play();


}


GameSound_p AudioManager::getSound(AudioManager::Sounds sound)
{
    return _sounds[sound].get();
}


SoundTrack_p AudioManager::getSoundTrack()
{
    return _soundTrack.get();
}

AudioManager& AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}
