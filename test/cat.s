.globl __crow_main
__crow_main:
pushl %ebp
movl %esp,%ebp
subl $20,%esp
call __crow_stdin
addl $0,%esp
movl %eax,-4(%ebp)
movl -4(%ebp),%eax
pushl %eax
call __crow_readFile
addl $4,%esp
movl %eax,-8(%ebp)
movl -8(%ebp),%eax
movl %eax,-12(%ebp)
movl -12(%ebp),%eax
pushl %eax
call __crow_stdout
addl $0,%esp
movl %eax,-16(%ebp)
movl -16(%ebp),%eax
pushl %eax
call __crow_writeFile
addl $8,%esp
movl %eax,-20(%ebp)
movl -20(%ebp),%eax
movl %ebp,%esp
popl %ebp
ret
