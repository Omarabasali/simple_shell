#include "shell.h"

/**
 * _exsh - exits the shell
 * @inff: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if inff.argv[0] != "exit"
 */
int _exsh(info_t *inff)
{
	int exitc;

	if (inff->argv[1])
	{
		exitc = conv_st(inff->argv[1]);
		if (exitc == -1)
		{
			inff->status = 2;
			print_err(inff, "Illegal number: ");
			prin_instr(inff->argv[1]);
			writ_chr('\n');
			return (1);
		}
		inff->err_num = conv_st(inff->argv[1]);
		return (-2);
	}
	inff->err_num = -1;
	return (-2);
}

/**
 * _chpro - changes the current directory of the process
 * @inff: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _chpro(info_t *inff)
{
	char *s, *dir, buffer[1024];
	int chdir_xx;

	s = getcwd(buffer, 1024);
	if (!s)
		_pri("TODO: >>getcwd failure emsg here<<\n");
	if (!inff->argv[1])
	{
		dir = get_env(inff, "HOME=");
		if (!dir)
			chdir_xx =
				chdir((dir = get_env(inff, "PWD=")) ? dir : "/");
		else
			chdir_xx = chdir(dir);
	}
	else if (_strcompare(inff->argv[1], "-") == 0)
	{
		if (!get_env(inff, "OLDPWD="))
		{
			_pri(s);
			_writechar('\n');
			return (1);
		}
		_pri(get_env(inff, "OLDPWD=")), _writechar('\n');
		chdir_xx =
			chdir((dir = get_env(inff, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_xx = chdir(inff->argv[1]);
	if (chdir_xx == -1)
	{
		print_err(inff, "can't cd to ");
		prin_instr(inff->argv[1]), writ_chr('\n');
	}
	else
	{
		_setenvar(inff, "OLDPWD", get_env(inff, "PWD="));
		_setenvar(inff, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _changdir - changes the current directory of the process
 * @stru: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _changdir(info_t *stru)
{
	char **aru_array;

	aru_array = stru->argv;
	_pri("help call all works. Function not yet implemented \n");
	if (0)
		_pri(*aru_array);
	return (0);
}
