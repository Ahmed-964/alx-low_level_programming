#include <stdio.h>

/**
 * main - Prints the alphabet.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char ok = 'a';
    for (ok = 'a'; ok<= 'z'; ok++)
        {
            putchar(ok);
    }
    putchar('\n');

    return 0;
}
