#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

sf::RenderWindow window(sf::VideoMode(800, 600), "Heapsort Visualisation");
std::vector<int> numbers;

void Render(const std::vector<int>& collection, const int waitTime)
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

void SwapVariables(int& a, int& b, const int waitTime)
{
	const auto c(a);
	a = b;
	b = c;

	Render(numbers, waitTime);	
}

void ShiftDown(std::vector<int>& numbersVector, int startIndex, const int max)
{
	int root = startIndex;
	while(root * 2 + 1 <= max)
	{
		int child = root * 2 + 1;
		if(child + 1 < max && numbersVector[child] < numbersVector[child + 1])
		{
			child++;
		}
		if(numbersVector[root] < numbersVector[child])
		{
			SwapVariables(numbersVector[root], numbersVector[child], 50);
			root = child;
		}else
		{
			return;
		}
	}
}

void Heapify(std::vector<int>& numbersVector, const int count)
{
	int start = (count - 2) / 2;
	while(start >= 0)
	{
		ShiftDown(numbersVector, start, count - 1);
		start--;
	}

	std::cout << "Heapified Vector:\n";
	for (auto& number : numbersVector)
	{
		std::cout << number << ", ";
	}
}

void HeapSort(std::vector<int>& numbersVector)
{
	Heapify(numbersVector, numbersVector.size());
	
	Render(numbersVector, 1000.f);
	
	int end = numbersVector.size() - 1;
	
	int count{ 0 };
	
	while(end > 0)
	{
		SwapVariables(numbersVector[end], numbersVector[0], 100);
		end--;
		ShiftDown(numbersVector, 0, end);
		std::cout << "\nStep " + std::to_string(count++) <<":\n";
		for (auto& number : numbersVector)
		{
			std::cout << number << ", ";
		}
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
		SwapVariables(vectorToShuffle[i], vectorToShuffle[randomNum], 10);
	}
}

void GenerateNumbersVector(std::vector<int>& numbersVector, const int max)
{
	for (int i = 0; i < max; ++i)
	{
		numbersVector.emplace_back(i);
	}
}


int main()
{
	std::cout << "How many numbers would you like to deal with?" << std::endl;
	int n{ 0 };
	std::cin >> n;
	
	GenerateNumbersVector(numbers, n);
	std::cout << "Vector from 1 to n: " << std::endl;
	for (auto& number : numbers)
	{
		std::cout << number << ", ";
	}
	Render(numbers, 1000);
	
	std::cout << "\n\n\nShuffled Vector : " << std::endl;
	FisherYatesShuffle(numbers);
	for (auto& number : numbers)
	{
		std::cout << number << ", ";
	}
	Render(numbers, 1000);
	
	std::cout << "\n\n\Heapsort : " << std::endl;
	HeapSort(numbers);
	
	Render(numbers, 1000);
	

	
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

		Render(numbers, 1.f);


		// Get the window to display its contents
		window.display();
	}

	return 0;
}
