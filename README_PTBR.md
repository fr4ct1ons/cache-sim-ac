# cache-sim-ac
Um simulador de hierarquia de memória em um processador multi-core.  
Autor: Gabriel Lucena (fr4ct1ons, lucena-fr4ct1ons)

## Instalação
Assumindo que você tem o G++ instalado, você pode simplesmente digitar `make` no terminal na pasta contendo este arquivo readme. Depois disso, você pode digitar `make clean` para limpar os arquivos .o que foram gerados. Alternativamente, você pode digitar `g++ main/main.cpp source/core.cpp source/processor.cpp -I include/ -o cachesim.out` para obter um resultado similar.

## Uso
Você pode rodar o programa digitando o seguinte comando na raiz do projeto:  
`./cachesim <arquivo de entrada> <numero de cores> <tamanho da cache L1>`  
O arquivo de entrada deve conter apenas números, que serão carregados na memória principal. O número de cores deve ser um múltiplo de 2. O tamanho da cache L1 deve ser qualquer valor maior que 0. Depois disso, se a inicialização ocorrer normalmente, você pode usar o programa normalmente.

## Estrutura do projeto
O projeto está sendo desenvolvido na linguagem C++.  
A estrutura do projeto é a seguinte:  
include/ - Deve conter os arquivos de cabeçalho. Arquivos contendo a declaração de structs, classes etc devem permanecer aqui.  
source/ - Deve conter a implementação das classes definidas anteriormente, exceto classes templates. Elas devem ir para a pasta include.  
main/ - Deve conter qualquer arquivo com um método `main()`.

## Contato
Para qualquer pergunta, você pode me contatar em https://twitter.com/fr4ct1ons ou via https://github.com/lucena-fr4ct1ons/. A propósito, fique a vontade para checar meus outros trabalhos!
