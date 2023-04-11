# Algorithm which visualize permutations simulation
## Screenshots
<pre><img src="https://user-images.githubusercontent.com/123249470/231189581-51d0d722-ac05-4046-ba7f-db6fef748286.gif" width="400" height="400" />   <img src="https://user-images.githubusercontent.com/123249470/231208904-8a680d4d-275e-4217-9d9d-5b35cd1ee8fa.gif" width="400" height="400"/></pre>

## Customize it by yourself

### Change the position and the amount of circles
  Set the number of the objects by changing index value (n is default):
```
Object circle[n];
```
Set position of the objects based on index value (to n- 1):
```
circle[0].set_pos(500, 100);
circle[1].set_pos(800, 50);
circle[2].set_pos(200, 700); 
.
.
.
circle[n-1].set_pos(400, 300); 
 ```
Change the value of an array that holds the maximum value of the permutation:
 ```
int a[] = { 0, 1, 2, ... , n-1};
 ```
### Example of changed code
 ```
Object circle[4];

circle[0].set_pos(500, 100);
circle[1].set_pos(800, 50);
circle[2].set_pos(200, 700);
circle[3].set_pos(150, 300);

int a[] = { 0, 1, 2, 3};
 ```
 ### Change colors:
 in class ```Object```
  ```
  class Object
{
public:
.
.
.
  void render(sf::RenderWindow& window, bool hasLineConnection) {
      circle.setPosition(pos);
      circle.setRadius(20);
      if (hasLineConnection) {
          circle.setFillColor(sf::Color::Cyan); //Change color of active circles(connected to line)
      }
      else {
          circle.setFillColor(sf::Color::White); //Change color of none active circles
      }
 ```
Note: algorithm visualization is based on SFML c++ library
## Task list
- [ ] upgrade graphics<br>
- [ ] split into files and organize code<br>
- [x]	function that finds range between objects<br>
- [x] function that return progress in percentage<br>

## What I have learned
•	improved SFML library skills<br>
•	the basics of algorithmics


