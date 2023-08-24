#include "shell.h"

/**
 * _strlengh - which it returns the length of a string
 * @str: the string whose length to check
 *
 * Return: an integer length of string
 */
int _strlengh(char *str)
{
	int y = 0;

	if (!str)
		return (0);

	while (*str++)
		y++;
	return (y);
}

/**
 * _strcompare - performs lexicogarphic comparison of two strangs.
 * @st1: the first strang
 * @st2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcompare(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * starts_by - which it checks if needle starts with haystack
 * @hystck: is the string to search
 * @nidle: the substring to find
 *
 * Return: the address of next char of haystack or NULL
 */
char *starts_by(const char *hystck, const char *nidle)
{
	while (*nidle)
		if (*nidle++ != *hystck++)
			return (NULL);
	return ((char *)hystck);
}

/**
 * _strconcat - it just concatenates of two strings
 * @dd: is the destination buffer
 * @ssrcc: the source buffer
 *
 * Return: a pointer to destination buffer
 */
char *_strconcat(char *dd, char *ssrcc)
{
	char *rett = dd;

	while (*dd)
		dd++;
	while (*ssrcc)
		*dd++ = *ssrcc++;
	*dd = *ssrcc;
	return (rett);
}
