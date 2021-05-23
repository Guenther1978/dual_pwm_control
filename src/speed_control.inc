;;
; @file
; @fn speed_control
; @brief Controls the Speed
;
; This function is called, when an timer oberflow occurs.
; The variable counter is decremented. If zero is reached,
; the counter is set to the duration again and a flag
; is set. Other functions like load_data will can be
; executed than. The used general purpose registers are
; defined in register.inc
;;
speed_control:
        bcf     STATUS, RP0
        bcf     STATUS, RP1
        clrf    sCflag
        decfsz  sCcounter, F
        goto    return_from_speed_control
        movf    sCduration, W
        movwf   sCcounter
        movlw   0xFF
        movwf   sCflag
return_from_speed_control:
        return
