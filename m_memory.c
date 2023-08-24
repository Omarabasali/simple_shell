#include "shell.h"

/**
 * pofree - it just frees of the pointer and NULLs the address
 * @potr: is the address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int pofree(void **potr)
{
	if (potr && *potr)
	{
		free(*potr);
		*potr = NULL;
		return (1);
	}
	return (0);
}
