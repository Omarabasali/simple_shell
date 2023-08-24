#include "shell.h"

/**
 * det_cmd - determines if the  file is an executable command
 * @inf: is the info struct
 * @ppath: is the path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int det_cmd(info_t *inf, char *ppath)
{
	struct stat st;

	(void)inf;
	if (!ppath || stat(ppath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duppl_chars - which it duplicates the characters
 * @pathst: is the PATH string
 * @startin: starting index
 * @stopin: stopping index
 *
 * Return: pointer to new buffer
 */
char *duppl_chars(char *pathst, int startin, int stopin)
{
	static char buf[1024];
	int i = 0, y = 0;

	for (y = 0, i = startin; i < stopin; i++)
		if (pathst[i] != ':')
			buf[y++] = pathst[i];
	buf[y] = 0;
	return (buf);
}

/**
 * find_apath - finds this cmd in the PATH string
 * @inf: the info struct
 * @pathst: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_apath(info_t *inf, char *pathst, char *cmd)
{
	int i = 0, curr_poss = 0;
	char *ppath;

	if (!pathst)
		return (NULL);
	if ((_strlengh(cmd) > 2) && starts_by(cmd, "./"))
	{
		if (det_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathst[i] || pathst[i] == ':')
		{
			ppath = duppl_chars(pathst, curr_poss, i);
			if (!*ppath)
				_strconcat(ppath, cmd);
			else
			{
				_strconcat(ppath, "/");
				_strconcat(ppath, cmd);
			}
			if (det_cmd(inf, ppath))
				return (ppath);
			if (!pathst[i])
				break;
			curr_poss = i;
		}
		i++;
	}
	return (NULL);
}
