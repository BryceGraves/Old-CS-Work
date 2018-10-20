section .text
global itoa;

; eax is integer to be converted to ASCII
; ebx is number of digits in integer
; ecx is output buffer to fill with ASCII characters
; e.g., integer 40320 gets converted to ASCII '40320'

itoa:
  ;setup
  mov  edi, ecx                 ;moving pointer from ecx for edi for consistency
  mov  ecx, ebx                 ;move length to ecx for iteration
  mov  ebx, 10                  ;put 10 in ebx to divide with later
  add  edi, ecx                 ;move output pointer to end output to be passed
  dec  edi                      ;move back one to the correct spot
  mov  edx, 0                   ;setting to 0 to make sure nothing is in it

.loopy:
  cmp  ecx, 0                   ;check to see if we are done
  je   .return                  ;head for the exit

  div  ebx                      ;divide integer by 10, the remainder is the single digit we need
  add  edx, 48                  ;convert single digit to ascii
  mov  [edi], dl                ;smack that digit into the output buffer
  mov  edx, 0                   ;clear overflow
  dec  edi                      ;move the buffer to the next digit location
  dec  ecx                      ;decrement by 1 since we have looped
  jmp  .loopy                   ;head back for more

.return:                        ;marty, you gotta come back with me!
  ret                           ;back to the future!

