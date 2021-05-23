;;
; @file
; @fn start_pwm
; @brief Starts the pwm output
;
; The pwm output has to be restarted after each change of the duty cycle.
;;

start_pwm:
        bsf     STATUS, RP0
        bcf     TRISB, LED
        bcf     STATUS, RP0
        clrf    PIR1
    
        bsf CCP1CON,CCP1M3
        bsf CCP1CON,CCP1M2
    
        bsf     T2CON, TMR2ON
PWM_Period_Match:
        btfss   PIR1, TMR2IF
        goto    PWM_Period_Match
        bcf     PIR1, TMR2IF

        return

