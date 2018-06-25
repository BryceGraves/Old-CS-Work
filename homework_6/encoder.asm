sys_exit    equ 1
sys_read    equ 3
sys_write   equ 4
run         equ 80H
return      equ 0
stdin       equ 0
stdout      equ 1

section .bss
  size_of_buffer: equ 1024                                           ;size of buffer to be made
  input_buffer: resb size_of_buffer                                  ;input buffer
  input_buffer_length: equ $ - input_buffer                          ;length of input buffer
  output_buffer: resb size_of_buffer                                 ;output buffer
  output_buffer_length: equ $ - output_buffer                        ;length of output buffer

section .text
  global _start

_start:
  ;buffer input and length stuff
  mov  edx, input_buffer_length                                ;length of buffer input
  mov  ecx, input_buffer                                       ;pointer of buffer input to be stored
  mov  ebx, stdin                                              ;stdin call
  mov  eax, sys_read                                           ;sys_read call
  int  run                                                     ;kernal call for above op code section

  ;setup
  mov  esi, input_buffer                                       ;move input_buffer pointer to esi
  mov  edi, output_buffer                                      ;move output buffer pointer to edi
  mov  ecx, input_buffer_length                                ;put buffer_length into ecx for iteration
  mov  al,  byte [input_buffer]                                ;pull first character to start the show
  mov  ebx, 0x00000031                                         ;set char count to one for the first char pull
  mov  edx, 2                                                  ;assigning 2 to edx to keep track of the length to output. For the first 2 bytes used.

loopy:
  dec  ecx                                                     ;decrementing at the start of loop to avoid having to remember >.<
  inc  esi                                                     ;move forward one character

  cmp  al, byte [esi]                                          ;compare previous char and the next char
  jne  new_char                                                ;if previous char and next input char are not the same jump to new char

  inc  ebx                                                     ;they are the same so we increment
  jmp  loopy                                                   ;head back to into loopy for more

new_char:
  mov  [edi], al                                               ;move old char to output buffer
  inc  edi                                                     ;move over one to add number of chars counted
  mov  [edi], bl                                               ;move count of old char to output buffer
  inc  edi                                                     ;move over one so we can do this again later
  add  edx, 2                                                  ;increase size of output by 2
  mov  ebx, 0x00000031                                         ;set count to one to account for new char
  mov  al, byte [esi]                                          ;move new char in to be counted

  cmp  al,  10                                                 ;check for return character, if it's there it's the end of input
  je   end_of_program                                          ;if equal jump to end processes

  jmp  loopy                                                   ;head back up to loopy for another loopy

end_of_program:
  mov  [edi], al                                               ;adding the return character to buffer to make things beautiful
  inc  edx                                                     ;increasing length of buffer to include return character

  mov  ecx, output_buffer                                      ;current byte to print in output buffer
  mov  ebx, stdout                                             ;smacking stdout into ebx to be called below
  mov  eax, sys_write                                          ;smacking sys_write into eax to be called below
  int  run                                                     ;kernel call of above

  mov  ebx, return                                             ;return 0 on exit
  mov  eax, sys_exit                                           ;exit call
  int  run                                                     ;call kernel to exit
