#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include "jrb.h"
#include "dllist.h"
#include "jval.h"
#include <string.h>

#define MAX 505
#define MAXLINE 505

#define MAXNESNE 4

#define NEW_nesne() _yeniKilitIcerigi(sizeof(struct nesne), kelimeDondur, huffmanDondur)

#define NEW(objname)    (struct objname *) NEW_##objname()

typedef struct partInfo {
    char kelime[25];
    char huffmankodu[25];
    float i;                            // bagli liste,hashmap vb. liste yapilari ile uyumlu olmasi icin ayirildi
    float j;                            // bagli liste,hashmap vb. liste yapilari ile uyumlu olmasi icin ayirildi
    char* (* virtualFonksiyon)(void *,int);
    char* (* overWriteFonksiyonu)(void *,int);
}Part;

void *_yeniKilitIcerigi(int size, void * fonksiyonTutucuPointer, void * ikinciFonksiyonPointeri) // constructor fonksiyon
{
    Part * i = calloc(1, size);
    // virtual fonksiyon, hisseler.json dan fiyat dondurur, nesne.json dan birimFiyatxAdet dondurur, emirler.json dan islem turu ve adet dondurur.
    i->virtualFonksiyon = fonksiyonTutucuPointer;
    i->overWriteFonksiyonu = ikinciFonksiyonPointeri;
    // icerigiStructYapisi constructor kodlari ...
    return i;
}

// --------------------------------------------------------

typedef struct nesne {            // kalitim yolu ile nesne sinifi
    Part satirIcerigi[MAX];
    float fiyat;
    int adet;
}Nesne;

char *kelimeDondur(Nesne * self,int indis)
{
    return self->satirIcerigi[indis].kelime;
}

char *huffmanDondur(Nesne * self,int indis)
{
    return self->satirIcerigi[indis].huffmankodu;
}


// --------------------------------------------------------

void setSembol(char *a,char *b){  // makro yardimi ile cagirilabilir guvenli string atama fonksiyonu
    strcpy(a, b);
}


void constructKilitNesnesi(struct nesne * kilitNesnesi[MAXNESNE]){
    for(int i = 0;i<MAXNESNE;i++){        /* Guvenli bir sekilde nesnelerin olusturulmasini saglar      */
        kilitNesnesi[i] = NEW(nesne);    /* New makrosu guvenli olan constructor fonskiyonu isare edert*/
    }
}


void welcome(){printf("                        _( )__ _( )__ _( )__ _( )__ _( )__ _( )__ _( )__\n\
                      _|     _|     _|     _|     _|     _|     _|     _|\n\
                     (_   _ (_   _ (_   _ (_   _ (_   _ (_   _ (_   _ (_\n\
                      |__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|\n\
                      |_     |_     |_     |_     |_     |_     |_     |_\n\
                       _) _   _) _   _) _   _) _   _) _   _) _   _) _   _)\n\
                      |__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|\n\
                      _|     _|     _|     _|     _|     _|     _|     _|\n\
                     (_   _ (_   _ (_   _ (_   _ (_   _ (_   _ (_   _ (_\n\
                      |__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|\n\
                      |_     |_     |_     |_     |_     |_     |_     |_\n\
                       _) _   _) _   _) _   _) _   _) _   _) _   _) _mx _)\n\
                      |__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|\n                                             HUFFMAN   \n");}

void beforaSifreleme(){printf("Sifreleme Basladi\n\n");}
void beforaSifrcozme(){printf("Sifrecozme basladi\n\n");}

void clear_input_buff(void)
{
    while ( getchar() != '\n' );
}

