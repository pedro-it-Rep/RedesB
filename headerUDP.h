#define SRC_PORT    16
#define DEST_PORT   16
#define LEN         16
#define CHKSUM_UDP  16
#define DATA_SIZE   32

#define TCP         0
#define UDP         1

typedef struct udp_Header
{
    unsigned int src_port; // Nossa porta
    unsigned int dest_port; // Porta de destino
    unsigned long int len; //Tamanho total do cabeçalho
    unsigned int chksum; // Verifica se ouve algum problema durante o envio
    char udp_Data[DATA_SIZE]; // Buffer
} UDP_PROTOCOL;

int n_fragments = 0;

unsigned short csum(unsigned short *buf, int nwords);
