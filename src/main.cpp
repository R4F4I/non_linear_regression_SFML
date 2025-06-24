#include <SFML/Graphics.hpp>
#include <iostream>
#include "formulas.hpp"


// data set Constants
#define EULER       2.71828
#define ALPHA       0.0001
#define EPSILON     0.001
#define THRESHOLD   0.0001 // LIMIT till which gradient descent is done

// data set array constants
#define SIZE 		20 // data set size m
#define PARAMS 		10

// SFML window constants
#define WIDTH	   	500
#define HEIGHT	   	500

// graph constants
#define EDGE 		10

template <typename T>
class Pair
{
public:
    T x,y;
	Pair(T x, T y) : x(x), y(y) {}
};

class line{
	static int sample_rate;
};

int line::sample_rate = 1000;

class Point : public sf::Vertex{

public:
	Point(
		float x = 0, 
		float y = 0, 
		sf::Color color = sf::Color::Red
	) : 
	sf::Vertex(sf::Vector2f(x, y), color) {}

};

class graph{


};

// since the data points are of type Pair<float>, we can use a template function to find the max value
template <typename T>
Pair <T> findMax(const Pair<T> arr[], int size) {
    
	Pair <T> max(arr[0].x, arr[0].y);
    for(int i = 1; i < size; ++i) {
        if(arr[i].x > max.x) max.x = arr[i].x;
        if(arr[i].y > max.y) max.y = arr[i].y;
    }
    return max;
}

template <typename T>
Pair <T> findMin(const Pair<T> arr[], int size) {
    
	Pair <T> min(arr[0].x, arr[0].y); // initialize to maximum possible values which is WIDTH and HEIGHT
    for(int i = 1; i < size; ++i) {
        if(arr[i].x < min.x) min.x = arr[i].x;
        if(arr[i].y < min.y) min.y = arr[i].y;
    }
    return min;
}

sf::Color RED = sf::Color::Red;


//if you want to load OpenGL
//#include <glad/glad.h>
//#include <errorReporting.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	
	// data points
	Pair<float> data[SIZE] = {
		
		
		{ -5.0, -1.50 },
        { -4.5,  0.01 },
        { -4.0,  0.55 },
        { -3.5,  1.20 },
        { -3.0,  1.85 },
        { -2.5,  2.30 },
        { -2.0,  2.70 },
        { -1.5,  3.00 },
        { -1.0,  3.20 },
        { -0.5,  3.30 },
        {  0.0,  3.35 },
        {  0.5,  3.30 },
        {  1.0,  3.20 },
        {  1.5,  3.00 },
        {  2.0,  2.70 },
        {  2.5,  2.30 },
        {  3.0,  1.85 },
        {  3.5,  1.20 },
        {  4.0,  0.55 },
        {  4.5,  0.01 }
		
    };
	
	// the data in data points must converted into a ratios that can be used to draw the graph
	// the largest and smallest data points will determine the edges, and hence will be used to scale the data points
	Pair<float> max = findMax(data, SIZE);
	Pair<float> min = findMin(data, SIZE);

// scaled_x = ((data[0].x - min.x) / (max.x - min.x)) * (WIDTH - 1)
// scaled_y = ((data[0].y - min.y) / (max.y - min.y)) * (HEIGHT - 1)

	

	Point point[SIZE];
	for (int i = 0; i < SIZE; ++i) {
	    float scaled_x = ((data[i].x - min.x) / (max.x - min.x)) * (WIDTH - EDGE);
	    // float scaled_y = ((data[i].y - min.y) / (max.y - min.y)) * (HEIGHT - EDGE);
		float scaled_y = HEIGHT - EDGE - ((data[i].y - min.y) / (max.y - min.y)) * (HEIGHT - EDGE);
	    point[i] = Point(scaled_x, scaled_y);
	}


	 sf::CircleShape shape(100.f);
	 window.setVerticalSyncEnabled(true);
	 shape.setFillColor(sf::Color::Green);

	sf::Clock clock;

	// create the graph grid


	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
			{
			
				// Adjust the viewport when the window is resized
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

		//calculate the delta time
		sf::Time deltaTime = clock.restart();
		float deltaTimeSeconds = deltaTime.asSeconds();

		//make sure delta time stays within normal bounds, like between one FPS and zero FPS
		deltaTimeSeconds = std::min(deltaTimeSeconds, 1.f);
		deltaTimeSeconds = std::max(deltaTimeSeconds, 0.f);

		//game code....
		window.clear();
		// window.draw(shape);

		
		// window.draw(point, SIZE, sf::Points);
		// this works because Point class inherits from sf::Vertex draw supports SFML types only
		window.draw(reinterpret_cast<sf::Vertex*>(point), SIZE, sf::Points);
		
		

		window.display();
	}

	return 0;
}