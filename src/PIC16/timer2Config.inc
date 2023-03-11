;;
; @file
; @brief This macro initializes timer 2
;
; Timer 2 is reponsible for the PWM generation in collaboration
; with the capture compare units.
;;

;;
; @def init_timer_2
;;

init_timer_2:
        ; Register Bank 0
        bcf       STATUS,RP0
        bcf       STATUS,RP1

        ; Configure and Start timer 2
        bsf     STATUS, RP0
        movlw   0xFF
        movwf   PR2
        bcf     PIE1, TMR2IE
        bcf     STATUS, RP0
        bsf     T2CON, TMR2ON

