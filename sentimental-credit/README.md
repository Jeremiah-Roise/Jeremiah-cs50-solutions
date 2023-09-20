---
files: [credit.py]
url: https://cdn.cs50.net/2022/fall/psets/6/sentimental-credit/README.md
window: [terminal]
---

# Credit

Implement a program that determines whether a provided credit card number is valid according to Luhn’s algorithm.

```
$ python credit.py
Number: 378282246310005
AMEX
```

## Specification

* In `credit.py`, write a program that prompts the user for a credit card number and then reports (via `print`) whether it is a valid American Express, MasterCard, or Visa card number, exactly as you did in Problem Set 1, except that your program this time should be written in Python.
* So that we can automate some tests of your code, we ask that your program’s last line of output be `AMEX\n` or `MASTERCARD\n` or `VISA\n` or `INVALID\n`, nothing more, nothing less.
* For simplicity, you may assume that the user’s input will be entirely numeric (i.e., devoid of hyphens, as might be printed on an actual card).
* Best to use `get_int` or `get_string` from CS50’s library to get users' input, depending on how you to decide to implement this one.


## Usage

Your program should behave per the example below.

```
$ python credit.py
Number: 378282246310005
AMEX
```

## Hints

* It's possible to use regular expressions to validate user input. You might use Python's [`re`](https://docs.python.org/3/library/re.html) module, for example, to check whether the user's input is indeed a sequence of digits of the correct length.

## Testing

While `check50` is available for this problem, you're encouraged to first test your code on your own for each of the following.

* Run your program as `python credit.py`, and wait for a prompt for input. Type in `378282246310005` and press enter. Your program should output `AMEX`.
* Run your program as `python credit.py`, and wait for a prompt for input. Type in `371449635398431` and press enter. Your program should output `AMEX`.
* Run your program as `python credit.py`, and wait for a prompt for input. Type in `5555555555554444` and press enter. Your program should output `MASTERCARD`.
* Run your program as `python credit.py`, and wait for a prompt for input. Type in `5105105105105100` and press enter. Your program should output `MASTERCARD`.
* Run your program as `python credit.py`, and wait for a prompt for input. Type in `4111111111111111` and press enter. Your program should output `VISA`.
* Run your program as `python credit.py`, and wait for a prompt for input. Type in `4012888888881881` and press enter. Your program should output `VISA`.
* Run your program as `python credit.py`, and wait for a prompt for input. Type in `1234567890` and press enter. Your program should output `INVALID`.

Execute the below to evaluate the correctness of your code using `check50`. But be sure to compile and test it yourself as well!

```
check50 cs50/problems/2022/fall/sentimental/credit
```

Execute the below to evaluate the style of your code using `style50`.

```
style50 credit.py
```

## How to Submit

1. Download your `credit.py` file by control-clicking or right-clicking on the file in your codespace's file browser and choosing **Download**.
1. Go to CS50's [Gradescope page](https://www.gradescope.com/).
1. Click "Problem Set 6: Sentimental (Credit)".
1. Drag and drop your `credit.py` file to the area that says "Drag & Drop". Be sure it has that **exact** filename! If you upload a file with a different name, the autograder likely will fail when trying to run it, and ensuring you have uploaded files with the correct filename is your responsibility!
1. Click "Upload".

You should see a message that says "Problem Set 6: Sentimental (Credit) submitted successfully!" You may not see a score just yet, but if you see the message then we've received your submission!

{% alert danger %}

Per Step 4 above, after you submit, be sure to check your autograder results. If you see `SUBMISSION ERROR: missing files (0.0/1.0)`, it means your file was not named exactly as prescribed (or you uploaded it to the wrong problem).

Correctness in submissions entails everything from reading the specification, writing code that is compliant with it, and submitting files with the correct name. If you see this error, you should resubmit right away, making sure your submission is fully compliant with the specification. The staff will not adjust your filenames for you after the fact!

{% endalert %}