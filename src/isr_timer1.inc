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
        btfss   sCflag, LED
        goto    exit_isr_timer_1
        
        call    stop_pwm
        call    change_pointer
        call    load_intensity
        call    send_intensity
        call    start_pwm
        call    uart_test

exit_isr_timer_1:
        return
