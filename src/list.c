#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct node* add_word(struct node *list, char *word) {
    struct node *cur = NULL;
#ifdef WITH_UTHASH
    /* TODO: Hash kodu */
	struct node *new = NULL;

	HASH_FIND_STR(list, word, new); // Hash tablosunda word u arar.

	if (new != NULL) {
		new->count++;
	}else {
		//yeni eleman eklenicek kısım
		new=(struct node*) malloc(sizeof(struct node));
		new->word = strdup(word);
		new->count = 1;
		HASH_ADD_KEYPTR(hh, list, new->word, strlen(new->word), new);
	}

	return list;


#else
    /* TODO: Bagli liste kodu */
    cur = list; // listeyi gecici bir degiskene atiyoruz
    while(cur != NULL){ // eger current node bos degilse
    	if(!strcmp(word, cur->word)){ // current node'daki kelime ile text icindeki kelimeyi karsilastiriyoruz
    		cur->count++; // eger ayni kelime listede varsa listedeki node'un count degerini artiriyoruz
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

    free(new->word);
    free(new);

#endif

    return cur;

}
