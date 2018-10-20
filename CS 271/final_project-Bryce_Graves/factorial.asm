section .text
global factorial

; factorial function calculate N! (N factorial) for input N
;
; eax holds N, the integer to factorial
; return value N! (N factorial) stored in eax

factorial:
  cmp  eax, 0              ;check to see if our starting factorial is 0
  je   .if_zero            ;head to section just for that case

  ;setup
  mov  ebx, eax            ;copy factorial to ebx for multiplication
  dec  ebx                 ;decrement for multiplication

.loopy:
  cmp  ebx, 0              ;check to see if the next digit to multiply is 0
  je   .return             ;if the next number is zero head for the exit

  mul  ebx                 ;multiply next factorial and current total
  dec  ebx                 ;lower by one for next multiplication
  jmp  .loopy              ;head back for more

.if_zero:                  ;if factorial is zero the result is 1 because math
  mov  eax, 1              ;set result to 1 then head down to return

.return:                   ;time to head back from the math party
  ret                      ;the exit

