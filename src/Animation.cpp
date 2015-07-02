#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(const sf::IntRect frame, int numOfFrames)
    : _firstFrame(frame), _frame(frame), _numOfFrames(numOfFrames)
{
}


Animation::~Animation()
{
}


void Animation::update(float time, float duration)
{
    if (time - _timeOfLastUpdate >= duration)
    {
        _frame.left = _firstFrame.left + _currFrame*_frame.width;
        ++_currFrame;
        if (_currFrame >= _numOfFrames) {
            _currFrame = 0;
        }
        _timeOfLastUpdate = time;
    }

}

float Animation::getTimeOfLastUpdate() const
{
    return _timeOfLastUpdate;
}


sf::IntRect Animation::getFrame() const
{
    return _frame;
}

int Animation::getNumOfFrames() const
{
    return _numOfFrames;
}
