.section .data
    prompt1: .ascii "Enter the value of x: "
    prompt2: .ascii "\nEnter the value of y: "
    x_greater: .ascii "\nx > y"
    y_greater: .ascii "\nx <= y"

.section .text
.globl main
main:
    # Prompt the user for the value of x
    mov $4, %eax
    mov $1, %ebx
    mov $prompt1, %ecx
    mov $22, %edx
    int $0x80
    
    # Read the value of x from the user
    mov $3, %eax
    mov $0, %ebx
    lea x, %ecx
    mov $1, %edx
    int $0x80
    
    # Prompt the user for the value of y
    mov $4, %eax
    mov $1, %ebx
    mov $prompt2, %ecx
    mov $23, %edx
    int $0x80
    
    # Read the value of y from the user
    mov $3, %eax
    mov $0, %ebx
    lea y, %ecx
    mov $1, %edx
    int $0x80
    
    # Convert ASCII value of x to integer
    sub $0x30, x    # Subtract to convert ASCII to integer
    movzx x, %ax    # Move converted value to register ax
    
    # Convert ASCII value of y to integer
    sub $0x30, y    # Subtract to convert ASCII to integer
    movzx y, %bx    # Move converted value to register bx
    
    # Compare x and y
    cmp %ax, %bx    # Compare values of ax and bx
    jge x_leq_y     # Jump if ax is greater than or equal to bx

    # If x > y, print message
    mov $4, %eax
    mov $1, %ebx
    mov $x_greater, %ecx
    mov $6, %edx
    int $0x80

    # Exit program
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80

x_leq_y:
    # If x <= y, print message
    mov $4, %eax
    mov $1, %ebx
    mov $y_greater, %ecx
    mov $7, %edx
    int $0x80

    # Exit program
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80

    
.section .bss
    .lcomm x, 1
    .lcomm y, 1