 > :construction: Este é um projeto de Redes de Computadores, feito na linguagem C. É um projeto que vai ser composto por mais funcionalidades ao longo desse sementres, onde ao decorrer desse semestre iremos atualizando o README. :construction:

# :stop_sign: Funcionalidades

- Lê um arquivo de entrada.
- Cria pacotes UDP.
- Encapsula o pacote UDP em um pacote IP
- Envia para outro programa, onde nós chamamos de cliente.
- Faz a análise, verifica a integridade do pacote atraves do checksum duas vezes, uma para o pacote IP e outra para o pacote UDP.
- Caso o checksum tenha se mantido, remonta o arquivo, caso contrário, dropa o pacote.

# :warning: TODO

Alterações no codigo que podem ser feita para melhorar seu entendimento ou para adicionar novas funcionalidades

- Modularizar melhor o código;

# :vertical_traffic_light: Próximas Funcionalidades

- Nothing to see here

# :scroll: Instruções de Uso:

### :desktop_computer: Windows

- Use o Visual Studio Code (recomendação).
- Baixe o WSL na Microsoft Store.
- Baixe as extensões:
    * C/C++
    * C/C++ Compiler Run
    * Remote - WS

### :desktop_computer: Linux

- Abra dois terminais para o cliente e servidor.

# :scroll: Abrir o projeto:

Para pegar o projeto é preciso seguir essas etapas.

1.Baixe o código fonte do projeto usando o comando:

        
    git clone https://github.com/pedro-it-Rep/RedesB.git
        
2.Descompacte o arquivo.

3.Vá para o repositório do projeto.

        
    cd RedesB

# :keyboard: Run Code:

### :desktop_computer: Windows

- Inicialize o projeto RedesB com o WSL.
- Crie dois terminais WSL, um para o cliente e outro para o servidor.
- Use o comanado para compilar:
    * o cliente (em um terminal)

    ```
    gcc client.c -o cli
    ```

    * e o servidor (no outro terminal)
    ```
    gcc server.c -o server
    ```

- Para rodar só digitar:
    * em um dos terminais
    ```
    ./serv
    ```

    * no outro terminal
    ```
    ./cli
    ```
- E veja  a mágica acontecer

### :desktop_computer: Linux

- Abra dois terminais
- Use o comanado para compilar:
- 
    * o cliente (em um terminal)
    ```
    gcc client.c -o cli
    ```
    * e o servidor (no outro terminal)
    ```
    gcc server.c -o server
    ```
- Para rodar só digitar:
    ```
    ./serv
    ```
    * em um terminal
    ```
    ./cli
    ```
- E veja  a mágica acontecer

# Contribuidores
| Name | Git account |
|------|-------------|
| Pedro Ignácio Trevisan| [https://github.com/pedro-it-Rep] | 
| Fabricio Silva Cardoso| [https://github.com/Fabricio-Silva-Cardoso1]|
| Cesar Marrote Manzano| [https://github.com/cesarmmanzano]|
