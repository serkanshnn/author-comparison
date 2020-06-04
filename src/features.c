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
	char *sentence, *word; // kelime ve cumlelerin tutulacagi degiskenler
	char *sptr, *rest, *alt_parca, *rest2; // kelime ve cumleleri bolerken kullanilacak degiskenler
	char *sentence_copy, *word_copy; // kelime ve cumleleri tutmak icin olusturulan copy degiskenleri

	// Ozellikleri hesaplamak icin kullanılacak degiskenler
	int length = 0;
	int word_count = 0;
	int sentence_count = 0;
	int unique_word_count = 0;
	int different_word_count = 0;
	int alt_parca_count=0;

	// kelimelerin tutulacagi liste degiskeni
	struct node* list = NULL;

	sentence = strtok_r(text , "?!.", &sptr); // metni cumlelere bolen kod parcasi
	while(sentence){
		sentence_copy = strdup(sentence); // cumleleri copy degiskenine atar
		if(strcmp(sentence_copy, "\n")) // eger cumle bosluk degilse
			sentence_count++;
		rest2 = sentence_copy;
		while((alt_parca=strtok_r(rest2, ",:;", &rest2))){ // alt cumleleri bolen kod parcasi
			if(strcmp(alt_parca, "\n")) // eger alt cumle bosluk degilse
				alt_parca_count++;
		}
		word = strtok_r(sentence, " ,:;?!.\n\t", &rest); // cumleleri kelimelere bolen kod parcasi
		while(word){
			word_copy = strdup(word); // kelimeleri copy degiskenine atar
			cleanup(word_copy); // gelen kelimeyi tum noktalama isaretleri ve buyuk harflerden temizler
			if(strcmp(word_copy,"")){ // eger kelime bos degilse
				word_count++;
				list = add_word(list, word_copy); // listeye kelimeyi ekler
				length += strlen(word_copy);
			}

			free(word_copy); // artik kullanilmayacak degisken silinir.
			word = strtok_r(NULL , " ,:;?!.\n\t", &rest);
		}

		free(sentence_copy); // artik kullanilmayacak degisken silinir.
		sentence = strtok_r(NULL , "?!.", &sptr);
	}
	// Eger liste hash ise
	#ifdef WITH_UTHASH
	/* TODO: Hash kullanarak kelime listesini
	 * gezip ilgili sayaclari hesaplayin. Gezdikce
	 * dugumleri HASH_DEL() ile temizleyip, mevcut
	 * dugumun char* uyesini ve dugumun kendisini
	 * free() ile iade etmelisiniz.*/

		struct node *s, *tmp;

		HASH_ITER (hh, list, s, tmp) { // Tum listeyi gezer
			different_word_count++;
			if(list->count == 1)
				unique_word_count++;
			HASH_DEL(list, s); // Baglari free eder

		}

	// Eger liste linked list ise
	#else
	/* TODO: Bagli liste kullanarak kelime listesini
	 * gezin. Gezdikce dugumlerin char* uyesini ve
	 * kendisini free() ile iade etmelisiniz. */
		while(list != NULL){ // Tum linked listi gezer
				different_word_count++;
				if(list->count == 1)
					unique_word_count++;
				list = list->next;
			}
	#endif

	/* TODO: Ortak kod. feat yapisinin uyelerini artik doldurabilirsiniz. */
	feat->avg_word_per_sentence = ((double) word_count / (double) sentence_count);
	feat->hapax = ((double) unique_word_count / (double) word_count);
	feat->avg_word_length = ((double) length / (double) word_count);
	feat->ttr = ((double) different_word_count / (double) word_count);
	feat->complexity = ((double) alt_parca_count / (double) sentence_count);

	free(list); // Listeyi hafizadan siler


}


