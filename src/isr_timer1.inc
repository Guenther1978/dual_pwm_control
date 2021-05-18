;;
; @file
; @fn isr_timer1
; @brief This is the timer 1 interupt handler.
;
; The routine deals with the timer 1
; overflow interrupt, the intensities
; are decreased or increased
;;
isr_timer1:
        movwf   w_temp
        swapf   STATUS,w
        bcf     STATUS,RP0
        bcf     STATUS,RP1
        movwf   status_temp

        bsf     PORTC, INT_MARKER
        
        btfsc   PIR1,TMR1IF
        goto    handle_isr_timer_1
        goto    Exit_ISR

handle_isr_timer_1:
;        bsf     STATUS, RP0
;        bsf     TRISC, LED_WW
        bsf     TRISC, LED_CW
        bcf     STATUS, RP0
        clrf    CCP1CON
        clrf    CCP2CON
        
        movlw   LED_WW
        movwf   led
        movf    pointer_ww, w
        movwf   pointer
        call    change_intensity
        movf    pointer, w
        movwf   pointer_ww
        movwf	pointer_sub_high
        incf    pointer_sub_high, f
        movf	pointer, w
        movwf	pointer_sub_low
        incf    pointer_sub_low, f

        call    load_data
        movf    intensity_high, w
        movwf   intensity_ww_high
        movf    intensity_low, w
        movwf   intensity_ww_low

        movlw   LED_CW
        movwf   led
        movf    pointer_cw, w
        movwf   pointer
        call    change_intensity
        movf    pointer, w
        movwf   pointer_cw
        movwf	pointer_sub_high
        incf    pointer_sub_high, f
        movf	pointer, w
        movwf	pointer_sub_low
        incf    pointer_sub_low, f
        
        call    load_data
        movf    intensity_high, w
        movwf   intensity_cw_high
        movf    intensity_low, w
        movwf   intensity_cw_low

        movf    intensity_ww_high, w
        movwf   CCPR1L
        btfsc   intensity_ww_low, 1
        bsf     CCP1CON, DC1B1
        btfsc   intensity_ww_low, 0
        bsf     CCP1CON, DC1B0

        movf    intensity_cw_high, w
        movwf   CCPR2L
        btfsc   intensity_cw_low, 1
        bsf     CCP2CON, DC2B1
        btfsc   intensity_cw_low, 0
        bsf     CCP2CON, DC2B0

        bsf     STATUS, RP0
        bcf     TRISC, LED_WW
        bcf     TRISC, LED_CW
        bcf     STATUS, RP0
        clrf    PIR1

	bsf	CCP1CON,CCP1M3
	bsf	CCP1CON,CCP1M2
	bsf	CCP2CON,CCP2M3
	bsf	CCP2CON,CCP2M2

        bsf     T2CON, TMR2ON
PWM_Period_Match:
        btfss   PIR1, TMR2IF
        goto    PWM_Period_Match
        bcf     PIR1, TMR2IF
Exit_ISR:
        bcf     PORTC, INT_MARKER
        swapf   status_temp,w       ; Restore context
        movwf   STATUS
        swapf   w_temp,f            ; swapf doesn't affect Status bits, but MOVF would
        swapf   w_temp,w
        retfie
