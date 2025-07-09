#include <SFML/Graphics.hpp>
#include <iostream>
#include "formulas.hpp"
#include "configuration.hpp"


// colors
sf::Color RED = sf::Color::Red;
sf::Color GREEN = sf::Color::Green;

// define group of points, line can also be considered as a group of points, which is sampled at a fixed interval
//////////////////////////////////////////
class Point : public sf::Vertex{

public:
	Point(
		float x = 0, 
		float y = 0, 
		sf::Color color = sf::Color::Red
	) : 
	sf::Vertex(sf::Vector2f(x, y), color) {}

};

/////////////////////////////////////////

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
	std::cout << "\033[?25l"; // ANSI escape code to hide the cursor

	// fetch data from "data.txt"
	Pair<float> data[SIZE];
	load_data_from_file("data.txt", data, SIZE);
	// fetch parameters from "parameters.txt"
	float para[PARAMS];
	load_data_from_file("parameters.txt", para, PARAMS);
	
	
	//? data and parameters defined in configuration.hpp
	Point point[SIZE];
	Point line[WIDTH];
	// the data in data points must converted into a ratios that can be used to draw the graph
	// the largest and smallest data points will determine the edges, and hence will be used to scale the data points
	Pair<float> max = DS::findMax(data, SIZE);
	Pair<float> min = DS::findMin(data, SIZE);

	// define the points
	for (int i = 0; i < SIZE; ++i) {
	    float scaled_x = ((data[i].x - min.x) / (max.x - min.x)) * (WIDTH - EDGE);
	    // float scaled_y = ((data[i].y - min.y) / (max.y - min.y)) * (HEIGHT - EDGE);
		float scaled_y = HEIGHT - EDGE - ((data[i].y - min.y) / (max.y - min.y)) * (HEIGHT - EDGE);
	    point[i] = Point(scaled_x, scaled_y);
	}

	sf::Clock clock;
	int print = 0;

	///////////////////////////////////////////////////////////////////////////////////
	// main loop

	sf::Font font;
    if (!font.loadFromFile("res/arial.ttf")) {
        std::cerr << "Could not load font\n";
        return 1;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("press enter to start!\n press escape to exit");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);


	bool started = false;
	printf("loss: %f\n",ML::loss_func(para,data));
	printf("parameters: ");
	for (size_t i = 0; i < PARAMS; i++) {
		std::cout << para[i];
		if (i < PARAMS - 1) {
			std::cout << ", ";
		}
	}
	printf("\n");

	while 
	(	window.isOpen() && 
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
	)
	{
		// process events
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
		

		if (!started)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				started = true;
				std::cout << "Started!\n";
			} else
			{
				window.draw(text);
			}
		} else
		{
			// debugging info
			if(print >10){
				printf("loss: %f\n",ML::loss_func(para,data));
				printf("parameters: ");
				for (size_t i = 0; i < PARAMS; i++) {
					std::cout << para[i];
					if (i < PARAMS - 1) {
						std::cout << ", ";
					}
				}
				printf("\n");
				printf("\033[%dA",2); // Move up 2 lines;
				print = 0;
			}
			print++;
			// define the line to be drawn
			for (size_t i = 0; i < WIDTH; i++)
			{
				// Map i to the original data x range
				float x = min.x + (max.x - min.x) * (float(i) / (WIDTH - EDGE));

				// Get the function value
				float y = ML::hypothesis(x, para);

				// Scale x and y to screen coordinates
				float scaled_x = ((x - min.x) / (max.x - min.x)) * (WIDTH - EDGE);
				float scaled_y = HEIGHT - EDGE - ((y - min.y) / (max.y - min.y)) * (HEIGHT - EDGE);

				line[i] = Point(scaled_x, scaled_y,sf::Color::Green);
			}
			
			// perform a single step of gradient descent
			ML::batch_gradient_descent_step(para, data);
			window.draw(reinterpret_cast<sf::Vertex*>(point), WIDTH, sf::Points);
			window.draw(reinterpret_cast<sf::Vertex*>(line), WIDTH, sf::Points);
			
		}

		window.display();
	}
	// print final parameters
	std::cout << "\nFinal parameters:\n[";
	for (size_t i = 0; i < PARAMS; i++) {
		std::cout << para[i];
		if (i < PARAMS - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "]\n\n";
	write_final_parameters(para,"final_parameters.txt");


	return 0;
}