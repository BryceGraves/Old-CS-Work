sys_exit    equ 1
sys_read    equ 3
sys_write   equ 4

run         equ 80H
return      equ 0
length      equ 1        ;byte length of chunk pulled

stdin       equ 0
stdout      equ 1

section .data
  message             db 'Type brackets below:', 0Ah     ;starting message and new line
  message_length      equ $-message                      ;length of starting message and new line
  error               db 'ERROR!!!', 0Ah                 ;error message and new line
  error_length        equ $-error                        ;length of error and new line

section .bss
  size_of_buffer: equ 1024                               ;size of buffer to be made
  buffer: resb size_of_buffer                            ;buffer allocated using size of buffer above
  buffer_length: equ $ - buffer                          ;length of buffer
 
section .text
  global _start

_start:
  ;starting message
  mov  edx, message_length                               ;assign message length to count
  mov  ecx, message                                      ;smack in memory location that message is stored at
  mov  ebx, stdout                                       ;stdout call
  mov  eax, sys_write                                    ;sys_write call
  int  run                                               ;kernal call for above op codes
  
  ;buffer input and length stuff
  mov  edx, buffer_length                                ;length of buffer input
  mov  ecx, buffer                                       ;pointer of buffer input to be stored
  mov  ebx, stdin                                        ;stdin call
  mov  eax, sys_read                                     ;sys_read call
  int  run                                               ;kernal call for above op codes

  ;setup
  mov  edi, esp                                          ;assign bottom of stack pointer to edi for check later
  mov  ebx, buffer                                       ;move start of buffer pointer to ebx
  mov  ecx, buffer_length                                ;put buffer_length into ecx for iteration

loopy_boi:                                               ;a boi that loops
  mov  al,  byte [ebx]                                   ;asssign value at current memory location to eax
  inc  ebx                                               ;incriment memory location to next byte for use later

  cmp  al,  40                                           ;compare current byte to "(" - curvy boi
  je   push_it                                           ;jump to push function to push curvy boi onto stack

  cmp  al,  91                                           ;compare current byte to "{" - wiggly boi
  je   push_it                                           ;jump to push function to push wiggly boi onto stack

  cmp  al,  123                                          ;compare current byte to "[" - squary boi
  je   push_it                                           ;jump to push function to push squary boi onto stack

  cmp  al,  41                                           ;compare current byte to ")" - curvy boi
  je   pop_it_curvy_boi                                  ;jump to pop function to compare current byte to the previously pushed byte

  cmp  al, 93                                            ;compare current byte to "}" - wiggly boi
  je   pop_it_wiggly_boi                                 ;jump to pop function to compare current byte to the previously pushed byte

  cmp  al, 125                                           ;compare current byte to "]" - squary boi
  je   pop_it_squary_boi                                 ;jumpt o pop function to compare current byte to the previously pushed byte

  dec  ecx                                               ;lower counter value by 1
  cmp  ecx, 0xffffffff                                   ;check to see if counter is less than 0, is less than zero after final loop... hopefully
  jne  loopy_boi                                         ;jump back to loopy_boi

  cmp  edi, esp                                          ;check to see if stack is empty
  jne  print_error                                       ;if stack is not empty jumpt to print error

  mov  edx, buffer_length                                ;smack the buffer length back into edx for reprinting
  mov  ecx, buffer                                       ;smack the buffer's memory location back into ecx for reprinting
  mov  ebx, stdout                                       ;stdout call
  mov  eax, sys_write                                    ;sys_write call
  int  run                                               ;kernal call for above op codes

end_program:
  mov  eax, sys_exit                                     ;sys_exit call
  mov  ebx, return                                       ;return nothing (0)
  int  run                                               ;kernal call for above op codes

print_error:
  mov  edx, error_length                                 ;smack error length into edx
  mov  ecx, error                                        ;smack error message pointer into ecx
  mov  ebx, stdout                                       ;stdout call
  mov  eax, sys_write                                    ;sys_write call
  int  run                                               ;kernal call for above op codes
  jmp  end_program                                       ;run for the exit

push_it:
  dec  ecx                                               ;lower count by one
  push ax                                                ;smack boi into stack
  jmp  loopy_boi                                         ;head back to our boi loopy

pop_it_curvy_boi: ;we are here because the boi at our current memory address is curvy
  dec  ecx                                               ;lower count by one
  pop  dx                                                ;pop previous boi off the stack (boi is 16-bits)
  cmp  dx, 40                                            ;confirm that our previous boi on stack was a curvy boi
  je   loopy_boi                                         ;if boi was curvy head back to our boi loopy
  jne  print_error                                       ;if not panic and jump to print error

pop_it_wiggly_boi: ;we are here because the boi at our current memory address is wiggly
  dec  ecx                                               ;lower count by one
  pop  dx                                                ;pop previous boi off the stack (boi is 16-bits)
  cmp  dx, 91                                            ;confirm that our previous boi on stack was a wiggly boi
  je   loopy_boi                                         ;if boi was wiggly head back to our boi loopy
  jne  print_error                                       ;if not panic and jump to print error

pop_it_squary_boi: ;we are here because the boi at our current memory address is squary
  dec  ecx                                               ;lower count by one
  pop  dx                                                ;pop previous boi off the stack (boi is 16-bits)
  cmp  dx, 123                                           ;confirm that our previous boi on stack was a squary boi
  je   loopy_boi                                         ;if boi was wiggly head back to our boi loopy
  jne  print_error                                       ;if not panic and jump to print error

