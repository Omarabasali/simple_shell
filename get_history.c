#include "shell.h"

/**
 * get_history_file - which it gets the history file
 * @inf: is the parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *inf)
{
	char *buff, *dire;

	dire = get_env(inf, "HOME=");
	if (!dire)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlengh(dire) + _strlengh(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcopy(buff, dire);
	_strconcat(buff, "/");
	_strconcat(buff, HIST_FILE);
	return (buff);
}

/**
 * create_history - creates a file, or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int create_history(info_t *inf)
{
	ssize_t fdd;
	char *filename = get_history_file(inf);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fdd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdd == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		inp_str(node->str, fdd);
		chr_wr('\n', fdd);
	}
	chr_wr(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * read_hist - it reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hist(info_t *inf)
{
	int i, last = 0, linecount = 0;
	ssize_t fdd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(inf);

	if (!filename)
		return (0);

	fdd = open(filename, O_RDONLY);
	free(filename);
	if (fdd == -1)
		return (0);
	if (!fstat(fdd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fdd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fdd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist_list(inf, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(inf, buf + last, linecount++);
	free(buf);
	inf->histcount = linecount;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_in_index(&(inf->history), 0);
	renum_history(inf);
	return (inf->histcount);
}

/**
 * build_hist_list - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hist_list(info_t *inf, char *buff, int linecount)
{
	list_t *node = NULL;

	if (inf->history)
		node = inf->history;
	add_node_to_end(&node, buff, linecount);

	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
 * renum_history - it renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_history(info_t *inf)
{
	list_t *node = inf->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (inf->histcount = i);
}
