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
    struct node* new = malloc(sizeof(struct node));
	new->word = malloc(sizeof(char) * 100);

	strcpy(new->word, word);

	new->count = 1;
	new->next = list;

	if(cur == NULL){
		cur = new;
		return new;
	}

	struct node *head = cur;

	struct node *prev;

	while(head != NULL){
		if(head->word == new->word){
			head->count++;
			new = NULL;
			return new;
		} else{
			prev = head;
			head = head->next;
		}
	}

	if(head == NULL){
		prev->next = new;
		return new;
	}

#endif



}

