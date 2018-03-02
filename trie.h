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
