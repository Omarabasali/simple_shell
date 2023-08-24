#include "shell.h"

/**
 * _memcon - which it fills memory with a constant byte
 * @ps: the pointer to the memory area
 * @by: the byte to fill *s with
 * @am: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memcon(char *ps, char by, unsigned int am)
{
	unsigned int i;

	for (i = 0; i < am; i++)
		ps[i] = by;
	return (ps);
}

/**
 * freest - it frees a string of strings
 * @ss: is the string of strings
 */
void freest(char **ss)
{
	char **u = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(u);
}

/**
 * _reallocate - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @pre_size: byte size of previous block
 * @nex_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_reallocate(void *ptr, unsigned int pre_size, unsigned int nex_size)
{
	char *pp;

	if (!ptr)
		return (malloc(nex_size));
	if (!nex_size)
		return (free(ptr), NULL);
	if (nex_size == pre_size)
		return (ptr);

	pp = malloc(nex_size);
	if (!pp)
		return (NULL);

	pre_size = pre_size < nex_size ? pre_size : nex_size;
	while (pre_size--)
		pp[pre_size] = ((char *)ptr)[pre_size];
	free(ptr);
	return (pp);
}
