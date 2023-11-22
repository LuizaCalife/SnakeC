# SnakeC

Projeto criado para cadeira de PIF do segundo periodo da Cesar School.

# Integrantes

Rubens de Souza Filho, Maria Luiza Calife, Gabriel Reinaldo Roma,

# Professores

Pamela Bezerra, Tiago Barros

# Instrução de compilação

Passo 1: Acesso ao Diretório

Abra um terminal e navegue até o diretório onde os arquivos do SnakeC estão localizados usando o comando cd:

cd seu/caminho/para/SnakeC/

Passo 2: Compilação

Use o compilador GCC para compilar todos os arquivos-fonte .c presentes na pasta src, e especifique o diretório de inclusão para os arquivos de cabeçalho na pasta include. Isso pode ser feito com o seguinte comando:

gcc ./src/*.c -I./include -o change-me

'gcc: Invoca o compilador GCC.
'./src/*.c: Compila todos os arquivos .c dentro da pasta src.
'-I./include: Especifica a localização dos arquivos de cabeçalho na pasta include.
'-o change-me: Define o nome do arquivo de saída como change-me. Você pode alterar change-me para o nome desejado do executável.

Passo 3: Execução

./change-me

Substitua change-me pelo nome que você definiu no passo anterior, se necessário.

# Lista de funções 

loadRanking() = carregamento do ranking do jogo

saveRanking() = salvando os rankings gerados

addPlayerToRanking() = adiciona o jogador atual ao ranking

showRanking() = mostra o ranking das 3 melhores posicoes 

updateScore() = atualizacao do score (de 10 em 10)

initializeGame() = funcao base para inicializar o jogo 

endGame() = funcao base para fechar o jogo

initializeSnake() = inicializacao da cobra no mapa

freeSnake() = liberacao de memoria da cobra

generateFood() = geracao de comida em partes aleatorias do mapa

 drawFood() = desenho da comida
 
 drawSnake() = desenho da cobra
 
 drawBorders() = desenho das bordas do jogo
 
 moveSnake() = movimentacao base da cobra 
 
 handleInput() = atribuimos a movimentacao criada na funcao anterior para as teclas
 
 checkCollision() = colisao da cobra com parede ou ela mesma e caso tenha comido puxamos novamente a funcao generateFood 
 
 gameLoop() = loop do game, caso queira reiniciar 
 
 showMenu() = menu do jogo com as escolhas: jogar e sair
 
 
 
