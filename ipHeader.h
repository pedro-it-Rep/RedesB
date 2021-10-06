/*
 * Cesar Marrote Manzano					RA: 18051755
 * Fabricio Silva Cardoso					RA: 18023481
 * Pedro Ignácio Trevisan					RA: 18016568
 */

#include "udpHeader.h"

typedef struct iphdr {
    uint8_t version : 4; /* Versão utilizada (Poder ser IPv6) */
    uint8_t header_len; /* Tamanho do cabeçalho */
    uint8_t tos; /* Type of Service */
    uint16_t pckt_len; /* Tamanho do pacote */
    uint16_t id; /* Id usado na remontagem do pacote */
    uint16_t flags; /* Flags */
    uint16_t frag_offset; /* Indica qual fragmento é */
    uint8_t ttl; /* Time to live */
    uint8_t proto; /* Protocolo utilizado */
    unsigned short int csum; /* Checkusum */
    uint32_t saddr; /* Source Addrs */
    uint32_t daddr; /* Destiny Addrs */

#ifdef UDP
    UDP_PROTOCOL ipData; //Pacote da camada de transporte
#endif

#ifdef TCP
    //tcp_Header ipData; //Pacote da camada de transporte
#endif

} IP_Header;

int n_fragments = 0;

unsigned short csum(unsigned short *buf, int nwords);

// Funções para o IP
void getIP();
void create_packetIP(int isUDP, IP_Header *ip_pckt);


/*
*************************************************************************
 * csum(unsigned short *buf, int nwords)                                *
 * Paramentros:                                                         *
 * @params buf = Contem os dados necessarios para o calculo do checksum *
 * nwords = contem o tamanho da struct utilizada                        *
 * @params Funcionalidade: Função responsavel por verificar a           *
 integridade dos pacotes enviados pelo servidor                         *
 ************************************************************************
 */
unsigned short ip_csum(unsigned short *buf, int nwords)
{

    unsigned long sum;

    for(sum=0; nwords>0; nwords--)
        sum += *buf++;

    sum = (sum >> 16) + (sum &0xffff);

    sum += (sum >> 16);

    return (unsigned short)(~sum);

}

/*
*************************************************************************
 * create_packetIP(int isUDP, IP_Header *ip_pckt)                       *
 * Paramentros:                                                         *
 * @params isUDP = Indica se deve utilizar o protocolo UDP              *
 * ip_pckt = struct com os campos do pacote IP                          *
 * @params Funcionalidade: preenche os principais campos do pacote IP   *
 ************************************************************************
 */
void create_packetIP(int isUDP, IP_Header *ip_pckt){

    printf("Creating IP Packet \n");
    ip_pckt->flags = 0;
    ip_pckt->ttl = 0;
    if(!isUDP){
        ip_pckt->proto = TCP;
    } else{
        ip_pckt->proto = UDP;
    }

    ip_pckt->saddr = INADDR_ANY;
    ip_pckt->daddr = INADDR_ANY;
}
