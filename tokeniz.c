#include "shell.h"

/**
 * **splitstr -  splits of any string into words. Repeat delimiters are ignored
 * @strr: the input string
 * @dd: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **splitstr(char *strr, char *dd)
{
	int i, j, r, m, numwords = 0;
	char **s;

	if (strr == NULL || strr[0] == 0)
		return (NULL);
	if (!dd)
		dd = " ";
	for (i = 0; strr[i] != '\0'; i++)
		if (!to_delimate(strr[i], dd)
		&& (to_delimate(strr[i + 1], dd) || !strr[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (to_delimate(strr[i], dd))
			i++;
		r = 0;
		while (!to_delimate(strr[i + r], dd) && strr[i + r])
			r++;
		s[j] = malloc((r + 1) * sizeof(char));
		if (!s[j])
		{
			for (r = 0; r < j; r++)
				free(s[r]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < r; m++)
			s[j][m] = strr[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **splitstr2 - it splits the  string into words
 * @instr: the input string
 * @dd: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splitstr2(char *instr, char dd)
{
	int i, j, r, m, numwords = 0;
	char **s;

	if (instr == NULL || instr[0] == 0)
		return (NULL);
	for (i = 0; instr[i] != '\0'; i++)
		if ((instr[i] != dd && instr[i + 1] == dd) ||
				    (instr[i] != dd && !instr[i + 1]) || instr[i + 1] == dd)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (instr[i] == dd && instr[i] != dd)
			i++;
		r = 0;
		while (instr[i + r] != dd && instr[i + r] && instr[i + r] != dd)
			r++;
		s[j] = malloc((r + 1) * sizeof(char));
		if (!s[j])
		{
			for (r = 0; r < j; r++)
				free(s[r]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < r; m++)
			s[j][m] = instr[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
