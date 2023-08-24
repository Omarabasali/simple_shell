#include "shell.h"

/**
 * jk_chain - it tests if the current char in buffer is a chain delimeter
 * @inf: is the parameter struct
 * @buff: which is the char buffer
 * @pp: is the address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int jk_chain(info_t *inf, char *buff, size_t *pp)
{
	size_t jc = *pp;

	if (buff[jc] == '|' && buff[jc + 1] == '|')
	{
		buff[jc] = 0;
		jc++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buff[jc] == '&' && buff[jc + 1] == '&')
	{
		buff[jc] = 0;
		jc++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[jc] == ';')
	{
		buff[jc] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pp = jc;
	return (1);
}

/**
 * ch_chain - it checks we have to continue chaining based on last status
 * @inf: which is the parameter struct
 * @buff: is the char buffer
 * @pp: address of current position in buff
 * @y: starting position in buff
 * @lengh: length of buff
 *
 * Return: Void
 */
void ch_chain(info_t *inf, char *buff, size_t *pp, size_t y, size_t lengh)
{
	size_t j = *pp;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[y] = 0;
			j = lengh;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[y] = 0;
			j = lengh;
		}
	}

	*pp = j;
}

/**
 * rep_alias - which it replaces an aliases in the tokenized string
 * @inf: is the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info_t *inf)
{
	int y;
	list_t *node;
	char *pp;

	for (y = 0; y < 10; y++)
	{
		node = node_starts_pref(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		pp = loc_str(node->str, '=');
		if (!pp)
			return (0);
		pp = _strduppl(pp + 1);
		if (!pp)
			return (0);
		inf->argv[0] = pp;
	}
	return (1);
}

/**
 * rep_vars - it just replaces the vars in the tokenized string
 * @inf: is the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *inf)
{
	int y = 0;
	list_t *node;

	for (y = 0; inf->argv[y]; y++)
	{
		if (inf->argv[y][0] != '$' || !inf->argv[y][1])
			continue;

		if (!_strcompare(inf->argv[y], "$?"))
		{
			rep_str(&(inf->argv[y]),
					_strduppl(conv_num(inf->status, 10, 0)));
			continue;
		}
		if (!_strcompare(inf->argv[y], "$$"))
		{
			rep_str(&(inf->argv[y]),
					_strduppl(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_pref(inf->env, &inf->argv[y][1], '=');
		if (node)
		{
			rep_str(&(inf->argv[y]),
					_strduppl(loc_str(node->str, '=') + 1));
			continue;
		}
		rep_str(&inf->argv[y], _strduppl(""));

	}
	return (0);
}

/**
 * rep_str - it replaces string
 * @past: the address of old string
 * @nnew: is the new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str(char **past, char *nnew)
{
	free(*past);
	*past = nnew;
	return (1);
}
