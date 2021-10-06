#define SRC_PORT    16
#define DEST_PORT   16
#define LEN         16
#define CHKSUM_UDP  16
#define DATA_SIZE   32

#define TCP         0
#define UDP         1

unsigned short csum(unsigned short *buf, int nwords);

typedef struct udp_Header
{
    unsigned int src_port; // Nossa porta
    unsigned int dest_port; // Porta de destino
    unsigned long int len; //Tamanho total do cabeçalho
    unsigned int chksum; // Verifica se ouve algum problema durante o envio
    char udp_Data[DATA_SIZE]; // Buffer
} UDP_PROTOCOL;

/*
*************************************************************************
 * csum(unsigned short *buf, int nwords)                                *
 * Paramentros:                                                         *
 * @params buf = Contem os dados necessarios para o calculo do checksum *
 * nwords = contem o tamanho da struct utilizada                        *
 * @params Funcionalidade: Função responsavel por receber os pacotes    *
 * enviados pelo servidor                                               *
 ************************************************************************
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