#include "shell.h"

/**
 * dis_hist - it shows the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: is the structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int dis_hist(info_t *inf)
{
	print_elem(inf->history);
	return (0);
}

/**
 * alias_set - sets alias to string
 * @inf: is parameter struct
 * @alstr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(info_t *inf, char *alstr)
{
	char *p, y;
	int nd;

	p = loc_str(alstr, '=');
	if (!p)
		return (1);
	y = *p;
	*p = 0;
	nd = delete_node_in_index(&(inf->alias),
		get_n_index(inf->alias, node_starts_pref(inf->alias, alstr, -1)));
	*p = y;
	return (nd);
}

/**
 * set_ali - sets alias to string
 * @inf: parameter struct
 * @alstr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_ali(info_t *inf, char *alstr)
{
	char *pp;

	pp = loc_str(alstr, '=');
	if (!pp)
		return (1);
	if (!*++pp)
		return (alias_set(inf, alstr));

	alias_set(inf, alstr);
	return (add_node_to_end(&(inf->alias), alstr, 0) == NULL);
}

/**
 * print_alstr - it prints an alias of  string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alstr(list_t *node)
{
	char *pp = NULL, *h = NULL;

	if (node)
	{
		pp = loc_str(node->str, '=');
		for (h = node->str; h <= pp; h++)
		_writechar(*h);
		_writechar('\'');
		_pri(pp + 1);
		_pri("'\n");
		return (0);
	}
	return (1);
}

/**
 * ali_man - mimics the alias built in
 * @inf: is the structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int ali_man(info_t *inf)
{
	int i = 0;
	char *pp = NULL;
	list_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alstr(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		pp = loc_str(inf->argv[i], '=');
		if (pp)
			set_ali(inf, inf->argv[i]);
		else
			print_alstr(node_starts_pref(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
