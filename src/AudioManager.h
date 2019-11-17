#pragma once

/* Singleton that loads and saves audio files. sf::SoundBuffer which is used for sf::Sound.
and sf::Music. The Game Objects get their sounds from here but sound track
is played from here directly. 
Very Useful if we want to turn off all FX.. we just mute them from here.*/

#include <SFML\Audio.hpp>
#include <vector>
#include <memory>

using std::unique_ptr;

using std::vector;

typedef unique_ptr<sf::SoundBuffer> buffer_up;

typedef unique_ptr<sf::Sound> sound_up;

typedef sf::Sound* GameSound_p;


//typedef unique_ptr<GameSound> gameSound_up;
typedef unique_ptr<sf::Music> music_up;

typedef sf::Music* SoundTrack_p;


//typedef unique_ptr<SoundTrack> soundTrack_up;




class AudioManager
{
public:

    enum Sounds
    {
        APPLAUSE,
        LOSING_BOO,
        DIE,
        EXPLOSION,
        TELEPORT,
        GETTING_HIT,
        COLLECT_BONUS,
        DYNAMITE_TICK,



        NUM_OF_SOUNDS
    };
    static AudioManager& getInstance();
    ~AudioManager();

    GameSound_p getSound(Sounds sound);
    SoundTrack_p getSoundTrack();

    // music button
    void volumeUp();
    void volumeDown();
    void stopSoundTrack();
    void playSoundTrack();

    void FXon();
    void FXoff();






private:

    vector<buffer_up> _buffers;

    vector<sound_up> _sounds;

    music_up _soundTrack;

    void setFXVolumes();

    // make ctor, copy-ctor and assignment operator private.
    AudioManager();
    AudioManager(const AudioManager&);
    AudioManager& operator=(AudioManager const& copy);

};

