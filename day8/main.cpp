#include <iostream>
#include <fstream>
#include <vector>

#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#define ABS(a) ((a) >= 0 ? (a) : -(a))

#define PART 1

std::vector<std::vector<int>> treeHeights;

int isVisible(int y, int x)
{
    int dir[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
    };
    int score = -1;
    int height = treeHeights[y][x];
    for (int i = 0; i < 4; ++i)
    {
        int curDir[2] = {dir[i][0], dir[i][1]};
        bool canSee = true;
        int cy = y;
        int cx = x;
        while (true)
        {
            if (cy < 0 || cx < 0 || cy > treeHeights.size() - 1 || cx > treeHeights[cy].size() - 1)
            {
                if (canSee)
                {
                    int value = ABS(cx - x + cy - y) - 1;
                    if (score == -1)
                        score = value;
                    else
                        score *= value;

                    if (PART == 1)
                        return 1;
                }
                break;
            }

            if ((cx != x || cy != y) && treeHeights[cy][cx] >= height)
            {
                int value = ABS(cx - x + cy - y);
                if (score == -1)
                    score = value;
                else
                    score *= value;
                break;
            }

            cy += curDir[0];
            cx += curDir[1];
        }
    }
#if PART == 1
    return 0;
#elif PART == 2
    return score;
#endif
    return -10;
}

int getNumberOfTreesVisible(std::ifstream &inputStream)
{
    // Read in all the tree heights
    std::string line;
    while (!std::getline(inputStream, line).eof())
    {
        treeHeights.push_back({});
        for (char c: line)
        {
            treeHeights[treeHeights.size() - 1].push_back(c - '0');
        }
    }

    // For each height check all directions for possible open sight
    int visibleCount = 0;
    for (int y = 0; y < treeHeights.size(); ++y)
    {
        for (int x = 0; x < treeHeights[y].size(); ++x)
        {
#if PART == 1
            visibleCount += isVisible(y, x);
#elif PART == 2
            visibleCount = MAX(isVisible(y, x), visibleCount);
#endif
        }
    }
    return visibleCount;
}

int main()
{
    std::ifstream inputStream("input.txt");
    int count = getNumberOfTreesVisible(inputStream);
    std::cout << "Number of trees visible: " << count << std::endl;
}
