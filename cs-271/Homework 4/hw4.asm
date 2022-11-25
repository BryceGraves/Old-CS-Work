sys_exit    equ 1
sys_read    equ 3
sys_write   equ 4

run         equ 80H
return      equ 0
length      equ 1        ;byte length of chunk pulled

stdin       equ 0
stdout      equ 1

%macro clear 0
  xor  eax, eax
  xor  ebx, ebx
  xor  ecx, ecx
  xor  edx, edx
%endmacro

section .data
  x: db 4
  y: db 0
  z: db 0
  a: db 0
  temp: db 0

section .text
  global _start

_start:

  ;setup
  clear                                                  ;part 1 already complete x = 2

  ;part 2 (6) y = x + 4
  mov  al,  byte [x]                                     ;move starting 2 into register for addition
  add  eax, 4                                            ;add four for sum of 6

  mov  [y], al                                           ;move new value to y for use later

  ;part 3: (3) z = y - (x + 1)
  clear

  mov  al,  byte [y]                                     ;move previously calculated y to eax
  mov  bl,  byte [x]                                     ;move original x to ebx
  
  add  ebx, 1                                            ;add one to x
  sub  eax, ebx                                          ;subtract sum of x and 1 (3)

  mov  [z], al                                           ;store z for use later

  ;part 4: a = (x + z) * (y / 2) + z^2
  clear

  mov  al,   byte [y]                                    ;move y into eax for division
  mov  ebx,  2                                           ;move 2 into ebx to divide eax by 2

  div  ebx                                               ;divide eax by the 2 in ebx
  mov  ebx, eax                                          ;store what was divided in ebx

  mov  al,  byte [z]                                     ;move z to eax to add x to it
  add  al,  byte [x]                                     ;add x to z in eax
  mul  ebx                                               ;multiply ebx and eax
  mov  ebx, eax                                          ;overwrite previous total with new product

  mov  al,  byte [z]                                     ;move z into eax for squaring
  mul  eax                                               ;square z
  add  eax, ebx                                          ;add z^2 to previous product
  mov  [a], al                                           ;store value in eax in variable a
  
  ;part 5: x = a + z
  clear

  mov  al,  byte [a]                                     ;move a to eax
  mov  bl,  byte [z]                                     ;move z to ebx
  add  eax, ebx                                          ;add a and z
  mov  [x], al                                           ;overwrite x

  ;final check
  clear

  mov  al,  byte [x]
  mov  bl,  byte [y]
  mov  cl,  byte [z]
  mov  dl,  byte [a]

end_program:
  mov  eax, sys_exit                                     ;sys_exit call
  mov  ebx, return                                       ;return nothing (0)
  int  run                                               ;kernal call for above op c
