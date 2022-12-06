#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_set>

// The only difference between part 1 and part 2 is
// the length of the marker, the lengths are 4 and 14 accordingly.
#define LENGTH_OF_MARKER 14

int getFirstMarkerEnd(std::ifstream &inputStream)
{
    std::unordered_set<char> lastRead;
    std::queue<char> queue;

    int i;
    char c;
    inputStream >> c;
    for (i = 0; !inputStream.eof(); inputStream >> c, ++i)
    {
        if (lastRead.size() == 14)
            break;

        if (lastRead.find(c) != lastRead.end())
        {
            while (queue.front() != c)
            {
                char c = queue.front();
                lastRead.erase(c);
                queue.pop();
            }
            char c = queue.front(); // We also need to repeat the
            lastRead.erase(c);      // procedure for one more time
            queue.pop();            // to remove `c` itself
        }
        lastRead.insert(c);
        queue.push(c);
    }
    return i;
}

int main()
{
    std::ifstream inputStream("input.txt");
    int position = getFirstMarkerEnd(inputStream);
    std::cout << "First marker end is at character number " << position << "\n";
}
