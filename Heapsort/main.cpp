#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

// Utilities
void generate_numbers_vector(std::vector<int>& numbersVector, const int max);
void fisher_yates_shuffle(std::vector<int>& vectorToShuffle);
int random_range(const int min, const int max);
void swap_variables(int& a, int& b, const int waitTime);
void render(const std::vector<int>& numbersVector, const int swappedValue, const int waitTime);

// Heap-sort functions
void shift_down(std::vector<int>& numbersVector, int start, const int end);
void heapify(std::vector<int>& numbersVector, const int count);
void heap_sort(std::vector<int>& numbersVector);

// Globals
sf::RenderWindow WINDOW(sf::VideoMode(800, 600), "Heap-sort Visualisation");
std::vector<int> NUMBERS;

int main()
{
	std::cout << "How many numbers would you like to deal with?" << std::endl;
	int n{ 0 };
	std::cin >> n;
	
	generate_numbers_vector(NUMBERS, n);
	std::cout << "Vector from 1 to n: " << std::endl;
	for (auto& number : NUMBERS)
	{
		std::cout << number << ", ";
	}
	render(NUMBERS, -1, 1000);
	
	std::cout << "\n\n\nShuffled Vector : " << std::endl;
	fisher_yates_shuffle(NUMBERS);
	for (auto& number : NUMBERS)
	{
		std::cout << number << ", ";
	}
	render(NUMBERS, -1, 1000);
	
	std::cout << "\n\n\Heapsort : " << std::endl;
	heap_sort(NUMBERS);
	
	render(NUMBERS, -1, 1000);
	

	
	// Main loop that continues until we call window.close()
	while (WINDOW.isOpen())
	{
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event{};
		while (WINDOW.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				WINDOW.close();
				break;
			default:
				break;
			}
		}

		// We must clear the window each time around the loop
		WINDOW.clear();

		render(NUMBERS, -1, 1.f);


		// Get the window to display its contents
		WINDOW.display();
	}

	return 0;
}

void generate_numbers_vector(std::vector<int>& numbersVector, const int max)
{
	for (int i = 0; i < max; ++i)
	{
		numbersVector.emplace_back(i);
	}
}

void fisher_yates_shuffle(std::vector<int>& vectorToShuffle)
{
	for (size_t i = 0; i < vectorToShuffle.size(); ++i)
	{
		// Generate a random number and swap the current index
		// with the random index
		const auto randomNum{ random_range(0, vectorToShuffle.size()) };
		swap_variables(vectorToShuffle[i], vectorToShuffle[randomNum], 10);
	}
}

int random_range(const int min, const int max)
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

void swap_variables(int& a, int& b, const int waitTime)
{
	const auto c(a);
	a = b;
	b = c;

	render(NUMBERS, a, waitTime);
}

void render(const std::vector<int>& numbersVector, const int swappedValue, const int waitTime)
{
	// We must clear the window each time around the loop
	WINDOW.clear();

	const float rectangleWidth{ static_cast<float>(WINDOW.getSize().x) / numbersVector.size() - 1 };

	for (auto i = 0; i < numbersVector.size(); ++i)
	{
		sf::RectangleShape rectangle(
			{ rectangleWidth, (static_cast<float>(numbersVector[i] + 1) / numbersVector.size()) * (static_cast<float>(WINDOW.getSize().y) - 100) }
		);
		rectangle.setOrigin(0, rectangle.getGlobalBounds().height);

		rectangle.setFillColor(swappedValue == i ? sf::Color::Red : sf::Color::White);

		rectangle.setPosition(static_cast<float>(i) + static_cast<float>(i) * rectangleWidth, static_cast<float>(WINDOW.getSize().y));

		WINDOW.draw(rectangle);
	}

	WINDOW.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
}

void shift_down(std::vector<int>& numbersVector, const int start, const int end)
{
	// the root represents how far down the heap to shift
	int root = start;
	
	while (root * 2 + 1 <= end) // (whilst the root has at least 1 child in the priority queue)
	{
		// point to the left child
		int child = root * 2 + 1;

		// If the child has a sibling and the child's value is less than its sibling's...
		if (child + 1 < end && numbersVector[child] < numbersVector[child + 1])
		{
			// ...Point to the right child instead
			child++;
		}
		// if the root is less than the child, we aren't in max-heap order anymore...
		if (numbersVector[root] < numbersVector[child])
		{
			// So swap them to maintain order...
			swap_variables(numbersVector[root], numbersVector[child], 50);
			root = child; // Set the root to the child to continue shifting down the row
		} else
		{
			return;
		}
	}
}

void heapify(std::vector<int>& numbersVector, const int count)
{
	// Start at the index of the last parent node of the max-heap in the
	// priority queue
	int start = (count - 2) / 2;
	while (start >= 0)
	{
		// Shift down the node at the start index to the proper place such that
		// all nodes below the start index are in max-heap order
		shift_down(numbersVector, start, count - 1);
		start--;
	}

	// After shifting down, all elements should be in max heap order...
	std::cout << "Heapified Vector:\n";
	for (auto& number : numbersVector)
	{
		std::cout << number << ", ";
	}
}

void heap_sort(std::vector<int>& numbersVector)
{
	// Place in a max-heap order...
	heapify(numbersVector, numbersVector.size());

	render(numbersVector, -1, 1000.f);

	int end = numbersVector.size() - 1;

	int count{ 0 };

	while (end > 0)
	{
		// Swap the root of the heap (the maximum value of the vector / the first item in the priority queue)
		// with the current element of the heap
		swap_variables(numbersVector[end], numbersVector[0], 100);

		// Decrement the size of the heap so that the previous max value will stay in its place
		--end;

		// Put the heap back into max heap order
		shift_down(numbersVector, 0, end);
		std::cout << "\nStep " + std::to_string(count++) << ":\n";
		for (auto& number : numbersVector)
		{
			std::cout << number << ", ";
		}
	}
}