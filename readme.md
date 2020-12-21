**Instruções de execução/compilação**

 

 

Baixe o projeto, entre na pasta do projeto e execute:

 

mkdir build &&cd build

 

Caso queria que a execução mostre todos os passos executados, execute o comando:

cmake -DDEBUG=true -S ..

Obs: a execução do programa com este comando é mais demorada pois irá printar no output todas as saídas.

 

Caso contrário execute com o comando abaixo.

cmake -DDEBUG=false -S ..

 

Após a executação de um dos comandos listados acima, execute o comando:

make

 

E finalmente execute:

./Bankrupt

 
