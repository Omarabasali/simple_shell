#include "shell.h"

/**
 * add_a_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @st: str field of node
 * @nm: node index used by history
 *
 * Return: the size of list
 */
list_t *add_a_node(list_t **head, const char *st, int nm)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memcon((void *)new_head, 0, sizeof(list_t));
	new_head->num = nm;
	if (st)
	{
		new_head->str = _strduppl(st);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_to_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @st: str field of node
 * @nm: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_to_end(list_t **head, const char *st, int nm)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memcon((void *)new_node, 0, sizeof(list_t));
	new_node->num = nm;
	if (st)
	{
		new_node->str = _strduppl(st);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_alist_str - prints only the str element of a list_t linked list
 * @f: pointer to first node
 *
 * Return: size of list
 */
size_t print_alist_str(const list_t *f)
{
	size_t i = 0;

	while (f)
	{
		_pri(f->str ? f->str : "(nil)");
		_pri("\n");
		f = f->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_in_index - deletes node at given index
 * @head: address of pointer to first node
 * @ind: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_in_index(list_t **head, unsigned int ind)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == ind)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_nodlist - frees all nodes of a list
 * @adhead_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_nodlist(list_t **adhead_ptr)
{
	list_t *node, *next_node, *head;

	if (!adhead_ptr || !*adhead_ptr)
		return;
	head = *adhead_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*adhead_ptr = NULL;
}
