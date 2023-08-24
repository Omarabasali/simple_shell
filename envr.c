#include "shell.h"

/**
 * cur_env - it prints current environment
 * @inf: is the structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int cur_env(info_t *inf)
{
	print_alist_str(inf->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @van: env var name
 *
 * Return: the value
 */
char *get_env(info_t *inf, const char *van)
{
	list_t *node = inf->env;
	char *pp;

	while (node)
	{
		pp = starts_by(node->str, van);
		if (pp && *pp)
			return (pp);
		node = node->next;
	}
	return (NULL);
}

/**
 * inith_env - it acts as initializes a new environment variable,
 *             or modify an existing one
 * @inf: is the structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int inith_env(info_t *inf)
{
	if (inf->argc != 3)
	{
		prin_instr("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenvar(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * rem_env - this func removes an environment variable
 * @inf: which is a str containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int rem_env(info_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		prin_instr("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenv(inf, inf->argv[i]);

	return (0);
}

/**
 * pop_env_lis - it populates the env linked list
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int pop_env_lis(info_t *inf)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_to_end(&node, environ[i], 0);
	inf->env = node;
	return (0);
}
