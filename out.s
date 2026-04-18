.data
newline_str: .asciiz "\n"
.align 2
g_r: .space 8
g_y: .space 4
g_x: .space 4

.text
.globl main
main:
    la $t0, g_x
    li $t1, 5
    sw $t1, 0($t0)
    la $t0, g_y
    li $t1, 3
    sw $t1, 0($t0)
    la $t0, g_y
    lw $t0, 0($t0)
    addiu $sp, $sp, -4
    sw $t0, 0($sp)
    la $t0, g_x
    addiu $sp, $sp, -4
    sw $t0, 0($sp)
    jal proc_addTo
    addiu $sp, $sp, 8
    la $t0, g_r
    addiu $t0, $t0, 0
    la $t1, g_x
    lw $t1, 0($t1)
    sw $t1, 0($t0)
    la $t0, g_r
    addiu $t0, $t0, 4
    la $t1, g_r
    addiu $t1, $t1, 0
    lw $t1, 0($t1)
    li $t2, 2
    mul $t1, $t1, $t2
    sw $t1, 0($t0)
    la $t0, g_r
    addiu $t0, $t0, 4
    lw $t0, 0($t0)
    move $a0, $t0
    li $v0, 1
    syscall
    la $a0, newline_str
    li $v0, 4
    syscall
    li $v0, 10
    syscall
proc_addTo:
    addiu $sp, $sp, -8
    sw $ra, 4($sp)
    sw $fp, 0($sp)
    move $fp, $sp
    lw $t0, 8($fp)
    lw $t1, 8($fp)
    lw $t1, 0($t1)
    addiu $t2, $fp, 12
    lw $t2, 0($t2)
    addu $t1, $t1, $t2
    sw $t1, 0($t0)
ret_addTo_0:
    move $sp, $fp
    lw $fp, 0($sp)
    lw $ra, 4($sp)
    addiu $sp, $sp, 8
    jr $ra
