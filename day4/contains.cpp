#include <iostream>
#include <fstream>

int getFullyContainedRanges(std::ifstream &inputStream)
{
    int count = 0;
    int startRange1, endRange1, startRange2, endRange2;
    char c;
    while (!inputStream.eof())
    {
        inputStream >> startRange1;
        inputStream >> c;
        inputStream >> endRange1;
        inputStream >> c;
        inputStream >> startRange2;
        inputStream >> c;
        inputStream >> endRange2;
        if ((startRange1 <= startRange2 && endRange1 >= endRange2) ||
            (startRange2 <= startRange1 && endRange2 >= endRange1))
        {
            ++count;
        }
    }
    return count;
}

int main()
{
    std::ifstream inputStream("input.txt");
    int count = getFullyContainedRanges(inputStream);
    std::cout << "Number of pairs where one range contains other: " << count << "\n";
    inputStream.close();
}
