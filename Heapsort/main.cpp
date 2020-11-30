#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

void SwapVariables(int& a, int& b)
{
	const auto c(a);
	b = a;
	b = c;
}


void ShiftDown(std::vector<int>& numbersVector, int startIndex, const int max)
{
	while (startIndex < max)
	{
		int i_big = startIndex;
		const auto c1 = (2 * startIndex) + 1;
		const auto c2 = c1 + 1;
		if (c1 < max && numbersVector[c1] > numbersVector[i_big])
		{
			i_big = c1;
		}
		if (c2 < max && numbersVector[c2] > numbersVector[i_big])
		{
			i_big = c2;
		}
		if (i_big == startIndex)
		{
			return;
		}
		SwapVariables(numbersVector[startIndex], numbersVector[i_big]);
		startIndex = i_big;
	}
}


int RandomRange(const int min, const int max)
{
	static bool first = true;
	if (first)
	{
		//seeding for the first time only!
		srand(time(nullptr));
		first = false;
	}
	return min + rand() % ((max)-min);
}


void FisherYatesShuffle(std::vector<int>& vectorToShuffle)
{
	for (size_t i = 0; i < vectorToShuffle.size(); ++i)
	{
		// Generate a random number and swap the current index
		// with the random index
		const auto randomNum{ RandomRange(0, vectorToShuffle.size()) };
		SwapVariables(vectorToShuffle[i], vectorToShuffle[randomNum]);
	}
}

void GenerateNumbersVector(std::vector<int>& numbersVector, const int max)
{
	for (int i = 0; i < max; ++i)
	{
		numbersVector.emplace_back(i);
	}
}

void Render(const std::vector<int>& collection, const int waitTime, sf::RenderWindow& window)
{
	// We must clear the window each time around the loop
	window.clear();

	const float rectangleWidth{ static_cast<float>(window.getSize().x) / collection.size() - 1 };

	for (unsigned i = 0; i < collection.size(); ++i)
	{
		sf::RectangleShape rectangle(
			{ rectangleWidth, (static_cast<float>(collection[i] + 1) / collection.size()) * (static_cast<float>(window.getSize().y) - 100) }
		);
		rectangle.setOrigin(0, rectangle.getGlobalBounds().height);

		rectangle.setFillColor(sf::Color::White);


		rectangle.setPosition(static_cast<float>(i) + static_cast<float>(i) * rectangleWidth, static_cast<float>(window.getSize().y));

		window.draw(rectangle);
	}

	window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Heapsort Visualisation");

	std::cout << "How many numbers would you like to deal with?" << std::endl;
	int n{ 0 };
	std::cin >> n;
	std::vector<int> numbers;
	GenerateNumbersVector(numbers, n);
	std::cout << "Vector from 1 to n: " << std::endl;
	for (auto& number : numbers)
	{
		std::cout << number << ", ";
	}
	Render(numbers, 1000, window);
	std::cout << "\n\n\nShuffled Vector : " << std::endl;

	FisherYatesShuffle(numbers);
	for (auto& number : numbers)
	{
		std::cout << number << ", ";
	}
	Render(numbers, 1000, window);
	std::cout << "\n\n\nShifted Vector : " << std::endl;

	
	ShiftDown(numbers, 0, static_cast<int>(numbers.size())- 1);
	for (auto& number : numbers)
	{
		std::cout << number << ", ";
	}
	Render(numbers, 1000, window);
	

	
	// Main loop that continues until we call window.close()
	while (window.isOpen())
	{
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event{};
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		// We must clear the window each time around the loop
		window.clear();




		// Get the window to display its contents
		window.display();
	}

	return 0;
}
