#include "shell.h"

/**
 * clear_inform - initializes info_t struct
 * @inf: struct address
 */
void clear_inform(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_inform - initializes info_t struct
 * @inf: struct address
 * @av: argument vector
 */
void set_inform(info_t *inf, char **av)
{
	int i = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = splitstr(inf->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strduppl(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		rep_alias(inf);
		rep_vars(inf);
	}
}

/**
 * free_inform - frees info_t struct fields
 * @inf: struct address
 * @allf: true if freeing all fields
 */
void free_inform(info_t *inf, int allf)
{
	freest(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (allf)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_nodlist(&(inf->env));
		if (inf->history)
			free_nodlist(&(inf->history));
		if (inf->alias)
			free_nodlist(&(inf->alias));
		freest(inf->environ);
			inf->environ = NULL;
		pofree((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_writechar(BUF_FLUSH);
	}
}
