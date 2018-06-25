section .text
global atoi;

; atoi function: convert ASCII character string to integer number
;
; eax is pointer to ASCII buffer to convert
; ebx is length of buffer (number of digits)
;
; return value (integer dword) stored in eax
	
atoi:
  ;setup
  mov  esi, eax               ;moving the pointer from eax to esi
  mov  eax, 0                 ;clear eax
  mov  ecx, ebx               ;move iterations to ecx
  add  esi, ecx               ;move pointer to end of input buffer
  dec  esi                    ;move pointer to the memory address that the value will be added to
  mov  edi, 0                 ;set edi to 0 so we know it doesn't have anything weird in it
  mov  ebx, 1                 ;overwrite ebx with 1 so I can use it for digit multiplication later
  
.loopy:
  cmp  ecx, 0                 ;check to see if the last digit was converted
  je   .return                ;if it was head for the exit

  mov  al, byte [esi]         ;move the digit to convert from buffer to al
  sub  eax, 48                ;convert digit from ascii to integer
  mul  ebx                    ;multiply convert integer to the correct digit count
  add  edi, eax               ;add integer to total

  mov  eax, 10                ;move 10 into eax to multiply with ebx to increase zero count
  mul  ebx                    ;do the multiplication
  mov  ebx, eax               ;move the new zero count multiplier to ebx
  mov  eax, 0                 ;reset eax for sanity check

  dec  ecx                    ;lower number of times to loop by one
  dec  esi                    ;move pointer to next digit to convert
  jmp  .loopy                 ;head back for more

.return:                      ;we gotta go back
  mov  eax, edi               ;move total into eax for use later
  ret                         ;return

