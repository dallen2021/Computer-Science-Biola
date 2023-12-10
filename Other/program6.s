.data
x_prompt:
	.string "\nEnter Value for x: "
y_prompt:
	.string "\nEnter Value for y: "
newLine:
	.string "\n"
add_sign:
	.string " + "
sub_sign:
	.string " - "
mult_sign:
	.string " * "
equal_sign:
	.string " = "

.bss
	.lcomm x, 32
	movl $0, x
	.lcomm y, 32
	movl $0, y
	.lcomm result, 32
	movl $0, result

.text
.global main
main:
	# Prompt user for x
	movq $4, %rax           
	movq $1, %rbx
	movq $x_prompt, %rcx    # message to write
	movq $20, %rdx          # length of message
	int $0x80               

	# Read x
	movq $3, %rax           # sys_read
	movq $0, %rbx           
	movq $x, %rcx           
	movq $0x2, %rdx         # size
	int $0x80               

	# Prompt user for y
	movq $4, %rax           
	movq $1, %rbx
	movq $y_prompt, %rcx    # message to write
	movq $20, %rdx          # length of message
	int $0x80

	# Read y
	movq $3, %rax           # sys_read
	movq $0, %rbx          
	movq $y, %rcx          
	movq $0x2, %rdx         # size
	int $0x80              

# Addition (x + y =) 
	movq $4, %rax           
	movq $1, %rbx           
	movq $newLine, %rcx     # message to write
	movq $1, %rdx           # length of message
	int $0x80               

	movq $4, %rax           
	movq $1, %rbx           
	movq $x, %rcx           
	movq $1, %rdx           
	int $0x80               

    # Output addition sign
	movq $4, %rax           
	movq $1, %rbx           
	movq $add_sign, %rcx    
	movq $3, %rdx           
	int $0x80               

	movq $4, %rax           
	movq $1, %rbx           
	movq $y, %rcx           
	movq $1, %rdx           
	int $0x80               

    # Output equal sign
	movq $4, %rax           
	movq $1, %rbx           
	movq $equal_sign, %rcx  
	movq $3, %rdx           
	int $0x80               

    movq x, %rdx            # move x to rdx 
    subq $0x30, %rdx        # convert to number
    
    movq y, %rax            # move y to rax 
    subq $0x30, %rax        # convert to number

    # Calculation
    addq %rax, %rdx         # add y and store result in rdx
    addq $0x30, %rdx        # convert back to ASCII
    movq %rdx, result       # store ASCII value into result

    # Output result
    movq $4, %rax               
    movq $1, %rbx               
    movq $result, %rcx           
    movq $0x1, %rdx             
    int  $0x80              

    # Reset
    movl $0, result         # Reset to 0
    movq $0, %rdx           # move value 0 to rdx register
    movq $0, %rax           # move value 0 to rax register


# Subtraction (x - y =) 
    # NewLine message
    movq $4, %rax               
    movq $1, %rbx               
    movq $newLine, %rcx         
    movq $1, %rdx               
    int  $0x80                 
    
    
    movq $4, %rax               
    movq $1, %rbx               
    movq $x, %rcx           
    movq $0x1, %rdx             
    int  $0x80                
    
    # Output subtraction sign
    movq $4, %rax               
    movq $1, %rbx               
    movq $sub_sign, %rcx        
    movq $3, %rdx               
    int  $0x80               
    
     
    movq $4, %rax               
    movq $1, %rbx               
    movq $y, %rcx           
    movq $0x1, %rdx             
    int  $0x80              
    
    # Output equal sign
    movq $4, %rax               
    movq $1, %rbx               
    movq $equal_sign, %rcx       
    movq $3, %rdx               
    int  $0x80              
    
    movq x, %rdx            # move x to rdx 
    subq $0x30, %rdx        # convert to number
    
    movq y, %rax            # move y to rax 
    subq $0x30, %rax        # convert to number

    # Calculation
    subq %rax, %rdx         # subtract y from x and store result in rdx 
    addq $0x30, %rdx        # convert back to ASCII
    movq %rdx, result       # store ASCII value into z

    # Output result
    movq $4, %rax               
    movq $1, %rbx               
    movq $result, %rcx           
    movq $0x1, %rdx             
    int  $0x80              

    # Reset
    movl $0, result         # Reset to 0
    movq $0, %rdx           # move value 0 to rdx register
    movq $0, %rax           # move value 0 to rax register


# Multiplication (x * y =)
    # NewLine message
    movq $4, %rax               
    movq $1, %rbx               
    movq $newLine, %rcx         
    movq $1, %rdx               
    int  $0x80                
    
    
    movq $4, %rax               
    movq $1, %rbx               
    movq $x, %rcx           
    movq $0x1, %rdx             
    int  $0x80                
    
    # Output multiplication sign
    movq $4, %rax               
    movq $1, %rbx               
    movq $mult_sign, %rcx     
    movq $3, %rdx               
    int  $0x80              
    
    
    movq $4, %rax               
    movq $1, %rbx               
    movq $y, %rcx           
    movq $0x1, %rdx             
    int  $0x80              
    
    # Output equal sign 
    movq $4, %rax               
    movq $1, %rbx               
    movq $equal_sign, %rcx       
    movq $3, %rdx               
    int  $0x80              

    movq x, %rdx            # move x to rdx 
    subq $0x30, %rdx        # convert to number
    
    movq y, %rax            # move y to rax 
    subq $0x30, %rax        # convert to number

    # Calculation
    imulq %rax, %rdx        # multiply by x and store result in rdx 
    addq $0x30, %rdx        # convert back to ASCII
    movq %rdx, result       # store ASCII value into result

    # Output result
    movq $4, %rax               
    movq $1, %rbx               
    movq $result, %rcx           
    movq $0x1, %rdx             
    int  $0x80              


    # Exit with return 0
	movl $1, %eax       # exit(0)   
	movl $0, %ebx          
	int  $0x80              
	ret
