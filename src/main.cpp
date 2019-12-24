/* main. Activates the controller.*/

#include "Controller.h"
#include "Logger.h"
#include "definitions.h"  // for font
#include <string>
#include "GraphicObjectsManager.h"
#include "GraphicWindow.h"

void showErrorMessage(const string& message);

int main() try
{
    try {
        Controller c;
        c.run();
    }
    catch (std::exception& e) {
        showErrorMessage("Unexpected error!\nExiting.\n");
        throw;
    }
    return 0;
}

catch (std::exception& e) {
    Logger::getInstance().log("main threw an Exception. Exiting.");
}

void showErrorMessage(const string& message)
{
    GraphicWindow window;

    sf::Text text;
    sf::Font font;
    text.setStyle(sf::Text::Regular);

    text.setPosition(sf::Vector2f(window.getSizeF().x / 2.f, window.getSizeF().y / 2.f));

    font = GraphicObjectsManager::getInstance().getOrbitronFont();

    text.setFont(font);

    text.setFillColor(sf::Color::Blue);

    text.setString(message);

    text.setCharacterSize(30);

    sf::Vector2f center;

    sf::FloatRect textSize;

    textSize = text.getGlobalBounds();

    // make the center of text it's origin.
    center = { textSize.width / 2.f, textSize.height / 2.f };

    text.setOrigin(center);


    window.draw(text);

    window.display();

    sf::Event event;

    while (true)
    {
        while (window.getWindow().pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                case sf::Event::KeyPressed:
                case sf::Event::MouseButtonPressed:
                    return;
            }
        }
    }
}