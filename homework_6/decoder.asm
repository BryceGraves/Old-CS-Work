sys_exit    equ 1
sys_read    equ 3
sys_write   equ 4
run         equ 80H
return      equ 0
stdin       equ 0
stdout      equ 1

section .bss
  size_of_buffer: equ 1024                                      ;size of buffer to be made
  input_buffer: resb size_of_buffer                             ;input buffer allocated using size of buffer above
  input_buffer_length: equ $ - input_buffer                     ;input buffer length
  output_buffer: resb size_of_buffer                            ;output buffer allocated using size of buffer above
  output_buffer_length: equ $ - output_buffer                   ;output buffer length

section .text
  global _start

_start:
  ;buffer input and length stuff
  mov  edx, input_buffer_length                                ;length of buffer input
  mov  ecx, input_buffer                                       ;pointer of buffer input to be stored
  mov  ebx, stdin                                              ;stdin call
  mov  eax, sys_read                                           ;sys_read call
  int  run                                                     ;kernal call for above op codes

  ;setup
  mov  esi, input_buffer                                       ;Pointer to the first byte of input
  mov  edi, output_buffer                                      ;move start of buffer pointer to ebx
  mov  al,  byte [esi]                                         ;put first char in input into al for use
  inc  esi                                                     ;move input pointer forward 1 to nab the count for the second character
  mov  bl,  byte [esi]                                         ;move number of times the character appeared to bl
  inc  esi                                                     ;move input pointer forward 1 to nab the count for the third character

loopy:                                                         ;it's ya boi loopy again
  mov  [edi], al                                               ;move stored character to output buffer
  inc  edi                                                     ;increment output pointer to next spot for a character
  dec  ebx                                                     ;lower character count by one
  cmp  bl, byte 0x30                                           ;check to see if count is 0 by checking the ascii value of 0
  ja   loopy                                                   ;if it's above we go back to our boi loopy for more

  mov  al,  byte [esi]                                         ;smack a new character into al for character storage
  inc  esi                                                     ;move input pointer forward 1 for count
  mov  bl,  byte [esi]                                         ;move count into bl for count storage
  inc  esi                                                     ;move pointer forward one to check next character later

  cmp  al,  10                                                 ;check to see if return character is next
  je   exit                                                    ;if it is head for the exit
  jmp  loopy                                                   ;head back to loopy for more

exit:
  mov  [edi], al                                               ;move newLine character into buffer to keep things pretty
  mov  edx, output_buffer_length                               ;length of output
  mov  ecx, output_buffer                                      ;pointer to where output is stored in memory
  mov  ebx, stdout                                             ;stdout call
  mov  eax, sys_write                                          ;sys_write call
  int  run                                                     ;kernel call for above

  mov  ebx, return                                             ;pass null return value to ebx
  mov  eax, sys_exit                                           ;sys_exit call
  int  run                                                     ;kernel call

