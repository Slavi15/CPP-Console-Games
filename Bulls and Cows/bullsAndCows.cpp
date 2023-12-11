#include <iostream>

using namespace std;

const int DIGITS_COUNT = 4;

unsigned userInput();
void getBullsAndCows(unsigned toGuess, unsigned myGuess, unsigned &bulls, unsigned &cows);
unsigned getBulls(unsigned toGuess, unsigned myGuess);
unsigned getCows(unsigned toGuess, unsigned myGuess);
void incrementCows(unsigned myGuess, unsigned compareNumber, unsigned &cowsCount);
bool isValidInput(unsigned num);
unsigned getDigitsCount(unsigned num);
unsigned countDigitOccurences(unsigned num, unsigned position); 
bool isNumberSpecial(unsigned num);

int main()
{
    unsigned toGuess = userInput();
    cout << "Congratulations! Try to guess the number!" << endl;

    unsigned bulls, cows;

    do
    {
        unsigned myGuess = userInput();
        getBullsAndCows(toGuess, myGuess, bulls, cows);
        cout << "Bulls: " << bulls << " Cows: " << cows << endl;
    } while (bulls != DIGITS_COUNT);

    cout << "You guessed it!" << endl;

    return 0;
}

unsigned userInput()
{
    unsigned n;
    do
    {
        cin >> n;
    } while (!isValidInput(n));
    return n;
}

void getBullsAndCows(unsigned toGuess, unsigned myGuess, unsigned &bulls, unsigned &cows)
{
    bulls = getBulls(toGuess, myGuess);
    cows = getCows(toGuess, myGuess) - bulls;
}

unsigned getBulls(unsigned toGuess, unsigned myGuess)
{
    unsigned bullsCount = 0;

    while (toGuess != 0)
    {
        if (toGuess % 10 == myGuess % 10)
            bullsCount++;
        
        toGuess /= 10;
        myGuess /= 10;
    }

    return bullsCount;
}

unsigned getCows(unsigned toGuess, unsigned myGuess)
{
    unsigned cowsCount = 0;

    while (toGuess != 0)
    {
        int lastDigit = toGuess % 10;
        incrementCows(myGuess, lastDigit, cowsCount);
        toGuess /= 10;
    }

    return cowsCount;
}

void incrementCows(unsigned myGuess, unsigned compareNumber, unsigned &cowsCount)
{
    while (myGuess != 0)
    {
        int lastDigit = myGuess % 10;
        if (lastDigit == compareNumber)
            cowsCount++;

        myGuess /= 10;
    }
}

bool isValidInput(unsigned num)
{
    return isNumberSpecial(num) && getDigitsCount(num) == DIGITS_COUNT;
}

unsigned getDigitsCount(unsigned num)
{
    if (num == 0)
        return 1;

    unsigned count = 0;

    while (num != 0)
    {
        count++;
        num /= 10;
    }

    return count;
}

unsigned countDigitOccurences(unsigned num, unsigned position)
{
    unsigned count = 0;

    while (num != 0)
    {
        int lastDigit = num % 10;
        if (lastDigit == position)
            count++;
        num /= 10;
    }

    return count;
}

bool isNumberSpecial(unsigned num)
{
    for (unsigned i = 0; i <= 9; i++)
        if (countDigitOccurences(num, i) > 1)
            return false;

    return true;
}