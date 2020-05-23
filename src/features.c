#include "features.h"
#include "list.h"

#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void cleanup(char *s) {
    /* s stringini kucuk harflere cevirip basindan ve
     * sonundan noktalama ve bazi diger karakterleri kaldirir. */
    char *cset = "!\"',;:.-?)([]<>*#\n\t\r";
    char *sp, *start, *ep, *end;
    int length, i;


    sp = start = s;
    ep = end = sp + strlen(s) - 1;

    /* basini ve sonunu temizle */
    while (sp <= end && strchr(cset, *sp))
        sp++;
    while (ep > start && strchr(cset, *ep))
        ep--;

    if ((start != sp) || (ep != end)) {
        length = (sp > ep) ? 0 : ((ep - sp) + 1);
        if (length > 0)
            memmove(start, sp, length);
        start[length] = '\0';
    }

    /* kucuk harfe cevir */
    for (i = 0; start[i] != '\0'; ++i) {
        start[i] = tolower(start[i]);
    }
}

/* TODO: iki imza arasindaki benzerligi hesaplayan fonksiyon. */
double sim_score(struct features *s1, struct features *s2) {
}

/* TODO */
void compute_features(char *text, struct features *feat) {
    /* TODO: Ortak kod */

#ifdef WITH_UTHASH
    /* TODO: Hash kullanarak kelime listesini
     * gezip ilgili sayaclari hesaplayin. Gezdikce
     * dugumleri HASH_DEL() ile temizleyip, mevcut
     * dugumun char* uyesini ve dugumun kendisini
     * free() ile iade etmelisiniz.*/
#else
    /* TODO: Bagli liste kullanarak kelime listesini
     * gezin. Gezdikce dugumlerin char* uyesini ve
     * kendisini free() ile iade etmelisiniz. */
#endif
    
    /* TODO: Ortak kod. feat yapisinin uyelerini artik doldurabilirsiniz. */
}


