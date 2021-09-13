#include "headerUDP.h"
#include <stdio.h>
#include <stdlib.h>

/*
 *******************************************************************
 * csum(unsigned short *buf, int nwords)                           *
 * Paramentros:                                                    *
 *  buf = Contem os dados necessarios para o calculo do checksum   *
 * nwords = contem o tamanho da struct utilizada                   *
 * Funcionalidade: Função responsavel por receber os pacotes       *
 * enviados pelo servidor                                          *
 *******************************************************************
 */
unsigned short csum(unsigned short *buf, int nwords)
{
    uint16_t *pak = buf;
    uint16_t cksum=0;

    for(int i=0;i<nwords/sizeof(uint16_t);i++){
        cksum+=(uint16_t)*pak;
        pak++;
    }
    cksum=~cksum;
    return cksum;
}
