/*
 ============================================================================
 Name        : permutations.c
 Author      : Iain Hill
 Version     : 1
 Copyright   : GPL

 Description : permutations of a given text string.

    Copyright (C) 2018 Iain Hill. 

 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

char *extract_char(char *str, int i)
{
	char *pt;
	pt = str+(++i);
	/* Overwrites its self intentionaly, comment out for use with
	 * address sanitizer, use memmove instead */
	memcpy(pt-1, pt, strlen(pt)+1);
	//memmove(pt-1, pt, strlen(pt)+1);

	return str;
}

char *insert_char(char *str, char c, int i)
{
	char *pt;
	pt = str+i;
	memmove(pt+1, pt, strlen(pt)+1);
	*pt = c;

	return str;
}

void _permutation(char *str, char *chosen, char *ptr, Trie **trie, int len)
{
	int i;

	if (len == 0)
		tTrie_add_word(trie, chosen);
	else {
		for (i = 0; i < len; i++) {

			// choose
			*ptr++ = *(str+i);
			extract_char(str, i);

			// explore
			_permutation(str, chosen, ptr, trie, len - 1);

			//un-choose
			insert_char(str, *--ptr, i);
			*ptr = '\0';
		}
	}
}

void permutations(char *str)
{
	Trie **trie = NULL;
	char *ptr, *chosen;
	int len = strlen(str);

	ptr = chosen = calloc(1, len+1);
	trie = tTrie_init(trie);

	_permutation(str, chosen, ptr, trie, len);

	tTrie_print(trie);
	tTrie_free(trie);

	free(chosen);
}

int main(int argc, char **argv)
{
	while (--argc)
		permutations(*++argv);

	return 0;
}
