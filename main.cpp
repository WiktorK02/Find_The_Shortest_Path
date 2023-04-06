#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>

#define SCREEN_HEIGHT 960
#define SCREEN_WIDTH 1200

using namespace std;

class obj
{
public:
    obj();

    void render(sf::RenderWindow& window);
    sf::Vector2f get_pos() {
        return pos;
    }
    void set_pos(float posx, float posy) {
        pos.x = posx;
        pos.y = posy;
    }
    ~obj();

private:
    sf::Vector2f pos;
    sf::CircleShape circle;
};

obj::~obj()
{
    // No need to delete circle since it's a member variable
}

obj::obj()
{
    
}

void obj::render(sf::RenderWindow& window) {
    circle.setPosition(pos);
    circle.setRadius(50);
    window.draw(circle);
}

// Function to display the array
void display(int a[], int n, obj circle[], sf::RenderWindow& window)
{
    window.clear(sf::Color::White); // Clear window with white color
    for (int i = 0; i < n; i++) {
        circle[i].render(window);

        // Draw lines between circles
        if (a[i] != -1) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = circle[i].get_pos() + sf::Vector2f(50, 50);
            line[1].position = circle[a[i]].get_pos() + sf::Vector2f(50, 50);
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::Blue;
            window.draw(line);
        }
    }
    window.display(); // Display the drawn frame
}

// Function to find the permutations
void findPermutations(int a[], int n, obj circle[], sf::RenderWindow& window)
{
    // Sort the given array
    sort(a, a + n);

    // Find all possible permutations
    cout << "loop restart";
    do {
        // Display the circles and lines
        display(a, n, circle, window);

        // Draw lines between circles
        sf::VertexArray lines(sf::Lines, n * 2);
        for (int i = 0; i < n; i++) {
            lines[i * 2].position = circle[i].get_pos() + sf::Vector2f(50, 50);
            lines[i * 2 + 1].position = circle[a[i]].get_pos() + sf::Vector2f(50, 50);
            lines[i * 2].color = sf::Color::White;
            lines[i * 2 + 1].color = sf::Color::Blue;
        }
        // Draw circles
        for (int i = 0; i < n; i++) {
            circle[i].render(window);
        }
        window.clear();
        for (int i = 0; i < 5; i++) circle[i].render(window);
        window.draw(lines);
        window.display();

        // Pause for a short duration
        this_thread::sleep_for(chrono::milliseconds(50));

    } while (next_permutation(a, a + n));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), ".");
    window.setFramerateLimit(500);

    obj circle[5];
    circle[0].set_pos(100, 100);
    circle[1].set_pos(1000, 50);
    circle[2].set_pos(500, 900);
    circle[3].set_pos(800, 500);
    circle[4].set_pos(200, 600);

    sf::Event event;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            switch (event.type) {

            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            }
        }

        int a[] = { 0, 1, 2, 3, 4 }; // Indices of circles
        int n = sizeof(a) / sizeof(a[0]);
        findPermutations(a, n, circle, window);
    }

    return 0;
}
