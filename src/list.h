#ifndef _LIST_H_
#define _LIST_H_

#ifdef WITH_UTHASH
#include "uthash.h"
#endif

struct node {
    char *word;
    int count;
#ifdef WITH_UTHASH
    /* Hash ile derlenirken ihtiyac duyulan bir
     * degisken */
    UT_hash_handle hh;
#else
    /* Bagli listeyle derlenirken ihtiyac duyulan
     * sonraki gosterici. */
    struct node *next;
#endif
};

struct node* add_word(struct node *list, char *word);

#endif
