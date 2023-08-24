#include "shell.h"

/**
 * conv_st - it converts a string to an integer
 * @s: which is the string to be converted
 * Return: 0 if no numbers in string, so converted number otherwise
 *       -1 on error
 */
int conv_st(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - to print an error message
 * @inf: is the parameter & return info struct
 * @cnstr: a string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_err(info_t *inf, char *cnstr)
{
	prin_instr(inf->fname);
	prin_instr(": ");
	print_dec(inf->line_count, STDERR_FILENO);
	prin_instr(": ");
	prin_instr(inf->argv[0]);
	prin_instr(": ");
	prin_instr(cnstr);
}

/**
 * print_dec - this function prints a decimal (integer) number (base 10)
 * @inp: which is the input
 * @fdw: the filedescriptor to write to
 *
 * Return: is the number of characters printed
 */
int print_dec(int inp, int fdw)
{
	int (*__putchar)(char) = _writechar;
	int i, counter = 0;
	unsigned int bbs, crnt;

	if (fdw == STDERR_FILENO)
		__putchar = writ_chr;
	if (inp < 0)
	{
		bbs = -inp;
		__putchar('-');
		counter++;
	}
	else
		bbs = inp;
	crnt = bbs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (bbs / i)
		{
			__putchar('0' + crnt / i);
			counter++;
		}
		crnt %= i;
	}
	__putchar('0' + crnt);
	counter++;

	return (counter);
}

/**
 * conv_num - converter function, a clone of itoa
 * @nm: is the number
 * @bs: the base
 * @arf: the argument flags
 *
 * Return: is the string
 */
char *conv_num(long int nm, int bs, int arf)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long d = nm;

	if (!(arf & CONVERT_UNSIGNED) && nm < 0)
	{
		d = -nm;
		sign = '-';

	}
	array = arf & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[d % bs];
		d /= bs;
	} while (d != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rep_fir - which is a function replaces first instance of '#' with '\0'
 * @buff: being the address of the string to modify
 *
 * Return: Always 0;
 */
void rep_fir(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
