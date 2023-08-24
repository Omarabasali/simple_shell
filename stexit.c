#include "shell.h"

/**
 **strn_cpy - which it copies a string
 *@stdst: is the destination string to be copied to
 *@stsrc: which is the source string
 *@am: the amount of characters to be copied
 *Return: the concatenated string
 */
char *strn_cpy(char *stdst, char *stsrc, int am)
{
	int i, y;
	char *s = stdst;

	i = 0;
	while (stsrc[i] != '\0' && i < am - 1)
	{
		stdst[i] = stsrc[i];
		i++;
	}
	if (i < am)
	{
		y = i;
		while (y < am)
		{
			stdst[y] = '\0';
			y++;
		}
	}
	return (s);
}

/**
 **str_cat - it just concatenate of two strings
 *@fst: being the first string
 *@sst: being the second string
 *@am: is the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *str_cat(char *fst, char *sst, int am)
{
	int i, y;
	char *s = fst;

	i = 0;
	y = 0;
	while (fst[i] != '\0')
		i++;
	while (sst[y] != '\0' && y < am)
	{
		fst[i] = sst[y];
		i++;
		y++;
	}
	if (y < am)
		fst[i] = '\0';
	return (s);
}

/**
 **loc_str - to locate a character in a string
 *@str: is the string to be parsed
 *@chr: the character to look for
 *Return: (str) a pointer to the memory area s
 */
char *loc_str(char *str, char chr)
{
	do {
		if (*str == chr)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
