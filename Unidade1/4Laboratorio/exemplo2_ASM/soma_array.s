        .text
entry:  b start                 @ Skip over the data
arr:    .byte 10, 20, 25        @ define um array de bytes
eoa:                            @ captura o endereco do final do array

        .align
start:
        ldr   r0, =eoa          @ carrega para r0 o endereco do final do vetor
        ldr   r1, =arr          @ carrega o endereco de inicio do vetor em r1
        mov   r3, #0            @ r3 = 0

loop:   ldrb  r2, [r1], #1      @ r2 recebe o contedudo do endereco r1 e depois incrementa o endereoco r1 
        add   r3, r2, r3        @ r3 acumula o valor de r2      r3 += r2
        cmp   r1, r0            @ faz uma comparacao entre os enderecos armazenados em r1 e r2.
                                @ internamente faz uma subtracao e afeta os flags. se forem iguais o valor resultara em 
                                @ zero e assim afeta o flag de zero. 
        bne   loop              @  branch if not equal, testa o flag de zera e salta se nao deu zero 
stop:   b stop                  @ fica em loop infinito
