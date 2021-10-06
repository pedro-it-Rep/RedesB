/*
 * Cesar Marrote Manzano					RA: 18051755
 * Fabricio Silva Cardoso					RA: 18023481
 * Pedro Ignácio Trevisan					RA: 18016568
 */
//Arrumar recebimento e checksum
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
#include "ipHeader.h"

UDP_PROTOCOL fragmented_Pckt;
IP_Header ip_pckt;

void receive_pckt();
int verify_IP_pckt();
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
    int verify_checksum, verify_IP_checksum;
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

    size = sizeof(client);

    if (sendto(sockfd, (char *)&ip_pckt, sizeof ip_pckt, 0, (struct sockaddr *)&client, sizeof client) < 0)
    {
        printf("Erro ao enviar o pacote");
    }

    while(1)
    {
        recvfrom(sockfd, (char *)&ip_pckt,  sizeof ip_pckt, 0, (struct sockaddr *)&client, &size);
        verify_IP_checksum = verify_IP_pckt();

        // Caso o pacote tenha sido modificado, é necessario dropa-lo, caso contrario salvamos ele em um arquivo
        if(verify_IP_checksum < 0)
        {
            printf("Pacote IP dropado \n");
            j++;
            if(j == n_fragments) {
                close(sockfd);
                break;
            }
        } 
        else 
        {
            fragmented_Pckt = ip_pckt.ipData;
            verify_checksum = verify_pckt();
            if(verify_checksum < 0){
                printf("Pacote UDP dropado \n");
                if(j == n_fragments) {
                    close(sockfd);
                    break;
                }
            } else {

                FILE *fp = fopen("cli_file.txt","a+");
                fprintf(fp, "%s", fragmented_Pckt.udp_Data);
                fclose(fp);
                j++;
                if(j == n_fragments) {
                    close(sockfd);
                    break;
                }

            }
        }
    }
}

/*
 *******************************************************************
 * verify_IP_pckt()                                                *
 * Paramentros: Essa função não utiliza parametros                 *
 * Funcionalidade: Função responsavel por verificar a integridade  *
 * dos pacotes IP recebidos                                        *
 *******************************************************************
 */
int verify_IP_pckt()
{
    int csum_value, len_value;
    csum_value = ip_csum((unsigned short *)&ip_pckt.ipData, sizeof(IP_Header) + sizeof(UDP_PROTOCOL)); 
    len_value = sizeof(ip_pckt);
    printf("IP -> CSUM_VALUE = %d // chksum = %d \n", csum_value, ip_pckt.csum);
    if(len_value == ip_pckt.header_len)
    {
        return 1; 
    } else {
        return -1;
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