## SFML Heap Sort Algorithm Visualisation
This small project visualises the heapsort algorithm using C++ and SFML. Using a user-defined amount of numbers, the program performs the Fisher-Yates shuffle algorithm on the `std::vector<>` and renders it using bars proportional to the size of the window and the amount of items in the container.  

The user inputs the amount of items they want:
![User input for the amount of items](/showcase/amount.png "User input for the amount of items")

The program displays the contents of the vector when it is shuffled and heapified using a max-heap:
![Shuffled and Heapified](/showcase/shuffled.png "Shuffled and Heapified vectors")

And then the animation plays. Here, n = 50:

![Heapsort Animation](/showcase/anim.gif "Heapsort Animation")
