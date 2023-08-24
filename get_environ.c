#include "shell.h"

/**
 * get_envir - it just returns a string array copy of our environ
 * @inf: is a structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_envir(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_of_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenvar - it removes the environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @stvar: the string env var property
 */
int _unsetenvar(info_t *inf, char *stvar)
{
	list_t *node = inf->env;
	size_t i = 0;
	char *pp;

	if (!node || !stvar)
		return (0);

	while (node)
	{
		pp = starts_by(node->str, stvar);
		if (pp && *pp == '=')
		{
			inf->env_changed = delete_node_in_index(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->env_changed);
}

/**
 * _setenvar - it initializes a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @stvar: is the string env var property
 * @stvalue: is the string env var value
 *  Return: Always 0
 */
int _setenvar(info_t *inf, char *stvar, char *stvalue)
{
	char *buf = NULL;
	list_t *node;
	char *pp;

	if (!stvar || !stvalue)
		return (0);

	buf = malloc(_strlengh(stvar) + _strlengh(stvalue) + 2);
	if (!buf)
		return (1);
	_strcopy(buf, stvar);
	_strconcat(buf, "=");
	_strconcat(buf, stvalue);
	node = inf->env;
	while (node)
	{
		pp = starts_by(node->str, stvar);
		if (pp && *pp == '=')
		{
			free(node->str);
			node->str = buf;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_to_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}
