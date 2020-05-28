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
    cur = list; // listeyi gecici bir degiskene atiyoruz
    while(cur != NULL){ // eger current node bos degilse
    	if(!strcmp(word, cur->word)){ // current node'daki kelime ile text icindeki kelimeyi karsilastiriyoruz
    		cur->count++; // eger ayni kelime listede varsa listedeki node'un count degerini attiriyoruz
    		return list;
    	}
    	cur = cur->next;
    }

    struct node *new = malloc(sizeof(struct node)); // yeni node icin yer acilir
	new->word = strdup(word); // word new->word icine kopyalanir
	new->count = 1;
	new->next = list; // liste basina eklenmesi icin yeni node'un nextine listenin kendisi verilir

    if(cur == NULL){ // eger current node bos ise yani kelime liste icinde yoksa
		cur = new;	// current node'a yeni node atanir(next'i listenin kendisi oldugu icin listenin basina eklenmis olur)
		return cur;
    }

#endif

}

