;;
; @file
; @fn stop_pwm
; @brief stops the pwm output
;
; If the duty cycle of the pwm should be changed, the capture compare
; module has to stop first.
;;

stop_pwm:
        bsf     STATUS, RP0
        bsf     TRISB, LED_WW
        bsf     TRISB, LED_CW
        bcf     STATUS, RP0
        clrf    CCP1CON
        clrf    CCP2CON

        return

