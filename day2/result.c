#include <stdio.h>

#define LINE_LENGTH 5

int get_single_line_score(char e, char r)
{
    // A - Rock(1), B - Paper(2), C - Scissors(3)
    // X - Lose, Y - Draw, Z - Win
    int score = 0;
    if (r == 'Y') 
        score += 3;
    else if (r == 'Z') 
        score += 6;
    int value_needed;
    if (r == 'Z')
        value_needed = (e - 'A' + 1) % 3 + 1;
    else if (r == 'Y')
        value_needed = e - 'A' + 1;
    else
        value_needed = e - 'A' == 0 ? 3 : e - 'A';
    score += value_needed;
    return score;
}

int get_total_score(FILE *f)
{
    int score = 0;
    char s[LINE_LENGTH + 1];
    fgets(s, LINE_LENGTH, f);
    while (!feof(f))
    {
        score += get_single_line_score(s[0], s[2]);
        fgets(s, LINE_LENGTH, f);
    }
    return score;
}

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    int score = get_total_score(f);
    printf("Score: %d\n", score);
    fclose(f);
}
