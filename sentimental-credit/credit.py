from cs50 import get_string


# call when card is invalid to exit program.
def INVALID():
    print("INVALID")
    exit()

# runs Luhn algorith and returns true if valid and calls INVALID function if not valid.


def luhnAlgorith(number):
    total = 0
    evenSum = 0
    isodd = False
    # loop through list of digits in reverse order.
    for i in range(len(number)-1, -1, -1):

        # if digit is an odd digit add to the odd digit sum.
        if isodd == True:
            isodd = False
            oddNumber = number[i]*2
            if oddNumber > 9:
                oddNumber = (oddNumber - 9)
            total += oddNumber

        # add even digits to sum
        elif isodd == False:
            isodd = True
            evenSum += number[i]
    if (total + evenSum) % 10 == 0:
        return True
    else:
        INVALID()


# sanatize user input.
while True:
    input = get_string("Number: ")
    if input != None:
        # checks that string is numeric and of length 13 or 16.
        if input.isnumeric() and len(input) in (13, 15, 16):
            break
        else:
            INVALID()

# turn string of digits into list of digits
cardNumber = []
for i in input:
    cardNumber.append(int(i))
# check for valid card number.
if cardNumber[0] == 4:
    luhnAlgorith(cardNumber)
    print("VISA")
elif cardNumber[0] == 3 and cardNumber[1] in (4, 7):
    luhnAlgorith(cardNumber)
    print("AMEX")
elif cardNumber[0] == 5 and cardNumber[1] in range(0, 6):
    luhnAlgorith(cardNumber)
    print("MASTERCARD")
else:
    INVALID()

