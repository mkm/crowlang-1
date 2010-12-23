.globl __crow_f1
__crow_f1:
pushl %ebp
movl %esp,%ebp
subl $4,%esp
movl $42,%eax
movl %eax,-4(%ebp)
movl -4(%ebp),%eax
movl %ebp,%esp
popl %ebp
ret
.globl __crow_f2
__crow_f2:
pushl %ebp
movl %esp,%ebp
subl $12,%esp
movl $0,%eax
movl %eax,-4(%ebp)
movl $0,%eax
movl %eax,-8(%ebp)
movl -4(%ebp),%eax
movl -8(%ebp),%ebx
test %ebx,%eax
je ref4
movl $2,%eax
movl %eax,-12(%ebp)
jmp ref5
ref4:
movl $3,%eax
movl %eax,-12(%ebp)
ref5:
movl -12(%ebp),%eax
movl %ebp,%esp
popl %ebp
ret
.globl __crow_f3
__crow_f3:
pushl %ebp
movl %esp,%ebp
subl $12,%esp
movl $1,%eax
movl %eax,-4(%ebp)
movl $0,%eax
movl %eax,-8(%ebp)
movl -4(%ebp),%eax
movl -8(%ebp),%ebx
test %ebx,%eax
je ref9
movl $2,%eax
movl %eax,-12(%ebp)
jmp ref10
ref9:
movl $3,%eax
movl %eax,-12(%ebp)
ref10:
movl -12(%ebp),%eax
movl %ebp,%esp
popl %ebp
ret
.globl __crow_f4
__crow_f4:
pushl %ebp
movl %esp,%ebp
subl $8,%esp
movl $8,%eax
movl %eax,-4(%ebp)
movl -4(%ebp),%eax
movl %eax,-8(%ebp)
movl -8(%ebp),%eax
movl %ebp,%esp
popl %ebp
ret
