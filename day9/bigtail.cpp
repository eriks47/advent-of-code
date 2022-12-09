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
    std::vector<Point> knots;
    for (int i = 0; i < 10; ++i)
        knots.push_back({0, 0});
    std::string line;
    while (!std::getline(inputStream, line).eof())
    {
        // Parse input
        char direction;
        int stepCount;
        sscanf(line.c_str(), "%c %d", &direction, &stepCount);

        Point &head = knots[0];
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

            for (int i = 1; i < knots.size(); ++i)
            {
                Point &tail = knots[i];
                Point &head = knots[i - 1];
                int diffX = ABS(head.x - tail.x);
                int diffY = ABS(head.y - tail.y);
                if (diffX + diffY > 2)
                {
                    if (head.y > tail.y)
                        ++tail.y;
                    else
                        --tail.y;

                    if (head.x > tail.x)
                        ++tail.x;
                    else
                        --tail.x;
                }

                else if (diffX == 2 || diffY == 2)
                {
                    if (tail.x != head.x)
                        pushNextTo(&tail.x, head.x);
                    else if (tail.y != head.y)
                        pushNextTo(&tail.y, head.y);
                }

                if (i == knots.size() - 1)
                {
                    Point tail = knots[i];
                    visited.insert(std::make_pair(tail.x, tail.y));
                }
            }
        }
    }
    return visited.size();
}

int main()
{
    std::ifstream inputStream("input.txt");
    int visitedCount = getNumberOfPositionsVisited(inputStream);
    std::cout << "Number of position visited by the tail: " << visitedCount << "\n";
}
