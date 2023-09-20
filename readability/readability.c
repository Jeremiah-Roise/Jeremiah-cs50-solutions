#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <math.h>
struct slice
{
    size_t sstart;
    size_t send;
};
//  set a slice to have an error.
void word_error(struct slice *x)
{
    x->send = -1;
    x->sstart = -1;
}

//  given the index of the space character before a word will return the index value of the next space.
//  if there is an error such as the index of a non space character being given it will return -1 in the word structure.
struct slice findWord(const char *text, const size_t indexOfWordStart)
{ 
    struct slice tmp  = {.sstart = indexOfWordStart, .send = indexOfWordStart};
    size_t length = strlen(text);
    
    //  find beginning of word.
    for (size_t i = tmp.sstart; i < length; i++)
    {
        if (text[i] == ' ' || text[i] == '\n')
        {
            tmp.sstart++;
        }
        else
        {
            break;
        }
    }

    //  find end of word.
    for (size_t i = tmp.sstart; i < length; i++)
    {
        if (i >= length)
        {
            tmp.send = length;
            break;
        }
        if (text[i] == ' ' || text[i] == '\n')
        {
            tmp.send = (i - 1);
            break;
        }
        else
        {
            tmp.send++;
        }
    }
    return tmp;
}

//  count the number of words in the slice.
size_t count_words(const char *text, const struct slice textSample)
{
    size_t length = strlen(text);
    //  loop through 100 letters and get the total number of words.
    size_t words = 0;
    size_t wordStartIndex = 0;
    struct slice tmp;
    for (size_t i = textSample.sstart; i < textSample.send; i++)
    {
        tmp = findWord(text, wordStartIndex);
        //  check if new end index is less than last end index
        if (tmp.send == -1 || tmp.sstart == -1)
        {
            //  something is very wrong
            printf("Had error!\n");
            break;
        }
        if (tmp.send >= length)
        {
            break;
        }
        
        else
        {
            wordStartIndex = tmp.send + 1;
            words++;
        }
        
        //  use find word and increment
        //  set text sample end to current largest number if number is less than text sample.
    }
    return words;
}

//  count the number of sentences in the slice.
size_t count_sentences(const char *text, const struct slice tmp)
{
    size_t sentenceEndIndex = 0;
    size_t sentences = 0;
    
    for (size_t i = tmp.sstart; i < tmp.send; i++)
    {
        //  find end of sentence.
        //  look for . ? !
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            //  found end.
            sentenceEndIndex = i;
            sentences++;
        }
    }
    return sentences;
}

//  count the number of letters in the slice.
size_t count_letters(const char *text, const struct slice tmp)
{
    size_t letters = 0;
    for (size_t i = tmp.sstart; i < tmp.send; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            letters++;
        }
    }
    return letters;
}

//  takes the inputs and calculates grade level.
const float calculate_grade_level(const size_t words, const size_t letters, const size_t sentences)
{
    float lettersPerHundred = (float)letters / (float)words * 100;
    float sentencesPerHundred = (float)sentences / (float)words * 100;

    return (0.0588f * (float)lettersPerHundred - 0.296f * (float)sentencesPerHundred - 15.8f);
}

int main(int, char **)
{
    string tmp = "";
    tmp = get_string("Text: ");
    printf("\n");

    struct slice all = {.sstart = 0, .send = strlen(tmp)};
    
    size_t wordsnum = count_words(tmp, all);
    size_t letters = count_letters(tmp, all);
    size_t sentences = count_sentences(tmp, all);
    float grade = calculate_grade_level(wordsnum, letters, sentences);
    //  format the grade level.
    if (grade > 16.0f)
    {
        printf("Grade 16+\n");
    }
    if (grade < 1.0f)
    {
        printf("Before Grade 1\n");
    }
    if (grade > 0.0f && grade < 16.0f)
    {
        printf("Grade %i\n", (int)round(grade));
    }
}