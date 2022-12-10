#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

struct Promise
{
    int value;
    int cycles;
};

void printCharacter(int cycle, int x)
{
    if ((cycle % 40) - x <= 2 && (cycle % 40) - x >= 0)
        std::cout << "#";
    else
        std::cout << ".";
    if (cycle % 40 == 0)
        std::cout << "\n";
}

void resolvePromises(std::vector<Promise> &promises, int &x)
{
    for (int i = 0; i < promises.size(); ++i)
    {
        Promise &p = promises[i];
        --p.cycles;
        if (p.cycles == 0)
        {
            x += p.value;
            promises.erase(promises.begin() + i);
        }
    }
}

int getStrengthSum(std::ifstream &inputStream)
{
    int strengthSum = 0;
    int interestingCycles[] = {20, 60, 100, 140, 180, 220};
    int ici = 0;
    int x = 1;
    std::string line;
    std::vector<Promise> promises;
    for (int cycle = 1; ; ++cycle)
    {
        if (promises.empty() || promises[promises.size() - 1].cycles != 1)
        {
            if (std::getline(inputStream, line).eof())
                break;
            if (line[0] == 'a')
            {
                char _trash[5];
                int val;
                sscanf(line.c_str(), "%s %d", _trash, &val);
                promises.push_back({.value = val, .cycles = 2});
            }
        }
        printCharacter(cycle, x);
        if (cycle == interestingCycles[ici])
        {
            strengthSum += cycle * x;
            ici = (ici + 1) % 6;
        }
        resolvePromises(promises, x);
    }
    return strengthSum;
}

int main()
{
    std::ifstream inputStream("input.txt");
    int sum = getStrengthSum(inputStream);
    std::cout << "Strength sum is: " << sum << "\n";
}
