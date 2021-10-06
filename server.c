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
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "ipHeader.h"

UDP_PROTOCOL initial_Pckt;
UDP_PROTOCOL fragmented_Pckt;
IP_Header ip_pckt;

char aux[2000];

void fragment_file(FILE *arq);
void send_package(int PROTO);

int main()
{
    FILE *arq;
    arq = fopen("teste.txt", "r");

    fragment_file(arq);
    create_packetIP(UDP, &ip_pckt);
    send_package(UDP);

    return 0;
}

/*
 *******************************************************************
 * fragment_file(int MAX_DATA, UDP_PROTOCOL pckt)                  *
 * Paramentros:                                                    *
 * MAX_DATA = tamanho máximo que o campo data pode receber         *
 * Arq = Caminho para o arquivo que deve ser lido                  *
 * Funcionalidade: Função responsavel por fragmentar o arquivo     *
 * lido em vários pacotes                                          *
 *******************************************************************
 */
void fragment_file(FILE *arq)
{
    int j = 0, i = 0;
    char c;
    char backup[DATA_SIZE];
    //Enquanto não for o final do arquivo
    while((c = fgetc(arq)) != EOF)
    {     
        initial_Pckt.udp_Data[j] = c;

        if(j == DATA_SIZE) //Caso seja o limite, salva o fragmento
        {
            strncpy(&aux[n_fragments * DATA_SIZE], initial_Pckt.udp_Data, DATA_SIZE); //Copia para a variavel
            j = 0;
            n_fragments++;
        } else {
            j++;
        }
    }

    if(j != 0) //Caso tenha alguma palavra que não tenha sido salva
    {
        for(i = 0; i < j; i++){
            backup[i] = initial_Pckt.udp_Data[i];
        }
        strncpy(&aux[n_fragments * DATA_SIZE], backup, DATA_SIZE); //Copia para a variavel
    }
}

/*
 *******************************************************************
 * send_package(int PROTO)                                         *
 * Paramentros:                                                    *
 * PROTO = define qual protocolo será utilizado                    *
 * Funcionalidade: Função responsavel por enviar os pacotes        *
 * ao cliente                                                      *
 *******************************************************************
 */
void send_package(int PROTO)
{
    int sockfd, size, j = 0;
    struct sockaddr_in server, client;
      
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Criação do pacote UDP
    int serverLength = sizeof(server);
    memset(&server, 0, serverLength);

    // Filling server information
    server.sin_family = AF_INET; // IPv4
    server.sin_addr.s_addr = ip_pckt.saddr; // Localhost -> Pode ser alterado para um IP não proprietario (Ex: 8.8.8.8)
    server.sin_port = htons(1234); //Can be changed → src_port

    // Bind the socket with the server address
    if ( bind(sockfd, (struct sockaddr *)&server, serverLength) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    fragmented_Pckt.src_port = 1234;
    fragmented_Pckt.dest_port = 1234;

    size = sizeof(client);
    //Espera uma solicitação do cliente para poder enviar os pacotes
    recvfrom(sockfd, (char *)&ip_pckt,  sizeof ip_pckt, 0, (struct sockaddr *)&server, &size);

    switch(PROTO){
        case 0: //TCP

            //listen("?"); //Necessario completar os campos
            //send("?", "?", "?"); //Necessario completar os campos
            break;

        case 1: //UDP

            while(j <= n_fragments){

                //Copia os dados para os respectivos campos, calcula o checksum e o len
                strncpy(fragmented_Pckt.udp_Data, &aux[j * DATA_SIZE], DATA_SIZE);
                fragmented_Pckt.chksum = csum(fragmented_Pckt.udp_Data, sizeof(UDP_PROTOCOL));
                printf("chksum = %d \n", fragmented_Pckt.chksum);
                fragmented_Pckt.len = sizeof(fragmented_Pckt);
                ip_pckt.id = j;
                ip_pckt.ipData = fragmented_Pckt;
                ip_pckt.csum = ip_csum((unsigned short *)&ip_pckt.ipData, sizeof(IP_Header) + sizeof(UDP_PROTOCOL)); 
                ip_pckt.header_len = sizeof(ip_pckt);
                if (sendto(sockfd, (char *)&ip_pckt, sizeof ip_pckt, 0, (struct sockaddr *)&server, sizeof server) < 0){
                    printf("Erro ao enviar o pacote");
                }
                j++;
            }
            close(sockfd);
            break;

        default:
            printf("Erro protocolo não indicado \n");
    }
}