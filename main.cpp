#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>
#include <cmath>

#define SCREEN_HEIGHT 960
#define SCREEN_WIDTH 1200

using namespace std;

class obj
{
public:
    obj();

    sf::Vector2f get_pos() {
        return pos;
    }
    void set_pos(float posx, float posy) {
        pos.x = posx;
        pos.y = posy;
    }
    void render(sf::RenderWindow& window, bool hasLineConnection) {
        circle.setPosition(pos);
        circle.setRadius(50);
        if (hasLineConnection) {
            circle.setFillColor(sf::Color::Green); // Change the color to green when circle is connected to a line
        }
        else {
            circle.setFillColor(sf::Color::White);
        }
        window.draw(circle);
    }

    void setLineConnection(bool hasLine) {
        hasLineConnection = hasLine;
    }
    bool getLineConnection() {
        return hasLineConnection;
    }
    ~obj();

private:
    sf::Vector2f pos;
    sf::CircleShape circle;
    bool hasLineConnection; // added flag to keep track of line connection
};

obj::~obj()
{

}

obj::obj()
{
    hasLineConnection = false; // initialize flag to false
}


// Function to display the array
void display(int a[], int n, obj circle[], sf::RenderWindow& window, sf::Text& percentage, float counter)
{
    double distnace_between = 0;
    window.clear(sf::Color::Black); // Clear window with black color
    for (int i = 0; i < n; i++) {
        // Draw lines between circles
        if (a[i] != -1) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = circle[i].get_pos() + sf::Vector2f(50, 50);
            line[1].position = circle[a[i]].get_pos() + sf::Vector2f(50, 50);

            //calculate distance between using pitagoras
            distnace_between = distnace_between + sqrt(pow(circle[i].get_pos().x - circle[a[i]].get_pos().x, 2) + pow(circle[i].get_pos().y - circle[a[i]].get_pos().y, 2));

            line[0].color = sf::Color::White;
            line[1].color = sf::Color::Blue;

            // Check if circle is connected to a line
            circle[i].render(window, true);
            circle[a[i]].render(window, false);
            window.draw(line);
        }
        if (!distnace_between == 0) cout << distnace_between << endl;
    }
    cout << endl;

    // Draw counter
    counter = counter / 720 * 100;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0) << counter;
    std::string textStr = oss.str();
    percentage.setString("Counter: " + textStr + "%");
    window.draw(percentage);

    window.display(); // Display the drawn frame
}

// Function to find the permutations
void findPermutations(int a[], int n, obj circle[], sf::RenderWindow& window, sf::Text& percentage)
{
    int counter = 0;
    // Sort the given array
    sort(a, a + n);

    // Find all possible permutations
    do {
        counter++;
        display(a, n, circle, window, percentage, counter);

        // Pause for a short duration
        this_thread::sleep_for(chrono::milliseconds(200));

    } while (next_permutation(a, a + n));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), ".");
    window.setFramerateLimit(120);

    sf::Text percentage;
    sf::Font font;
    font.loadFromFile("minecraft_font.ttf");
    percentage.setFont(font); // font is a sf::Font

    // set the character size
    percentage.setCharacterSize(24); // in pixels, not points!

    // set the color
    percentage.setFillColor(sf::Color::White);
    int counter = 0;

    obj circle[6];
    //object possition 
    circle[0].set_pos(100, 100);
    circle[1].set_pos(1000, 50);
    circle[2].set_pos(500, 900);
    circle[3].set_pos(800, 500);
    circle[4].set_pos(200, 600);
    circle[5].set_pos(400, 500);

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
        percentage.setString(to_string(counter));
        counter++;
        
        int a[] = { 0, 1, 2, 3, 4, 5}; // Indices of circles
        int n = sizeof(a) / sizeof(a[0]);
        
        window.clear();
        findPermutations(a, n, circle, window, percentage);
        window.display();
    }

    return 0;
}

