#include "shell.h"
#include "shell.h"

/**
 * interact - returns true if shell is interactive mode
 * @dat: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int interact(info_t *dat)
{
	return (isatty(STDIN_FILENO) && dat->readfd <= 2);
}

/**
 * to_delimate - ti just checks if character is a delimeter or not
 * @qw: is the char to check
 * @delimate: is the delimeter string
 * Return: 1 if true, 0 for  false
 */
int to_delimate(char qw, char *delimate)
{
	while (*delimate)
		if (*delimate++ == qw)
			return (1);
	return (0);
}

/**
 * _alphacar - checks for alphabetic character
 * @um: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _alphacar(int um)
{
	if ((um >= 'a' && um <= 'z') || (um >= 'A' && um <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _convst - which it converts a string to an integer
 * @ring: is the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _convst(char *ring)
{
	int zx, cor = 1, llag = 0, output;
	unsigned int result = 0;

	for (zx = 0; ring[zx] != '\0' && llag != 2; zx++)
	{
		if (ring[zx] == '-')
			cor *= -1;

		if (ring[zx] >= '0' && ring[zx] <= '9')
		{
			llag = 1;
			result *= 10;
			result += (ring[zx] - '0');
		}
		else if (llag == 1)
			llag = 2;
	}

	if (cor == -1)
		output = -result;
	else
		output = result;

	return (output);
}
