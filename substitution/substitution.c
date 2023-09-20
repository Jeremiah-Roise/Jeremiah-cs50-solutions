#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//  a simple function that checks whether a char* is alphabetical.
bool strisalpha(const char *input)
{
    size_t length = strlen(input);
    for (size_t i = 0; i < length; i++)
    {
        if (isalpha(input[i]) == 0)
        {
            printf("Is not alphabetical!\n");
            printf("%c\n", input[i]);
            return false;
        }
    }
    
    return true;
}

//  check whether the key has the correct number of characters,
//  if it has only alphabetical characters,
//  and, if a character reapeats multiple times in the key.
bool checkKey(const char *Key)
{
    size_t length = strlen(Key);
    if (strisalpha((const char *)Key) == false)
    {
        printf("is not alphabetical!");
        return false;
    }
    
    if (length != 26)
    {
        printf("Wrong key length!\n");
        printf("%i", length);
        return false;
    }
    for (size_t i = 0; i < length; i++)
    {
        for (size_t c = 0; c < length; c++)
        {
            if (Key[i] == Key[c] && c != i)
            {
                printf("error character: %c occures multiple times in key.", Key[i]);
                return false;
            }
            
        }
    }
    return true;
}

//  substitute the characters in the data for the characters in the array.
//  preserves case of the data arg.
string substitute(string data, string key)
{

    size_t dlength = strlen(data);
    size_t klength = strlen(key);
    char formattedData[dlength];
    char formattedKey[klength];
    //  move all characters into an array.
    for (size_t i = 0; i < dlength; i++)
    {
        formattedData[i] = data[i];
    }
    for (size_t i = 0; i < klength; i++)
    {
        const char index = key[i];
        formattedKey[i] = (char)tolower((unsigned int)index);
    }

    char encryptedData[dlength];
    for (size_t i = 0; i < dlength; i++)
    {
        //  this is for preserving case.
        if (isalpha(formattedData[i]) != 0)
        {
            if (islower(formattedData[i]) != 0)
            {
                encryptedData[i] = formattedKey[(formattedData[i] - 'a')];
            }
            else
            {
                //  force value to uppercase
                encryptedData[i] = toupper(formattedKey[(formattedData[i] - 'A')]);
            }
        }
        else
        {
            encryptedData[i] = formattedData[i];
        }
        //  putting the line end at the correct possition so it prints to the screen nicely.
        if (i < dlength)
        {
            encryptedData[i + 1] = '\0';
        }
    }
    printf("ciphertext: %s\n", encryptedData);
}

int main(int argc, char *argv[]) 
{
    //  check for the correct number of args.
    if (argc != 2)
    {
        printf("Wrong number of arguments!\n");
        return 1;
    }
    
    //  performing the key check.
    if (checkKey(argv[1]) == false)
    {
        return 1;
    }
    
    else
    {
        //  get plaintext from user.
        char *tmp = get_string("plaintext: ");
        //  perform substitution.
        substitute(tmp, argv[1]);
    }
}