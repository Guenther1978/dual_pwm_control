;;
; @file
; @brief This macro initializes timer 1
;
; Timer 1 is reponsible for the change of the intensities.
; T1CKPS<1:0>: 11 -> 1:8, 10 -> 1:4, 01 -> 1:2, 00 -> 1:1
;;

;;
; @def init_timer_1
;;

init_timer_1:
        ; Register Bank 0
        bcf       STATUS,RP0
        bcf       STATUS,RP1

        ; Configure and start timer 1
        bcf     T1CON, T1CKPS1
        bsf     T1CON, T1CKPS0
        bsf     STATUS, RP0
        bsf     PIE1, TMR1IE
        bcf     STATUS, RP0
        bsf     T1CON, TMR1ON

