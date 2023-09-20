#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

//  get point score from character by forcing to lowercase and dropping all characters index by the value of 'a'.
size_t getScoreForLetter(char letter)
{
    return POINTS[(tolower(letter) - 'a')];
}

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //  did player 1 win?
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    //  did player 2 win?
    if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    //  or was it a tie?
    else
    {
        printf("Tie!");
    }
}

//  computes the score of the string.
int compute_score(string word)
{
    size_t length = strlen(word);
    int score = 0;
    for (size_t i = 0; i < length; i++)
    {
        //  ignore non alphabet characters.(same as adding zero for non alphabet characters.)
        if (isalpha(word[i]) != 0)
        {
            score += getScoreForLetter(word[i]);
        }
        
    }
    return score;
}
