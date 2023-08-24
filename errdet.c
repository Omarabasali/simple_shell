#include "shell.h"

/**
 * prin_instr - it prints an input string
 * @strp: which is the string to be printed
 *
 * Return: None
 */
void prin_instr(char *strp)
{
	int i = 0;

	if (!strp)
		return;
	while (strp[i] != '\0')
	{
		writ_chr(strp[i]);
		i++;
	}
}

/**
 * writ_chr - writes the character chr to stderr
 * @chr: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writ_chr(char chr)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buf[i++] = chr;
	return (1);
}

/**
 * chr_wr - writes the character c to given fd
 * @chr: The character to print
 * @fdw: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int chr_wr(char chr, int fdw)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fdw, buf, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buf[i++] = chr;
	return (1);
}

/**
 * inp_str - it prints an input string
 * @str: as the string to be printed
 * @fdw: as the filedescriptor to write to
 *
 * Return: number of chars put
 */
int inp_str(char *str, int fdw)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += chr_wr(*str++, fdw);
	}
	return (i);
}
