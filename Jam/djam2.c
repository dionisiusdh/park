
#include "jam.h"
#include <stdio.h>


int main(){
    int i,N;
    int awal = 86400;
    int akhir = 0;
    JAM awalan,akhiran;
    scanf("%d",&N);
    for(i=0;i<N;i++){
        JAM J1;
        JAM J2;
        printf("[%d]\n",i+1);
        BacaJAM(&J1);
        BacaJAM(&J2);
        if(JAMToDetik(J1)>JAMToDetik(J2)){
            if(JAMToDetik(J2)<awal){
                awal = JAMToDetik(J2);
                awalan = J2;
            }
            if(JAMToDetik(J1)>akhir){
                akhir = JAMToDetik(J1);
                akhiran = J1;
            }
            printf("%ld\n",Durasi(J2,J1));
        }
        else{
            if(JAMToDetik(J1)<awal){
                awal = JAMToDetik(J1);
                awalan = J1;
            }
            if(JAMToDetik(J2)>akhir){
                akhir = JAMToDetik(J2);
                akhiran = J2;
            }
            printf("%ld\n",Durasi(J1,J2));
        }
    }
    TulisJAM(awalan);
    printf("\n");
    TulisJAM(akhiran);
    printf("\n");
    return 0;
}