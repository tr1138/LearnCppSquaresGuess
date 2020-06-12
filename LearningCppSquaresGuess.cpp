#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <cmath>

int getInt()
{
    //std::cout << "Enter integer: ";
    int x{};
    std::cin >> x;
    return x;
}

int randomInt(int min, int max)
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::uniform_int_distribution rdm{ min, max };
    return rdm(mt);
}

std::vector<int> generateResultsVector()
{
    //Player supplied starting value
    std::cout << "Start where? ";
    int start{ getInt() };
    
    //Number of values player has to calculate
    std::cout << "How many? ";
    int count{ getInt() };

    int mult{ randomInt(2,4) };

    std::vector<int> numbers;

    //The requested number of values, starting from player's start value, are squared and
    //multiplied by the random multiplier
    for (int i{ 0 }; i < count; ++i)
    {
        numbers.push_back((start + i) * (start + i) * mult);
    }
    
    std::cout << "I generated " << count <<
        " square numbers. Do you know what each number is after multiplying it by " << mult <<
        "?\n";

    return (numbers);
}

void guessGame(std::vector<int> &numbers)
{
    //Player "guesses" the calculated values until all are correct or guess is wrong
    while (!numbers.empty())
    {
        std::cout << "> ";
        int guess{ getInt() };
        
        //check for correct guess
        auto found{ std::find(numbers.begin(), numbers.end(), guess) };
        
        //guess is wrong
        if (found == numbers.end())
        {
            //Lambda is to find the closest remaining number to the guess
            auto nearest{ std::min_element(numbers.begin(), numbers.end(),
                   [=](const auto& a, const auto& b) {return ((std::abs(a - guess)) < (std::abs(b - guess))); }
                   ) };
            
            //std::cout << (*nearest - guess) << '\n'; debug output
            
            if (std::abs(*nearest - guess) < 5)
            {
                std::cout << guess << " is wrong! Try " << *nearest << " next time.\n";
                return;
            }
            else
            {
                std::cout << guess << " is wrong!\n";
                return;
            }
        }

        //Correct guess is removed, leaving others to still find
        else
        {
            numbers.erase(found);
            if (!numbers.empty())
                std::cout << "Nice! " << numbers.size() << " number(s) left.\n";
            else
                std::cout << "Nice! You found all numbers, good job!\n";
        }
    }
}

int main()
{
    std::vector<int> numbers{ generateResultsVector() };

    // cheat for dubug
     
    //for (int element : numbers)
    //    std::cout << element << '\n';
    

     guessGame(numbers);

    return 0;
}