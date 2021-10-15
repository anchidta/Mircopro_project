.thumb
.syntax unified
@if dont understand address please look memory map 
.equ GPIOA_CRL, 0x40010800 @Port configuration register low
.equ GPIOA_ODR, 0x4001080C @GPIO-A Output Data register
.equ RCC_APB2ENR, 0x40021018 @RCC APB2 peripheral clock enable register
.equ STACKINIT, 0x20005000
.equ LEDDELAY, 2000000 
.text
.org 0
vectors:
.word STACKINIT
@ stack pointer value when stack is empty
.word _start + 1
@ reset vector (odd for thumb state)
.global _start

_start:
@set peripheral clock port GPIO_A
LDR R6, = RCC_APB2ENR
MOV R0, 0x04 @set 0x04 to use GPIOA_EN
STR R0, [R6] @store R0 to R6
@push-pull(00) and 50Mhz(11)
LDR R6, = GPIOA_CRL
LDR R0, = 0x33333333 @0011001100110011001100110011001100
STR R0, [R6] @store R0 to R6
@set port to be output port
LDR R6, = GPIOA_ODR
MOV R2, 1   @ON LED
MOV R3, 0   @OFF LED
MOV R4, 34  @22,00100010 = 34
MOV R5, 49  @31,00110001 = 49
MOV R7, 135 @87,10000111 = 135

loop:
STR R2, [R6] @store R2 to R6
LSLS R2, R2, #1 @shift bit 1 left
LDR R1, = LEDDELAY

delay1: 
SUBS R1, 1 @count time
BNE delay1
CMP R2, #0x100 @COMPARE R2 with 0x100
BNE loop
CMP R2, #0x100 @ if r2 > 0xFF Clear r2
B loop1 @go to loop1

loop1:
STR R4, [R6] @store R4 to R6
LDR R1, = LEDDELAY

delay3: 
SUBS R1, 1
BNE delay3
B loop2 @go to loop2

loop2:
STR R5, [R6] @store R5 to R6
LDR R1, = LEDDELAY

delay4: 
SUBS R1, 1
BNE delay4
B loop3 @go to loop3

loop3:
STR R7, [R6] @store R7 to R6
LDR R1, = LEDDELAY

delay5: 
SUBS R1, 1
B delay5 
