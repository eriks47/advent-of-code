#include <iterator>
#include <stdio.h>
#include <vector>
#include <algorithm>

int max_calories(FILE *f)
{
    std::vector<int> cals;

    int calories = 0;
    char c, prev;
    c = prev = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n' && prev == '\n')
        {
            cals.push_back(calories);
            calories = 0;
            continue;
        }
        else if (c == '\n')
            continue;

        int current = 0;
        do
        {
            current = current * 10 + c - '0';
        } while ((c = fgetc(f)) != '\n');
        calories += current;
        prev = c;
    }
    std::sort(cals.begin(), cals.end());
    std::reverse(cals.begin(), cals.end());
    return cals[0] + cals[1] + cals[2];
}

int main()
{
    FILE *f = fopen("input.txt", "r");
    int max = max_calories(f);
    printf("Maximum number of calories: %d\n", max);
    fclose(f);
}
