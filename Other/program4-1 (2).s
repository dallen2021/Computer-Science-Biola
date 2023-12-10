.section .data
slope_prompt:
  .ascii "Enter the slope m:"           # prompt the user for slope input
  slope_prompt_len = . - slope_prompt   # length of message in bytes
yint_prompt:
  .ascii "\nEnter the y-intercept b:"   # prompt the user for y-intercept input
  yint_prompt_len = . - yint_prompt     
x_prompt:
  .ascii "\nEnter the value for x:"     # prompt the user for x input
  x_prompt_len = . - x_prompt           
result_msg:
  .ascii "\nThe value for y is: "       # display result


.section .bss
slope_input:
  .skip 1         # reserve 1 byte of memory for each input
yint_input:
  .skip 1        
x_input:
  .skip 1        
result:
  .skip 1         


.section .text
.globl main

main:
  # prompt user for slope input
  mov $4, %eax
  mov $1, %ebx
  mov $slope_prompt, %ecx        # address of the slope  
  mov $slope_prompt_len, %edx    # length of the slope  
  int $0x80                      # system call to display prompt

  # read slope input
  mov $3, %eax
  mov $0, %ebx
  mov $slope_input, %ecx         
  mov $1, %edx
  int $0x80                      

  # prompt user for y-intercept input
  mov $4, %eax
  mov $1, %ebx
  mov $yint_prompt, %ecx         # address of the y-intercept  
  mov $yint_prompt_len, %edx     # length of the y-intercept  
  int $0x80                      # system call to display prompt 

  # read y-intercept input
  mov $3, %eax
  mov $0, %ebx
  mov $yint_input, %ecx         
  mov $1, %edx
  int $0x80                      

  # prompt user for x input
  mov $4, %eax
  mov $1, %ebx
  mov $x_prompt, %ecx            # address of the x  
  mov $x_prompt_len, %edx        # length of the x  
  int $0x80                      # system call to display prompt

  # read x input
  mov $3, %eax
  mov $0, %ebx
  mov $x_input, %ecx             
  mov $1, %edx
  int $0x80                     

  # convert ASCII inputs to integer values
  sub $0x30, slope_input         # subtract ASCII value of '0' from each input to convert to integers
  sub $0x30, yint_input          
  sub $0x30, x_input             


  # calculate y = mx + b
  movzx slope_input, %eax 		# move the value of slope_input into the lower 8 bits of eax, setting the rest to 0
  imul x_input, %eax 			# multiply eax by x_input and store the result in eax
  add yint_input, %eax 			# add yint_input to eax and store the result in eax

  # convert result to ASCII
  add $0x30, %al 				# add the ASCII value of '0' to the lower 8 bits of eax, converting it to ASCII
  mov %al, result 				# move the value of eax into the result buffer

  # display result
  mov $4, %eax 					
  mov $1, %ebx 					
  mov $result_msg, %ecx			# set buffer address for output to result_msg
  mov $19, %edx 				# set length of output to 19 (length of result_msg + length of result)
  int $0x80 					

  mov $4, %eax 					
  mov $1, %ebx 					
  mov $result, %ecx 			# set buffer address for output to result
  mov $1, %edx 					
  int $0x80 					# call kernel to write output to stdout

  # exit program
  xor %eax, %eax 				# set return code to 0
  mov $1, %eax				 	
  xor %ebx, %ebx 				# clear ebx
  int $0x80 					# exit program and return 0
