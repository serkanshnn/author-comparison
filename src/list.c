#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct node* add_word(struct node *list, char *word) {
    struct node *cur = NULL;
#ifdef WITH_UTHASH
    /* TODO: Hash kodu */
    //HASH_FIND_STR(list, word, cur);
#else
    /* TODO: Bagli liste kodu */
    int count = 0;
	struct node *new_node = malloc(sizeof(struct node));
	cur = list;

	new_node->word = word;
	new_node->count = 1;
	new_node->next = NULL;

	if(cur->next == NULL){
		return new_node;
	}

	while(cur->next != NULL){
		if (!strcmp(cur->word, word)){
			cur->count++;
			count++;
		}
		cur = cur->next;
	}

	if(!count && cur->next == NULL){
		cur->next = new_node;
	}

	free(new_node);

#endif

	return cur;


}
