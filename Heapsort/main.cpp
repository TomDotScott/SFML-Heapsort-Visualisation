#include <iostream>
#include <SFML/Graphics.hpp>
int random(const int min, const int max)
{
    static bool first = true;
    if (first)
    {
        //seeding for the first time only!
        srand(time(nullptr));
        first = false;
    }
    return min + rand() % ((max) - min);
}


void FisherYatesShuffle(std::vector<int>& vectorToShuffle)
{
    for (size_t i = 0; i < vectorToShuffle.size(); ++i)
    {
        // Generate a random number and swap the current index
        // with the random index
        const auto randomNum = random(0, vectorToShuffle.size());
        const auto temp = vectorToShuffle[i];
        vectorToShuffle[i] = vectorToShuffle[randomNum];
        vectorToShuffle[randomNum] = temp;
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
    std::vector<int> numbers;
    GenerateNumbersVector(numbers, n);
    std::cout << "Vector from 1 to n: " << std::endl;
    for (auto& number : numbers)
    {
        std::cout << number << ", ";
    }
    std::cout << "\n\n\nShuffled Vector : " << std::endl;

    FisherYatesShuffle(numbers);
    for (auto& number : numbers)
    {
        std::cout << number << ", ";
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Heapsort Visualisation");
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
