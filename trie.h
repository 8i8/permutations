/*
 ============================================================================
 Name        : trie.c trie.h
 Author      : Iain Hill
 Version     : 1
 Copyright   : GPL

 Description : trie data structure for C programming.

    Copyright (C) 2018 Iain Hill. 

 ============================================================================
 */
typedef struct Trie {
	int c;
	struct Trie **next;
	int word_end;
} Trie;


/* Print trie list to terminal */
void tTrie_print(Trie **list);

/* Create a new trie list */
Trie **tTrie_init(Trie **listing);

/* Add a new word to the trie */
void tTrie_add_word(Trie **list, char* str);

/* Dispose of trie */
void tTrie_free(Trie **list);
