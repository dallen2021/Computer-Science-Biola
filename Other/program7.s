.section .data
array:
  .long 1, 1, 2, 3     # integer array with four values

msg:
  .ascii "The sum is: "    # message to be displayed

sum_str:
  .space 1          # space for 1 character to represent sum (assuming an 8-bit integer)

.section .text
.globl main

main:
  movl $0, %eax       # initialize sum to zero
  movl $0, %ecx       # initialize loop counter to zero

sum_loop:
  cmp $4, %ecx        # check if loop counter is equal to four
  je sum_done         # if so, jump to end of loop
  movl array(,%ecx,4), %ebx   # get current array element and store in ebx
  addl %ebx, %eax     # add current array element to sum
  incl %ecx           # increment loop counter
  jmp sum_loop        # jump back to start of loop

sum_done:
  movl %eax, %ebx     # move sum to ebx for ASCII conversion
  add $0x30, %bl      # convert to ASCII
  movb %bl, sum_str   # store ASCII value
  movq $4, %rax          
  movq $1, %rbx         
  movq $msg, %rcx   
  movq $12, %rdx         
  int $0x80          
  
  movq $4, %rax
  movq $1, %rbx 
  movq $sum_str, %rcx    
  movq $1, %rdx        
  int $0x80          

exit:
  movl $0, %eax       # set return value to zero
  movl $1, %ebx       # system call for exiting program
  int $0x80           
