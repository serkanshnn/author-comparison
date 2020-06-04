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
	
	struct features *file1 = s1; //gelen dosyayi gecici bir degişkene atiyoruz.
	struct features *file2 = s2;

	//bu kisimda fai fbi degerleri icin bir dizi olusturup bu diziye bu degerleri aktariyoruz.
	double fa[5] = {file1->avg_word_length, file1->ttr, file1->hapax, file1->avg_word_per_sentence, file1->complexity};
	double fb[5] = {file2->avg_word_length, file2->ttr, file2->hapax, file2->avg_word_per_sentence, file2->complexity};
	double result = 0;
	
	//w degeri icin dizi olusturup degerleri icine aktariyoruz.
	double w[5]={11,33,50,0.4,4};


	//gerekli olan hesaplama for dongusu icinde hesaplanir.
	int i;
	for(i = 0; i < 5; i++){
		result += w[i] * fabs(fa[i] - fb[i]);
	}

	return result; //bulunan sonuc degeri geri dondurulur.
}

/* TODO */
void compute_features(char *text, struct features *feat) {
    /* TODO: Ortak kod */
	char *sentence, *word, *sptr , *sentence_copy, *word_copy, *rest;
	char *alt_parca,*rest3;
	int alt_parca_count=0;
	int length = 0;
	int word_count = 0, sentence_count = 0;
	struct node* list = NULL;
	sentence = strtok_r(text , "?!.", &sptr);
	while(sentence){
		sentence_copy = strdup(sentence);
		if(strcmp(sentence_copy, "\n"))
			sentence_count++;
		rest3=sentence_copy;
				while((alt_parca=strtok_r(rest3, ",:;", &rest3)))
				{
				if(strcmp(alt_parca, "\n"))
					alt_parca_count++;
				}
		word = strtok_r(sentence, " ,:;?!.\n\t", &rest);
		while(word){
			word_copy = strdup(word);
			cleanup(word_copy);
			if(strcmp(word_copy,"")){
				word_count++;
				#ifdef WITH_UTHASH
					/* TODO: Hash kullanarak kelime listesini
					 * gezip ilgili sayaclari hesaplayin. Gezdikce
					 * dugumleri HASH_DEL() ile temizleyip, mevcut
					 * dugumun char* uyesini ve dugumun kendisini
					 * free() ile iade etmelisiniz.*/

					list = add_word(list, word_copy);
				#else
					/* TODO: Bagli liste kullanarak kelime listesini
					 * gezin. Gezdikce dugumlerin char* uyesini ve
					 * kendisini free() ile iade etmelisiniz. */
					list = add_word(list, word_copy);
				#endif
				length += strlen(word_copy);
			}

			free(word_copy);
			word = strtok_r(NULL , " ,:;?!.\n\t", &rest);
		}

		free(sentence_copy);
		sentence = strtok_r(NULL , "?!.", &sptr);
	}
	/* TODO: Ortak kod. feat yapisinin uyelerini artik doldurabilirsiniz. */
	//printf("word: %d sentence: %d\n", word_count, sentence_count);
	feat->avg_word_per_sentence = ((double) word_count / (double) sentence_count);
	int a = 0;
	int different_word_count = 0;

#ifdef WITH_UTHASH
	while(list != NULL){
			different_word_count++;
			if(list->count == 1)
				a++;
			//printf("%s -> %d\n", list->word, list->count);
			list = list->hh.next;
		}
#else
	while(list != NULL){
			different_word_count++;
			if(list->count == 1)
				a++;
			//printf("%s -> %d\n", list->word, list->count);
			list = list->next;
		}
#endif


	//printf("word: %d a: %d\n", word_count, a);
	//printf("word: %d length: %d\n", word_count, length);
	//printf("word: %d different: %d\n", word_count, different_word_count);
	feat->hapax = ((double) a / (double) word_count);
	feat->avg_word_length = ((double) length / (double) word_count);
	feat->ttr = ((double) different_word_count / (double) word_count);
	feat->complexity = ((double) alt_parca_count / (double) sentence_count);

	free(list);


}


