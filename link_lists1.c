#include "shell.h"

/**
 * link_len - which it determines length of linked list
 * @f: pointer to first node
 *
 * Return: size of list
 */
size_t link_len(const list_t *f)
{
	size_t i = 0;

	while (f)
	{
		f = f->next;
		i++;
	}
	return (i);
}

/**
 * list_of_strings - returns an array of strings of the list->str
 * @f: pointer to first node
 *
 * Return: array of strings
 */
char **list_of_strings(list_t *f)
{
	list_t *node = f;
	size_t i = link_len(f), j;
	char **strn;
	char *str;

	if (!f || !i)
		return (NULL);
	strn = malloc(sizeof(char *) * (i + 1));
	if (!strn)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlengh(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strn[j]);
			free(strn);
			return (NULL);
		}

		str = _strcopy(str, node->str);
		strn[i] = str;
	}
	strn[i] = NULL;
	return (strn);
}


/**
 * print_elem - prints all elements of a list_t linked list
 * @f: pointer to first node
 *
 * Return: size of list
 */
size_t print_elem(const list_t *f)
{
	size_t i = 0;

	while (f)
	{
		_pri(conv_num(f->num, 10, 0));
		_writechar(':');
		_writechar(' ');
		_pri(f->str ? f->str : "(nil)");
		_pri("\n");
		f = f->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_pref - returns node whose string starts with prefix
 * @ptr: is the pointer to list head
 * @prefix: is a string to match
 * @n: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_pref(list_t *ptr, char *prefix, char n)
{
	char *pp = NULL;

	while (ptr)
	{
		pp = starts_by(ptr->str, prefix);
		if (pp && ((n == -1) || (*pp == n)))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

/**
 * get_n_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_n_index(list_t *head, list_t *node)
{
	size_t y = 0;

	while (head)
	{
		if (head == node)
			return (y);
		head = head->next;
		y++;
	}
	return (-1);
}
