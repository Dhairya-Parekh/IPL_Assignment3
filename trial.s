	.globl main
 	.type main, @function
.LC0:
    .string "Hello, world!\n"
main:
    pushl   %ebp
    movl    %esp, %ebp
    pushl   $.LC0
    call    printf
    leave
    ret
    