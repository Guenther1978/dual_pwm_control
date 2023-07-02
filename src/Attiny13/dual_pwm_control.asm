;
; dual_pwm_control.asm
;
; Created: 25.06.2023 11:15:47
; Author : guent
;



	#include <tn13Adef.inc>


	.def	aux = r16
	.def	isr_save = r17
	.def	memory = r0
	.equ	warmwhite = 0
	.equ	coldwhite = 1
	.def	pointer = r18
	.def	darker = r19
	.def	counter = r4
	.def	duration = r5
	.def	interrupts = r6

 	rjmp	RESET
	reti						; EXT_INT0
	reti						; PCINT0
	rjmp	ISR_TIM0_OVF		; Timer0 Overflow Handler
	reti						; EE_RDY
	reti						; ANA_COMP
	reti						; TIM0_COMPA
	reti						; TIMO_COMPB
	reti						; WATCHDOG
	reti						; ADC
	;;
RESET:
	ldi		aux, low(RAMEND)
	out		SPL, aux
	;; Initialize PWM Ports loop:
	sbi		DDRB, 0
	sbi		DDRB, 1
	;; Initialize pointer
	ldi		aux, 0
	mov		pointer, aux
	mov		darker, aux
	mov		interrupts, aux
	;; Initialize Timer
	ldi		aux, 0xA3
	out		TCCR0A, aux
	ldi		aux, 2
	out		TCCR0B, aux
	ldi		aux, 2
	out		TCCR0B, aux
	;; Enable Timer Overflow Interrupt
	ldi		aux, 2
	out		TIMSK0, aux
	ldi		aux, 55
	out		OCR0A, aux
	ldi		aux, 200
	out		OCR0B, aux
	sei
loop:
	rjmp	loop

ISR_TIM0_OVF:
	in		isr_save, SREG
	inc		interrupts
	brvc	isr_return
	cpi		darker, 255 
	brbs	1, decrease_pointer
	inc		pointer
	cpi		pointer, 255
	brbc	1, load_intensity
	ser		darker
	rjmp	load_intensity
decrease_pointer:
	dec		pointer
	cpi		pointer, 0
	brbc	1, load_intensity
	clr		darker
load_intensity:
	mov		aux, pointer
	ldi		ZH, high(2 * intensity_table)
	ldi		ZL, low(2 * intensity_table)
	add		ZL, pointer
	brvc	carry_clear_1
	inc		ZH
carry_clear_1:
	lpm
	mov		aux, memory
	out		OCR0A, aux
	com		aux
	mov		aux, pointer
	ldi		ZH, high(2 * intensity_table)
	ldi		ZL, low(2 * intensity_table)
	add		ZL, pointer
	brvc	carry_clear_2
	inc		ZH
carry_clear_2:
	lpm		
	mov		aux, memory
	out		OCR0B, aux

isr_return:
	out		SREG, isr_save
	reti

intensity_table:
	#include "intensities.inc"
