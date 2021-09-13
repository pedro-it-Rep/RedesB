typedef iphdr {
    uint8_t version : 4; /* Versão utilizada (Poder ser IPv6) */
    uint8_t header_len; /* Tamanho do cabeçalho */
    uint8_t tos; /* Type of Service */
    uint16_t pckt_len; /* Tamanho do pacote */
    uint16_t id; /* Id usado na remontagem do pacote */
    uint16_t flags; /* Flags */
    uint16_t frag_offset; /* Indica qual fragmento é */
    uint8_t ttl; /* Time to live */
    uint8_t proto; /* Protocolo utilizado */
    uint16_t csum; /* Checkusum */
    uint32_t saddr; /* Source Addrs */
    uint32_t daddr; /* Destiny Addrs */
} IP_Header;

