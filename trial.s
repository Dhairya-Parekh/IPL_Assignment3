	.globl main
 	.type main, @function
.LC0:
    .string "Hello %d %d %d, world!\n"
.LC1:
    .string "Hola, mundo!\n"
.LC2:
    .string "Bonjour, monde!\n"
main:
    pushl   %ebp
    movl    %esp, %ebp
    pushl   $34
    pushl   $56
    pushl   $78
    pushl   $.LC0
    call    printf
    addl    $4, %esp
    pushl   $.LC1
    call    printf
    addl    $4, %esp
    pushl   $.LC2
    call    printf
    addl    $4, %esp
    movl    $0, %eax
    leave
    ret
    