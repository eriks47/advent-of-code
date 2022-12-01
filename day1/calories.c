#include <stdio.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)

int max_calories(FILE *f)
{
    char c;
    int calories, max;
    calories = max = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n')
        {
            max = MAX(max, calories);
            calories = 0;
            continue;
        }

        int current = 0;
        do
        {
            current = current * 10 + c - '0';
        } while ((c = fgetc(f)) != '\n');
        calories += current;
    }
    return max;
}

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    int max = max_calories(f);
    printf("Maximum number of calories: %d\n", max);
    fclose(f);
}
