#include "shell.h"

/**
 * exi_shel - it just exits the shell
 * @inf: a sttructure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int exi_shel(info_t *inf)
{
	int exitch;

	if (inf->argv[1])
	{
		exitch = conv_st(inf->argv[1]);
		if (exitch == -1)
		{
			inf->status = 2;
			print_err(inf, "Illegal number: ");
			prin_instr(inf->argv[1]);
			writ_chr('\n');
			return (1);
		}
		inf->err_num = conv_st(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * pro_ch_dir - it changes the current directory of the process
 * @inf: Structure containing potential arguments. just used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int pro_ch_dir(info_t *inf)
{
	char *s, *dir, buffer[1024];
	int ch_dir;

	s = getcwd(buffer, 1024);
	if (!s)
		_pri("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = get_env(inf, "HOME=");
		if (!dir)
			ch_dir =
				chdir((dir = get_env(inf, "PWD=")) ? dir : "/");
		else
			ch_dir = chdir(dir);
	}
	else if (_strcompare(inf->argv[1], "-") == 0)
	{
		if (!get_env(inf, "OLDPWD="))
		{
			_pri(s);
			_writechar('\n');
			return (1);
		}
		_pri(get_env(inf, "OLDPWD=")), _writechar('\n');
		ch_dir =
			chdir((dir = get_env(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		ch_dir = chdir(inf->argv[1]);
	if (ch_dir == -1)
	{
		print_err(inf, "can't cd to ");
		prin_instr(inf->argv[1]), writ_chr('\n');
	}
	else
	{
		_setenvar(inf, "OLDPWD", get_env(inf, "PWD="));
		_setenvar(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * ch_crdir - it changes the current directory of the process
 * @inf: a structure containing potential arguments. just used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int ch_crdir(info_t *inf)
{
	char **arg_arry;

	arg_arry = inf->argv;
	_pri("help call works. Function not yet implemented \n");
	if (0)
		_pri(*arg_arry);
	return (0);
}
