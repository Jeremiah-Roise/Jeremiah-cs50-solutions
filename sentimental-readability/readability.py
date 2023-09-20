#!/usr/bin/python3
from cs50 import get_string


# checks whether a string is alphabetical.
def isAlpha(text):
    for i in text:
        char = ord(i)
        if not ((char > (ord('a')-1) and char < (ord('z')+1)) or (char > (ord('A')-1) and char < (ord('Z')+1))):
            return False
    return True


# gets all ascii chars from startIndex until space or end of string is encountered.
def getWord(startIndex, text):
    word = ""
    recording = False 
    for i in range(startIndex, len(text)):
        char = text[i]

        # first activation starts recording, second activation stops recording and exits.
        if char == ' ':
            if recording == True:
                return (word, i)
            recording = False
        else:
            if recording == False:
                recording = True
            if recording == True:
                word += char

    return (word, 0)


# returns number of words in string.
def getWords(text):
    nextWordStart = 0
    count = 0
    while True:
        word, tmp = getWord(nextWordStart, text)
        nextWordStart = tmp
        count += 1
        if tmp == 0:
            return count


# gets sentence starting at start index.
def getSentence(startIndex, text):
    word = ""
    recording = False 
    for i in range(startIndex, len(text)):
        char = text[i]

        if char in {'!', '.', '?'}:
            if recording == True:
                return (word, i)
            recording = False
        else:
            if recording == False:
                recording = True
            if recording == True:
                word += char

    return (word, 0)


# returns number of sentences in string.
def getSentences(text):
    nextWordStart = 0
    count = 0
    while True:
        word, tmp = getSentence(nextWordStart, text)
        nextWordStart = tmp
        if tmp == 0:
            return count
        count += 1


# returns number of alphabetical chars in string.
def getLetters(text):
    count = 0
    for i in text:
        char = ord(i)
        if (char > (ord('a')-1) and char < (ord('z')+1)) or (char > (ord('A')-1) and char < (ord('Z')+1)):
            count += 1
    return count


text = get_string("Text: ")

# get all data for calculation of grade level.
numberOfWords = getWords(text)
numberOfLetters = getLetters(text)
numberOfSentences = getSentences(text)

# do grade calculation.
lettersPerHundred = numberOfLetters / numberOfWords * 100
sentencesPerHundred = numberOfSentences / numberOfWords * 100
gradeLevel = 0.0588 * lettersPerHundred - 0.296 * sentencesPerHundred - 15.8

# formatted output.
if gradeLevel < 1:
    print("Before Grade 1")
elif gradeLevel > 16:
    print("Grade 16+")
else:
    print("Grade ", round(gradeLevel))
