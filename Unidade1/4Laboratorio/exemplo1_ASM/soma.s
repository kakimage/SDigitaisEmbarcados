@ simbolo de comentario, equivale ao // do C++

      .text                  @ tudo daqui para baixo sera considerado texto, entenda-se

                             @ "codigo", outro segmento possivel seria .data "dados", area de variaveis
start:                       @ um label, nao ocupa espaco
        mov   r0, #5         @ carrega o registrador r0 com o valor constante 5
        mov   r1, #4         @ carrega o valor r1 com o valor constante 4
        add   r2, r1, r0     @ adiciona r0 a  r1  e coloca o resultado em r2

stop:   b stop               @ aqui existe um outro label e uma instrucao de b "branch", 
                             @ que salta para o label stop, logo isso é um loop infinito
