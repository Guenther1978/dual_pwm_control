        ;;
        ;; @file
        ;;

#define  __16F882
#include <p16f882.inc>
	__CONFIG    _CONFIG1, _LVP_OFF & _FCMEN_OFF & _IESO_OFF & _BOR_OFF & _CPD_OFF & _CP_OFF & _MCLRE_ON & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT
	__CONFIG    _CONFIG2, _WRT_OFF & _BOR21V
        
#include "constants.inc"
#include "registers.inc"      

        org 0
        goto      wwcw_control

        org 4

#include "isr_caller.inc"
#include "isr_uart.inc"
#include "isr_timer1.inc"
#include "stop_pwm.inc"
#include "change_pointer.inc"
#include "load_intensity.inc"
#include "send_intensity.inc"
#include "start_pwm.inc"
#include "random16.inc"
#include "speed_control.inc"
#include "new_duration.inc"
#include "new_min_pointer.inc"
#include "new_max_pointer.inc"
#include "uart.inc"


        ;; 
        ; @brief This program controls warm white and cold white led stripes.
        ;
        ; Timer 2 is responsible for the output of PWM signals on RC1 and RC2.
        ; Changing of the duty cycles is done with Timer 1.
        ;; 
wwcw_control:
        bcf       STATUS,RP0          ; Ensure ISR executes in Register Bank 0
        bcf       STATUS,RP1

        #include "timer1Config.inc"
        #include "timer2Config.inc"
        call    random_init
        call    uart_init        

        clrf    darker
        clrf    pointer
        clrf    intensity_high
        clrf    intensity_low
        movlw   MAX
        movwf   pointer_max
        movlw   1
        movwf   pointer_min
        movlw   0x07
        movwf   sCduration
        movwf   sCcounter
	
        ;; enabling PWM mode
	clrf	CCP1CON
	bsf	CCP1CON,CCP1M3
	bsf	CCP1CON,CCP1M2
	clrf	CCP2CON
	bsf	CCP2CON,CCP2M3
	bsf	CCP2CON,CCP2M2

	;; pin 1 and pin 2 are outputs
	bsf	STATUS,RP0
	bcf	TRISC, LED_WW
	bcf	TRISC, LED_CW
	bcf	STATUS,RP0
       
        ;; Clear Data
        clrf    darker
        movlw   LED_WW
        movwf   darker
        movlw   MAX
        movwf   pointer_ww
        movwf   pointer_max
        movlw   MIN
        movwf   pointer_cw
        movwf   pointer_min      

        ;; Enable global interrupts
        bsf     INTCON, GIE
        bsf     INTCON, PEIE

mainloop:
        goto    mainloop

#include "intensities_high.inc"
#include "intensities_low.inc"
        
        end
