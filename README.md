# SnakeC

Projeto criado para cadeira de PIF do segundo periodo da Cesar School.

# Integrantes

Rubens de Souza Filho, Maria Luiza Calife, Gabriel Reinaldo Roma,

# Professores

Pamela Bezerra, Tiago Barros

# Instrução de compilação

Instruções de Compilação para SnakeC:

Estas instruções são destinadas a compilar o código-fonte do SnakeC em sua máquina local.

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

Observações:

Certifique-se de ter o GCC instalado em seu sistema.
Verifique se os arquivos necessários estão nos diretórios corretos (src para arquivos-fonte e include para arquivos de cabeçalho).
Caso haja erros durante a compilação, verifique as mensagens de erro e corrija os problemas nos arquivos-fonte.




