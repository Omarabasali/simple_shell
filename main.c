#include "shell.h"

/**
 * mainint - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int mainint(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int dd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (dd)
			: "r" (dd));

	if (ac == 2)
	{
		dd = open(av[1], O_RDONLY);
		if (dd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				prin_instr(av[0]);
				prin_instr(": 0: Can't open ");
				prin_instr(av[1]);
				writ_chr('\n');
				writ_chr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = dd;
	}
	pop_env_lis(info);
	read_hist(info);
	msh(info, av);
	return (EXIT_SUCCESS);
}
