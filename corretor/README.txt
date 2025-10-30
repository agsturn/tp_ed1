==================================================
README - Como Usar o Corretor Automático do TP1
==================================================

Este arquivo explica como usar o script 'corretor.py' e o 'Makefile' para compilar e testar automaticamente o código do TP1.

-------------------------
1. Estrutura de Pastas
-------------------------

É ESSENCIAL que a estrutura de pastas seja mantida exatamente como abaixo:

TP1/
├── formula.c
├── formula.h
├── tp.c
├── (e os outros arquivos do projeto)
│
└── corretor/
    ├── corretor.py       (script de correção)
    ├── Makefile         (arquivo de compilação)
    ├── README.txt       (Este arquivo)
    │
    └── tests/
        ├── 3cnf-3v-5c.txt
        ├── 3cnf-3v-5c.out
        ├── 3cnf-5v-10c.txt
        ├── 3cnf-5v-10c.out
        └── (etc... todos os outros arquivos de teste)

Resumo:
- Os arquivos de código-fonte (.c, .h) ficam na raiz da pasta `TP1`.
- Os arquivos do corretor (script, Makefile) ficam na subpasta `TP1/corretor/`.
- Uma cópia dos arquivos de teste (.txt, .out) ficam na subpasta `TP1/corretor/tests/`.

-------------------------
2. Como Rodar os Testes
-------------------------

1.  Abra o seu terminal (de preferência o terminal do próprio VS Code). 
2.  Navegue para DENTRO da pasta `corretor`.
    (Exemplo de comando: `cd caminho/para/seu/projeto/TP1/corretor`)
3.  Uma vez DENTRO da pasta `corretor`, execute o seguinte comando:
    
    python corretor.py

-------------------------
3. O que o Script Faz
-------------------------

Ao ser executado, o script `corretor.py` vai:

1.  **Chamar o `make`:** Ele usará o `Makefile` para compilar seu código. O `Makefile` está configurado para buscar os arquivos `.c` na pasta de cima (`../`).
    * Se der **Erro de Compilação**, o script para e sua nota é 0.
    * Se o código compilar com **Warnings**, o script avisa e sua nota final será reduzida.

2.  **Executar os Testes:** O script vai pegar cada arquivo `.txt` de dentro da pasta `tests/`.
    * Ele executa o seu programa (`./exe`) usando o `.in` como entrada.
    * Ele compara a saída do seu programa com o conteúdo do arquivo `.out` correspondente.

3.  **Mostrar o Resultado:** Você verá o status de cada teste:
    * **[ OK ]**: A saída do seu programa foi idêntica à saída esperada.
    * **[ ER ]**: A saída do seu programa foi diferente do arquivo `.out` (Erro).
    * **[ EXCEDEU O TEMPO ]**: Seu programa demorou mais de 5 segundos para executar esse teste e foi interrompido.

4.  **Calcular a Nota:** No final, o script mostrará uma nota de 0.0 a 10.0, baseada na porcentagem de testes corretos e na presença (ou não) de warnings na compilação.

-------------------------
4. Como Adicionar Novos Testes
-------------------------

Você pode criar seus próprios testes facilmente:

1.  Crie um arquivo de entrada (ex: `meu_teste.txt`) com o caso de teste que você quer.
2.  Descubra qual é a saída correta para esse teste e crie o arquivo de saída correspondente (ex: `meu_teste.out`).
3.  Coloque AMBOS os arquivos (`meu_teste.txt` e `meu_teste.out`) dentro da pasta `corretor/tests/`.

Pronto! Na próxima vez que você rodar `python corretor.py`, seus novos testes serão incluídos automaticamente.