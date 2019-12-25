#include "Player.h"
#include "GraphicObjectsManager.h"
#include "Dynamite.h"
#include "Explosion.h"
#include "BoardProxy.h"
#include "FreeTile.h"
#include "StoneWall.h"
#include "ExplodingWall.h"
#include "Teleport.h"
#include "Bonus.h"
#include "AIEnemy.h"

const float PLAYER_MOVE_PAUSE = 0;

Player::Player(const Posf& posf, const Posb& posb, size_t playerNum) : BomberMan(posf, posb), _playerNum(playerNum)
{
    switch (playerNum) {
        case 1:
            _sprite.setColor(PLAYER_1_COLOR);
            break;

        case 2:
            _sprite.setColor(PLAYER_2_COLOR);
            break;
    }
    _bonusSound = AudioManager::getInstance().getSound(AudioManager::COLLECT_BONUS);
}

Player::~Player()
{}

void Player::saveKey(sf::Keyboard::Key key)
{
    _key.keyPressed = true;
    _key.key = key;
}

void Player::update()
{
    Movable::update();

    switch (_bomberManState) {
        case BomberMan::LAST_EXPLOSION_S:
        case BomberMan::COMPLETELY_DEAD_S: {
            break;
        }

        case BomberMan::PLAYING_S: {
            if (!_key.keyPressed)
                break;

            if (movementKey(_key.key)) {
                if (timeToMove(PLAYER_MOVE_PAUSE)) {
                    setLastMoveToNow();
                } else {
                    break;
                }
                if (tryMove(keyToDirection(_key.key))) {
                    setMoveOnBoard();
                    // updateMovingAnimation();
                }
            }

            else {
                Action action = keyToAction(_key.key);

                switch (action) {
                    case PUT_DYNAMITE: {
                        // call base class - Bomberman - method.
                        placeDynamite(*_boardProxy);
                    }

                    default:
                        break;
                }
            }

            break;
        }

        case BomberMan::EXPLODING_S: {
            break;
        }

        default:
            break;
    }

    updateAnimation();
    _key.keyPressed = false;
}

void Player::colide(GameObject& other)
{
    other.colide(*this);
}

void Player::colide(Bonus& other)
{
    _bonusSound->play();
    BomberMan::colide(other);
}

int Player::getAvailableDynamites() const
{
    return _availbleDynamites;
}

int Player::getHealth() const
{
    return _health;
}

bool Player::movementKey(sf::Keyboard::Key key) const
{
    return key == sf::Keyboard::Left || key == sf::Keyboard::Right || key == sf::Keyboard::Up ||
           key == sf::Keyboard::Down || key == sf::Keyboard::W || key == sf::Keyboard::A || key == sf::Keyboard::D ||
           key == sf::Keyboard::S;
}

Movable::Direction Player::keyToDirection(sf::Keyboard::Key key) const
{
    switch (key) {
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            return Player::UP;

        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            return Player::DOWN;

        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            return Player::LEFT;

        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            return Player::RIGHT;

        default:
            return Player::UNDEFINED;
    }
}

Player::Action Player::keyToAction(sf::Keyboard::Key key) const
{
    switch (key) {
        case sf::Keyboard::LControl:
        case sf::Keyboard::RControl:
            return PUT_DYNAMITE;

        default:
            return NOTHING;
    }
}
