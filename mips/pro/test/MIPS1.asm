addi $s0, $s1, 2
and $s1, $s0, $s1
funa:nor $s2, $s0, $s2
or $s3, $s0, $s3
funb:sll $s4, $s0, 2
srl $s5, $s4, 2
add $s5, $s5, $s0
sub $s5, $s5, $s0
lw $t0, 4($at)
sw $t0, 8($at)
j funa
