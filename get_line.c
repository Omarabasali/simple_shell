#include "shell.h"

/**
 * input_bufcha - it just  buffers chained commands
 * @inf: is the parameter struct
 * @buff: is the address of buffer
 * @adlen: which is the address of len var
 *
 * Return: the bytes read
 */
ssize_t input_bufcha(info_t *inf, char **buff, size_t *adlen)
{
	ssize_t y = 0;
	size_t len_p = 0;

	if (!*adlen)
	{

		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		y = getline(buff, &len_p, stdin);
#else
		y = _getnxline(inf, buff, &len_p);
#endif
		if (y > 0)
		{
			if ((*buff)[y - 1] == '\n')
			{
			(*buff)[y - 1] = '\0';
				y--;
			}
			inf->linecount_flag = 1;
			rep_fir(*buff);
			build_hist_list(inf, *buff, inf->histcount++);

			{
				*adlen = y;
				inf->cmd_buf = buff;
			}
		}
	}
	return (y);
}

/**
 * get_lininput - it gets the  line minus the newline
 * @inf: is the parameter struct
 *
 * Return: bytes read
 */
ssize_t get_lininput(info_t *inf)
{
	static char *buff;
	static size_t i, y, lengh;
	ssize_t r = 0;
	char **buf_p = &(inf->arg), *p;

	_writechar(BUF_FLUSH);
	r = input_bufcha(inf, &buff, &lengh);
	if (r == -1)
		return (-1);
	if (lengh)
	{
		y = i;
		p = buff + i;

		ch_chain(inf, buff, &y, i, lengh);
		while (y < lengh)
		{
			if (jk_chain(inf, buff, &y))
				break;
			y++;
		}

		i = y + 1;
		if (i >= lengh)
		{
			i = lengh = 0;
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlengh(p));
	}

	*buf_p = buff;
	return (r);
}

/**
 * reads_buff - reads a buffer
 * @inf: parameter struct
 * @buff: buffer
 * @si: size
 *
 * Return: r
 */
ssize_t reads_buff(info_t *inf, char *buff, size_t *si)
{
	ssize_t r = 0;

	if (*si)
		return (0);
	r = read(inf->readfd, buff, READ_BUF_SIZE);
	if (r >= 0)
		*si = r;
	return (r);
}

/**
 * _getnxline - which it gets the next line of input from STDIN
 * @inf: is the parameter struct
 * @adptr: is the address of pointer to buffer, preallocated or NULL
 * @silen: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getnxline(info_t *inf, char **adptr, size_t *silen)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t y;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *u;

	p = *adptr;
	if (p && silen)
		s = *silen;
	if (i == len)
		i = len = 0;

	r = reads_buff(inf, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	u = loc_str(buf + i, '\n');
	y = u ? 1 + (unsigned int)(u - buf) : len;
	new_p = _reallocate(p, s, s ? s + y : y + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		str_cat(new_p, buf + i, y - i);
	else
		strn_cpy(new_p, buf + i, y - i + 1);

	s += y - i;
	i = y;
	p = new_p;

	if (silen)
		*silen = s;
	*adptr = p;
	return (s);
}

/**
 * sigintHandler - it just blocks ctrl-C
 * @signum: is the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signum)
{
	_pri("\n");
	_pri("$ ");
	_writechar(BUF_FLUSH);
}
