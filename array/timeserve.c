#include <stdio.h>
#include "timeserve.h"

void MakeTimeEmpty(TabTime *T)
//Membuat sebuah TabTime baru yang Neff-nya 0
{   //KAMUS
    //ALGORITMA
    NeffTime(*T) = 0;
}
boolean IsEmptyTime(TabTime T)
//Mengecek apakah TabTime kosong / Neff-nya 0 atau tidak
{   //KAMUS
    //ALGORITMA
    return (Neff(T) == 0);
}
void AddTime(TabTime *T, ElArrayTime X)
//Menambah sebuah elemen ElArrayTime ke dalam array yang diurutkan berdasarkan time Elemen dari terkecil ke terbesar
{   //KAMUS
    int i;
    ElArrayTime temp1,temp2;
    //ALGORITMA
    if (NeffTime(*T) == 0){
        ElmtTime(*T,0) = X;
        NeffTime(*T) += 1;
    }
    else{
        temp1 = X;
        for (i=0; i< NeffTime(*T); i++){
            if (Time(ElmtTime(*T,i)) > time(temp1)){
                temp2 = ElmtTime(*T,i);
                ElmtTime(*T,i) = temp1;
                temp1 = temp2;
            }
        }
        ElmtTime(*T,NeffTime(*T)) = temp2;
        NeffTime(*T) += 1;
    }
} 
void DellTime(TabTime *T)
//Menghapus elemen pertama dari ElArrayTime
{   //KAMUS
    int i;
    //ALGORITMA
    for (i = 1; i<NeffTime(*T); i++){
        ElmtTime(*T,i-1) = ElmtTime(*T,i);
    }
    NeffTime(*T) -= 1;
}