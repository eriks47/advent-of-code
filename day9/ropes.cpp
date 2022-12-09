#include <iostream>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#define ABS(a) ((a) >= 0 ? (a) : -(a))

struct Point
{
    int x, y;
};

void pushNextTo(int *value, int target)
{
    int modifier = 0;
    if (target - *value > 0)
        modifier = -1;
    else
        modifier = 1;
    *value += target - *value + modifier;
}

int getNumberOfPositionsVisited(std::ifstream &inputStream)
{
    std::set<std::pair<int, int>> visited;
    Point head = {0, 0};
    Point tail = {0, 0};
    std::string line;
    while (!std::getline(inputStream, line).eof())
    {
        // Parse input
        char direction;
        int stepCount;
        sscanf(line.c_str(), "%c %d", &direction, &stepCount);

        for (int i = 0; i < stepCount; ++i)
        {
            // Move head
            switch (direction)
            {
            case 'R':
                ++head.x;
                break;
            case 'L':
                --head.x;
                break;
            case 'U':
                ++head.y;
                break;
            case 'D':
                --head.y;
                break;
            }

            // Move tail
            // If in different row and column and not touching -- move diagonaly
            if (ABS(head.x - tail.x) == 2 && head.y != tail.y)
            {
                tail.y = head.y;
                pushNextTo(&tail.x, head.x);
            }
            else if (ABS(head.y - tail.y) == 2 && head.x != tail.x)
            {
                tail.x = head.x;
                pushNextTo(&tail.y, head.y);
            }

            // If in same row or column -- push it 
            else if (ABS(head.x - tail.x) == 2 || ABS(head.y - tail.y) == 2)
            {
                if (tail.x != head.x)
                    pushNextTo(&tail.x, head.x);
                else if (tail.y != head.y)
                    pushNextTo(&tail.y, head.y);
            }

            // Populate `visited`
            visited.insert(std::make_pair(tail.x, tail.y));
        }
    }
    return visited.size();
}

int main()
{
    std::ifstream inputStream("input.txt");
    int visitedCount = getNumberOfPositionsVisited(inputStream);
    std::cout << "Number of position visited: " << visitedCount << "\n";
}
