;;
; @file
; @fn isr_timer1
; @brief This is the timer 1 interupt handler.
;
; The routine deals with the timer 1
; overflow interrupt, the intensities
; are decreased or increased
;;

isr_timer_1:
        call    speed_control
        btfss   sCflag, LED_WW
        goto    exit_isr_timer_1
        
        call    stop_pwm
        movlw   LED_WW
        movwf   led
        movf    pointer_ww, W
        movwf   pointer
        call    change_pointer
        movf    pointer, W
        movwf   pointer_ww
        call    load_intensity
        movf    intensity_high, W
        movwf   intensity_ww_high
        movf    intensity_low, W
        movwf   intensity_ww_low

        movlw   LED_CW
        movwf   led
        movf    pointer_cw, W
        movwf   pointer
        call    change_pointer
        movf    pointer, W
        movwf   pointer_cw
        call    load_intensity
        movf    intensity_high, W
        movwf   intensity_cw_high
        movf    intensity_low, W
        movwf   intensity_cw_low

        call    send_intensity
        call    start_pwm

exit_isr_timer_1:
        bcf     PIR1, TMR1IF
        return
