/* File: mesinkata.c */
/* Realisasi Mesin Kata: Model Akuisisi Versi I */

#include "../boolean.h"
#include <stdio.h>
#include "mesinkata.h"

/* State Mesin Kata */
boolean EndKata;
Kata CKata;

void IgnoreBlank(){
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
  while (CC == BLANK) {
    ADV();
  }
}

void STARTKATA(){
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
  START();
  IgnoreBlank();
  if (CC == MARK) {
    EndKata = true;
  } else /* CC != MARK */ {
    EndKata = false;
    SalinKata();
  }
}

void ADVKATA(){
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
  IgnoreBlank();
  if (CC == MARK) {
    EndKata = true;
  } else /* CC != MARK */ {
    SalinKata();
  }
}

void SalinKata(){
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
  int i; /* definisi */
  /* Algoritma*/
  i = 0; /* inisialisasi */
  while ((CC != MARK) && (CC != BLANK)) {
    CKata.TabKata[i] = CC;
    ADV();
    i++;
  } /* CC = MARK or CC = BLANK */
  CKata.Length = i;
}

boolean IsEQKata(Kata K1, Kata K2)
/* Menghasilkan apakah kata K1 dan K2 merupakan kata yang sama */
{ //KAMUS
  int i = 0;
  boolean sama = true;
  //ALGORITMA
  if (K1.Length == K2.Length){
    while (sama && i<K1.Length){
      if (K1.TabKata[i] != K2.TabKata[i]){
        sama = false;
      }
      i+= 1;
    }
    return sama;
  }
  else{
    return false;
  }
}

int KataToInteger (Kata K)
/* Mengubah Kata ke dalam bentuk integer */
{
  int i;
  int hasil = 0;
  for(i=0;i<K.Length;i++){
      if(K.TabKata[i] == '0'){
        hasil = hasil*10+0;
      }
      else if(K.TabKata[i] == '1'){
        hasil = hasil*10+1;
      }
      else if(K.TabKata[i] == '2'){
        hasil = hasil*10+2;
      }
      else if(K.TabKata[i] == '3'){
        hasil = hasil*10+3;
      }
      else if(K.TabKata[i] == '4'){
        hasil = hasil*10+4;
      }
      else if(K.TabKata[i] == '5'){
        hasil = hasil*10+5;
      }
      else if(K.TabKata[i] == '6'){
        hasil = hasil*10+6;
      }
      else if(K.TabKata[i] == '7'){
        hasil = hasil*10+7;
      }
      else if(K.TabKata[i] == '8'){
        hasil = hasil*10+8;
      }
      else if(K.TabKata[i] == '9'){
        hasil = hasil*10+9;
      }
      else{
        hasil = hasil*10;
      }
  }
  return hasil;
}

int KataToIntegerB(Kata K){
  //KAMUS
  int hasil;
  //ALGORITMA
  hasil = 0;
  while ((CC != MARK) && (CC != BLANK)){
    hasil= 10;
    hasil += CC -'0';
    ADV();    
  }
  return hasil;
}

void PrintKata (Kata K) {
  int i = 0;
  while (i<K.Length){
    printf("%c",K.TabKata[i]);
    i++;
  }
}

void Bagi2Kata (Kata Kin, Kata *Kout1, Kata *Kout2){
  //KAMUS
  int i=0;
  //ALGORITMA
  SalinKata();
  (*Kout1) = CKata;
  IgnoreBlank();
  while (CC != MARK){
    (*Kout2).TabKata[i] = CC;
    ADV();
    i++; 
  }
  (*Kout2).Length = i;
}

Kata StringToKata (char *string, int lengthString){
  Kata K;
  int i = 0;
  while(i<lengthString){
    K.TabKata[i] = string[i];
    K.Length++;
    i++;
  }
  return K;
}

Kata concatNama() {
  Kata K;
  STARTKATA();
  int j=0; int i;
  while (!EndKata) {
    for (i=0; i<CKata.Length; i++) {
      K.TabKata[i+j] = CKata.TabKata[i];
    }
    K.TabKata[i+j] = ' ';
    j+=CKata.Length+1;
    ADVKATA();
  }
  K.Length = j;
  return K;
}