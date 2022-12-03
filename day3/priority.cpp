#include <fstream>
#include <iostream>
#include <unordered_set>

uint64_t repeatingPrioritySum(std::ifstream &inputStream)
{
    uint64_t total = 0;
    std::string rucksack;
    while (!std::getline(inputStream, rucksack).eof())
    {
        std::unordered_set<char> set;
        for (int i = 0; i < rucksack.length() / 2; ++i)
            set.insert(rucksack[i]);

        for (int i = rucksack.length() / 2; i < rucksack.length(); ++i)
        {
            char c = rucksack[i];
            if (set.find(c) != set.end())
            {
                total += c > 'Z' ? c - 'a' + 1 : c - 'A' + 27;
                break;
            }
        }
    }
    return total;
}

int main()
{
    std::ifstream inputStream = std::ifstream("input.txt");
    uint64_t total = repeatingPrioritySum(inputStream);
    std::cout << "Sum of priorities of repeating types: " << total << "\n";
    inputStream.close();
}
