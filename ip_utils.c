#include "ipHeader.h"
#include <stdio.h>
#include <stdlib.h>

IP_Header ip_pckt;

void create_packet(){

    ip_pckt->id = 0;
    ip_pckt->flags = 0;
    ip_pckt->ttl = 0;
    ip_pckt->header_len = sizeof(ip_pckt);

}

void getIP(){

    ip_pckt.saddr = "192.168.XX.XX"; //Inicio de um IP qualquer
    ip_pckt.daddr = "8.8.8.8"; //Endereço não endereçado (Google)

}