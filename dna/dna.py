import csv
import sys


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


def checkMatch(database, strs, sequence):
    match = None
    for person in database:
        match = person["name"]
        for i in strs:
            if int(person[i]) != longest_match(sequence, i):
                match = None
        if match != None:
            return match
                

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        exit("Usage: python dna.py data.csv sequence.txt")

    database = {}
    strs = []
    # TODO: Read database file into a variable
    with open(sys.argv[1]) as file:
        database = csv.DictReader(file)

        strs = database.fieldnames[1:]
        if strs == None:
            exit("internal error fieldnames returned none")
    
        # TODO: Read DNA sequence file into a variable
        with open(sys.argv[2]) as file:
            sequence = file.read()

        # TODO: Find longest match of each STR in DNA sequence
            # TODO: Check database for matching profiles
            person = checkMatch(database, strs, sequence)
            if person == None:
                print("No match")
            else:
                print(person)

    return


main()
