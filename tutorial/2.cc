#include <iostream>
#include <vector>
#include <string>

int main()
{

    //
    // Example #1
    //

    // Create a vector<double> of length 0
    std::vector<double> v1;

    // Extend the vector by appending a few values
    v1.push_back(1.1);
    v1.push_back(2.2);
    v1.push_back(3.3);

    // Read a value back using .at(index)
    // and save it to a variable.
    double v1_1 = v1.at(1);

    // We can also read values using [index]
    double v1_2 = v1[2];

    // Get the current size of the vector
    int v1_size = v1.size();

    // Let's print some info
    std::cout << "v1: size: " << v1_size << std::endl;
    std::cout << "v1: elements: "
              << v1.at(0) << ", " << v1.at(1) << ", " << v1.at(2)
              << std::endl;
    std::cout << "v1_1: " << v1_1 << std::endl;
    std::cout << "v1_2: " << v1_2 << std::endl;

    //
    // Example #2
    //

    // Create a vector<int> of length 10
    std::vector<int> v2(10);

    // Assign some values directly
    v2[0] = 0; // Could also do v2.at(0) = 0
    v2[1] = 1; // Could also do v2.at(1) = 1

    // Assign the rest of the elements using a loop.
    // For fun, let's do a Fibonacci sequence.
    for (size_t i = 2; i < v2.size(); i++)
    {
        v2[i] = v2[i - 1] + v2[i - 2];
    }

    // Let's print the content of v2 on a single line using a loop
    std::cout << "v2:";
    for (size_t i = 0; i < v2.size(); i++)
    {
        std::cout << " " << v2[i];
    }
    std::cout << std::endl;

    // Once again, now with an alternative way of looping
    // through the values in a vector
    std::cout << "v2: ";
    for (int value : v2)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    //
    // Example #3 -- other ways to initialize vectors
    //

    // Create a vector<double> of length 5, with all
    // elements intitialised to 1.0
    std::vector<double> v3(5, 1.0);

    // Create a vector<std::string> of length 3,
    // with all elements initialised differently
    std::vector<std::string> v4 = {"AAA", "BBB", "CCC"};

    // We're done
    return 0;
}