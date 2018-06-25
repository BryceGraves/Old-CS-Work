section .text
global count_digits;

; count_digits counts the number of digits in an integer value
; e.g., 1000 has 4 digits.
;
; eax contains integer value to count 
; return value (number of digits) stored in eax

count_digits:
  ;setup
  mov  ebx, 10          ;adding 10 to ebx to divide using it later
  mov  ecx, 0           ;setting digit ccount to 0
  mov  edx, 0           ;setting edx to zero for a sanity check

.loopy:
  cmp  eax, 0           ;check to see if last division made integer 0
  je   .return          ;head to return when out of digits

  div  ebx              ;smack a digit off
  mov  edx, 0           ;clear overflow
  inc  ecx              ;put the digit in the bucket
  jmp  .loopy           ;head back for another smack

.return:                ;we gotta go back
  mov  eax, ecx         ;move digit count to eax
  ret                   ;get out of here

