#include <stdio.h>

#define LINE_LENGTH 5

int get_single_line_score(char e, char r)
{
    int score = 0;
    score += r - 'X' + 1;
    if ((e == 'A' && r == 'X') || (e == 'B' && r == 'Y') || (e == 'C' && r == 'Z'))
        score += 3;
    else if ((e == 'A' && r == 'Y') || (e == 'B' && r == 'Z') || (e == 'C' && r == 'X'))
        score += 6;
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
