#include "shell.h"

/**
 * msh - main shell loop
 * @inf: being the parameter & return info struct
 * @arv: which is the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int msh(info_t *inf, char **arv)
{
	ssize_t y = 0;
	int builtin_rret = 0;

	while (y != -1 && builtin_rret != -2)
	{
		clear_inform(inf);
		if (interact(inf))
			_pri("$ ");
		writ_chr(BUF_FLUSH);
		y = get_lininput(inf);
		if (y != -1)
		{
			set_inform(inf, arv);
			builtin_rret = find_builtincm(inf);
			if (builtin_rret == -1)
				find_cmdp(inf);
		}
			else if (interact(inf))
			_writechar('\n');
			free_inform(inf, 0);
	}
	create_history(inf);
	free_inform(inf, 1);
	if (!interact(inf) && inf->status)
		exit(inf->status);
	if (builtin_rret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_rret);
}

/**
 * find_builtincm - it finds a builtin command
 * @inf: is the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *	0 if builtin executed successfully,
 *	1 if builtin found but did not successful,
 *	2 if builtin signals exit()
 */
int find_builtincm(info_t *inf)
{
	int y, built_in_rret = -1;
	builtin_table builtintbl[] = {
		{"exit", exi_shel},
		{"env", cur_env},
		{"help", ch_crdir},
		{"history", dis_hist},
		{"setenv", inith_env},
		{"unsetenv", inith_env},
		{"cd", pro_ch_dir},
		{"alias", ali_man},
		{NULL, NULL}
	};

	for (y = 0; builtintbl[y].type; y++)
		if (_strcompare(inf->argv[0], builtintbl[y].type) == 0)
		{
			inf->line_count++;
			built_in_rret = builtintbl[y].func(inf);
			break;
		}
	return (built_in_rret);
}

/**
 * find_cmdp - finds a command in PATH
 * @inf: is the parameter & return info struct
 *
 * Return: void
 */
void find_cmdp(info_t *inf)
{
	char *ppath = NULL;
	int i, y;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (i = 0, y = 0; inf->arg[i]; i++)
		if (!to_delimate(inf->arg[i], " \t\n"))
			y++;
	if (!y)
		return;

	ppath = find_apath(inf, get_env(inf, "PATH="), inf->argv[0]);
	if (ppath)
	{
		inf->path = ppath;
		fork_cmdx(inf);
	}
	else
	{
		if ((interact(inf) || get_env(inf, "PATH=")
					|| inf->argv[0][0] == '/') && det_cmd(inf, inf->argv[0]))
			fork_cmdx(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_err(inf, "not found\n");
		}
	}
}

/**
 * fork_cmdx - forks  an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmdx(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_envir(inf)) == -1)
		{
			free_inform(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_err(inf, "Permission denied\n");
		}
	}
}
