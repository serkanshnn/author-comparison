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
    struct node *new = malloc(sizeof(struct node));
    new->word = strdup(word);
    new->count = 1;
    new->next = list;

    cur = list;

    while(cur != NULL){
    	if(!strcmp(word, cur->word)){
    		cur->count++;
    		return list;
    	}
    	cur = cur->next;
    }

    if(cur == NULL){
		cur = new;
		return new;
    }

#endif



}

