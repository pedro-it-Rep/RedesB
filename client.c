/*
 * Cesar Marrote Manzano					RA: 18051755
 * Fabricio Silva Cardoso					RA: 18023481
 * Pedro Ignácio Trevisan					RA: 18016568
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "headerUDP.h"

UDP_PROTOCOL fragmented_Pckt;

void receive_pckt();
int verify_pckt();

int main()
{
    receive_pckt();

    return 0;
}

/*
 *******************************************************************
 * receive_pckt()                                                  *
 * Paramentros: Essa função não utiliza parametros                 *
 * Funcionalidade: Função responsavel por receber os pacotes       *
 * enviados pelo servidor                                          *
 *******************************************************************
 */
void receive_pckt()
{

    int sockfd, size, j;
    int verify_checksum;
    struct sockaddr_in client;
    struct hostent *hp, *gethostbyname();
      
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Criação do pacote UDP
    int clientLength = sizeof(client);
    memset(&client, 0, clientLength);

    // Filling server information
    client.sin_addr.s_addr = INADDR_ANY;
	client.sin_family = AF_INET;
	client.sin_port = htons(1234);

    if (sendto(sockfd, (char *)&fragmented_Pckt, sizeof fragmented_Pckt, 0, (struct sockaddr *)&client, sizeof client) < 0)
    {
        printf("Erro ao enviar o pacote");
    }

    while(1)
    {
        recvfrom(sockfd, (char *)&fragmented_Pckt,  sizeof fragmented_Pckt, 0, (struct sockaddr *)&client, &size); // ???
        verify_checksum = verify_pckt();

        // Caso o pacote tenha sido modificado, é necessario dropa-lo, caso contrario salvamos ele em um arquivo
        if(verify_checksum < 0)
        {
            printf("Pacote dropado \n");
            j++;
            if(j == n_fragments) break;
        } 
        else 
        {
            FILE *fp = fopen("cli_file.txt","a+");
            fprintf(fp, "%s", fragmented_Pckt.udp_Data);
            fclose(fp);
            j++;
            if(j == n_fragments) break;
        }
    }
}

/*
 *******************************************************************
 * verify_pckt()                                                   *
 * Paramentros: Essa função não utiliza parametros                 *
 * Funcionalidade: Função responsavel por verificar a integridade  *
 * dos pacotes recebidos                                           *
 *******************************************************************
 */
int verify_pckt()
{
    int csum_value, len_value;
    csum_value = csum(fragmented_Pckt.udp_Data, sizeof(UDP_PROTOCOL));
    len_value = sizeof(fragmented_Pckt);
    printf("CSUM_VALUE = %d // chksum = %d \n", csum_value, fragmented_Pckt.chksum);
    if(len_value == fragmented_Pckt.len)
    {
        return 1; 
    } else {
        return -1;
    }
}