#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First Game");
    sf::CircleShape player(50);  // A circle-shaped player
    player.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();            // Clear screen
        window.draw(player);       // Draw player
        window.display();          // Show on screen
    }

    return 0;
}
