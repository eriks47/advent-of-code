#include <iostream>
#include <fstream>

int getOverlapingRanges(std::ifstream &inputStream)
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

        // Check if one range overlaps with another
        if (startRange1 <= endRange2 && endRange1 >= startRange2)
        {
            ++count;
        }
    }
    return count;
}

int main()
{
    std::ifstream inputStream("input.txt");
    int count = getOverlapingRanges(inputStream);
    std::cout << "Number of pairs where ranges overlap: " << count << "\n";
    inputStream.close();
}
