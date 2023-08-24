#include "shell.h"

/**
 * _strcopy - which it copies a string
 * @dd: the destination
 * @ssrcc: being the source
 *
 * Return: is a pointer to destination
 */
char *_strcopy(char *dd, char *ssrcc)
{
	int y = 0;

	if (dd == ssrcc || ssrcc == 0)
		return (dd);
	while (ssrcc[y])
	{
		dd[y] = ssrcc[y];
		y++;
	}
	dd[y] = 0;
	return (dd);
}

/**
 * _strduppl - which it duplicates of any string
 * @strr: is the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strduppl(const char *strr)
{
	int lenn = 0;
	char *rret;

	if (strr == NULL)
		return (NULL);
	while (*strr++)
		lenn++;
	rret = malloc(sizeof(char) * (lenn + 1));
	if (!rret)
		return (NULL);
	for (lenn++; lenn--;)
		rret[lenn] = *--strr;
	return (rret);
}

/**
 * _pri - it prints an input string
 * @strr: is the string to be printed
 *
 * Return: Nothing
 */
void _pri(char *strr)
{
	int y = 0;

	if (!strr)
		return;
	while (strr[y] != '\0')
	{
		_writechar(strr[y]);
		y++;
	}
}

/**
 * _writechar - which it writes the character c to stdout
 * @w: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _writechar(char w)
{
	static int y;
	static char buf[WRITE_BUF_SIZE];

	if (w == BUF_FLUSH || y >= WRITE_BUF_SIZE)
	{
		write(1, buf, y);
		y = 0;
	}
	if (y != BUF_FLUSH)
		buf[y++] = w;
	return (1);
}
