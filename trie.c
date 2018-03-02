#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "trie.h"

#define UCHAR 256 /* Length of character index for c_list */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Create and fill
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Trie *_new_c_node(char c)
{
	Trie *new_node = malloc(sizeof(Trie));
	new_node->c = tolower(c);
	new_node->next = NULL;
	new_node->word_end = 0;

	return new_node;
}

Trie **_new_c_list(Trie **list)
{
	int i;
	list = malloc(UCHAR * sizeof(Trie*));

	for (i = 0; i < UCHAR; i++)
		list[i] = NULL;

	return list;
}

void _add_word(Trie *word, char *str)
{
	Trie *c_node = word;

	while (*++str) {

		/* Next node list */
		if (c_node->next == NULL)
			c_node->next = _new_c_list(c_node->next);

		/* Next node */
		if (c_node->next[(int)*str] == NULL)
			c_node->next[(int)*str] = _new_c_node(*str);

		c_node = c_node->next[(int)*str];
	}

	c_node->word_end = 1;
}

void tTrie_add_word(Trie **list, char *str)
{
	if (list[(int)*str] == NULL)
		list[(int)*str] = _new_c_node(*str);

	_add_word(list[(int)*str], str);
}

Trie **tTrie_init(Trie **list)
{
	return _new_c_list(list);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Print
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void _print_word(Trie *word, char *out, char *pt_out)
{
	int i;
	pt_out += sprintf(pt_out, "%c", word->c);

	if (word->next != NULL)
		for (i = 0; i < UCHAR; i++)
			if (word->next[i] != NULL)
				_print_word(word->next[i], out, pt_out);
	if (word->word_end)
		printf("%s\n", out);
}

void _print_list(Trie **list, char *out, char *pt_out)
{
	int i;
	for (i = 0; i < UCHAR; i++)
		if (list[i] != NULL)
			_print_word(list[i], out, pt_out);
}

void tTrie_print(Trie **list)
{
	char *pt, out[UCHAR] = {'\0'};
	pt = out;

	_print_list(list, pt, pt);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Disposal
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void _trie_free_word(Trie *word)
{
	int i;

	if (word->next != NULL) {
		for (i = 0; i < UCHAR; i++)
			if (word->next[i] != NULL)
				_trie_free_word(word->next[i]);
		free(word->next);
	}
	free(word);
}

void tTrie_free(Trie **list)
{
	int i;
	for (i = 0; i < UCHAR; i++)
		if (list[i] != NULL)
			_trie_free_word(list[i]);
	free(list);
}
