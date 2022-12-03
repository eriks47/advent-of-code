#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

uint64_t charToPriority(char c)
{
    return c > 'Z' ? c - 'a' + 1 : c - 'A' + 27;
}

uint64_t badgePrioritySum(std::ifstream &inputStream)
{
    uint64_t total = 0;
    std::string rucksack;
    uint64_t lineNumber = 0;
    std::unordered_map<char, int> map;
    while (!std::getline(inputStream, rucksack).eof())
    {
        std::unordered_set<char> inserted;
        for (char c: rucksack)
        {
            if (inserted.find(c) != inserted.end())
                continue;
            int value;
            if (map.find(c) != map.end())
                value = map.find(c)->second + 1;
            else
                value = 1;
            map[c] = value;
            inserted.insert(c);

            if (value == 3)
            {
                total += charToPriority(c);
                break;
            }
        }
        lineNumber = (lineNumber + 1) % 3;
        if (lineNumber == 0)
            map.clear();
    }
    return total;
}

int main()
{
    std::ifstream inputStream = std::ifstream("input.txt");
    uint64_t total = badgePrioritySum(inputStream);
    std::cout << "Sum of priorities of proper badges: " << total << "\n";
    inputStream.close();
}
