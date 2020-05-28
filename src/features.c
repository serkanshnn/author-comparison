#include "features.h"
#include "list.h"

#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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


	
	
	struct features *dosya1=s1; //gelen dosyayı geçiçi bir değişkene atıyoruz.
	struct features *dosya2=s2;

	//bu kısımda fai fbi değerleri için bir dizi oluşturup bu diziye bu değerleri aktarıyoruz.
	double fa[5]={dosya1->avg_word_length,dosya1->avg_word_per_sentence,dosya1->complexity,dosya1->hapax,dosya1->ttr};
	double fb[5]={dosya2->avg_word_length,dosya2->avg_word_per_sentence,dosya2->complexity,dosya2->hapax,dosya2->ttr};


	double sonuc=0;
	//w değeri için dizi oluşturup değerleri içine aktarıyoruz.
	double w[5]={11,33,50,0.4,4};

	//gerekli olan hesaplama for döngüsü içinde hesaplanır.
	int i;
	for(i=0;i<5;i++){

		sonuc+=w[i]*fabs(fa[i]-fb[i]);

	}

	return sonuc;//bulunan sonuç değeri geri döndürülür.


}

/* TODO */
void compute_features(char *text, struct features *feat) {
    /* TODO: Ortak kod */
	char *sentence, *word, *sptr , *sentence_copy, *word_copy, *rest;
	struct node* list = NULL;
	sentence = strtok_r(text , "?!.", &sptr);
	while(sentence){
		sentence_copy = strdup(sentence);
		word = strtok_r(sentence, " ,:;?!.\n\t", &rest);
		while(word){
			word_copy = strdup(word);
			cleanup(word_copy);
			if(strcmp(word_copy,"")){
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
					list = add_word(list, word_copy);
				#endif
			}

			free(word_copy);
			word = strtok_r(NULL , " ,:;?!.\n\t", &rest);
		}

		free(sentence_copy);
		sentence = strtok_r(NULL , "?!.", &sptr);
	}
	/* TODO: Ortak kod. feat yapisinin uyelerini artik doldurabilirsiniz. */
	free(list);

}