int main(int argc, char **argv)
{
            JRB geciciCop;
            Part BUFFFFF[MAX];
            int tmpDonguDegiskeni;
            
            
     


            int mod = 0;
            if(strcmp(argv[1], "-e") == 0)
            {
                mod =1;
                
            }
            else
            {
                mod=0;
            }
            
            
            
        Nesne * kilitNesnesi[1]; //nesne nesneleri pointerları
    
        constructKilitNesnesi(kilitNesnesi); //nesne nesnesi olusturuldu
    
        welcome();
    
    
    	
        printf("argv : %s,%s,%s", argv[1],argv[2],argv[3]);
                IS fieldsInputStr;
                int i;
                int coookUzunKelimeTutucu;
                int counter = 0;
                JRB t;
                t = make_jrb();
                fieldsInputStr = new_inputstruct(".kilit");
                if (fieldsInputStr == NULL) {
                  exit(1);
                }
                while(get_line(fieldsInputStr) >= 0) {
                  Part *parcaAdresi = &kilitNesnesi[0]->satirIcerigi[counter];
                  for (i = 0; i < fieldsInputStr->NF; i++) {
                    if(i==0){
                    coookUzunKelimeTutucu = sscanf(fieldsInputStr->fields[i]," \"%24[^\"]\": ",parcaAdresi->kelime);
                    }
                    else{
                    coookUzunKelimeTutucu = sscanf(fieldsInputStr->fields[i]," \"%24[^\"]\", ",parcaAdresi->huffmankodu);
                    }
                  }
                    if(mod)
                    {
                        jrb_insert_str(t, parcaAdresi->kelime, new_jval_v((void *) parcaAdresi));
                        
                    } else
                    {
                        jrb_insert_str(t, parcaAdresi->huffmankodu, new_jval_v((void *) parcaAdresi));
                        
                    }
                  counter++;
                }
        jettison_inputstruct(fieldsInputStr);
            
            printf("\nKilit Dosyasi Kelime Okuma testi ||||");
            printf("%s-",kilitNesnesi[0]->satirIcerigi->virtualFonksiyon(kilitNesnesi[0],0));
            printf("%s-",kilitNesnesi[0]->satirIcerigi->virtualFonksiyon(kilitNesnesi[0],1));
            printf("%s-",kilitNesnesi[0]->satirIcerigi->virtualFonksiyon(kilitNesnesi[0],2));
            printf("%s-",kilitNesnesi[0]->satirIcerigi->virtualFonksiyon(kilitNesnesi[0],3));
            printf("||||TEST BITTI");
            printf("\nKilit Dosyasi Huffman Okuma testi ||||");
            printf("%s-",kilitNesnesi[0]->satirIcerigi->overWriteFonksiyonu(kilitNesnesi[0],0));
            printf("%s-",kilitNesnesi[0]->satirIcerigi->overWriteFonksiyonu(kilitNesnesi[0],1));
            printf("%s-",kilitNesnesi[0]->satirIcerigi->overWriteFonksiyonu(kilitNesnesi[0],2));
            printf("%s-",kilitNesnesi[0]->satirIcerigi->overWriteFonksiyonu(kilitNesnesi[0],3));
            printf("||||TEST BITTI\n");
		IS girisYapisi;
            Part *p = &kilitNesnesi[0]->satirIcerigi[counter];
         if(mod){
                FILE *m;
    m = fopen("encripted", "w");
    fprintf(m,"");
    fclose(m);
             beforaSifreleme();
             girisYapisi = new_inputstruct(argv[2]);
             if (girisYapisi == NULL) {
               exit(1);
             }
             while(get_line(girisYapisi) >= 0) {
               for (tmpDonguDegiskeni = 0; tmpDonguDegiskeni < girisYapisi->NF; tmpDonguDegiskeni++) {
                   geciciCop = jrb_find_str(t, girisYapisi->fields[tmpDonguDegiskeni]);
                   p = (Part *) geciciCop->val.v;
                   printf("%1s ",p->huffmankodu);
                   
                     FILE *ffff;
    		     ffff = fopen("encripted", "a");
   		     fprintf(ffff," ");
                    fprintf(ffff, p->huffmankodu);
                    fclose(ffff);

               }
             }
             jettison_inputstruct(girisYapisi);
         }

         else if(mod == 0){
         FILE *m;
              m = fopen("decripted", "w");
    fprintf(m,"");
    fclose(m);

             beforaSifrcozme();
             IS isc;
             isc = new_inputstruct(argv[2]);
             if (isc == NULL) {
               exit(1);
             }
             while(get_line(isc) >= 0) {
               for (tmpDonguDegiskeni = 0; tmpDonguDegiskeni < isc->NF; tmpDonguDegiskeni++) {
                   geciciCop = jrb_find_str(t, isc->fields[tmpDonguDegiskeni]);
                   p = (Part *) geciciCop->val.v;
                   printf("%-1s ", p->kelime);
                   FILE *ffff;
    		     ffff = fopen("decripted", "a");
    		         fprintf(ffff," ");
                    fprintf(ffff, p->kelime);
                    fclose(ffff);
               }
             }
             jettison_inputstruct(isc);
         }
         else if(mod == 3){printf("??????\n");clear_input_buff();}
         else if(mod == 4){printf("??????\n");clear_input_buff();}
         else if(mod == 5){printf("??????\n");clear_input_buff();}
         else if(mod == 6){printf("??????\n");clear_input_buff();}
         else if(mod == 7){printf("??????\n");clear_input_buff();}
         else if(mod == 8){printf("??????\n");clear_input_buff();}
         else{
             clear_input_buff();
         }
    
    return 0;
  }
