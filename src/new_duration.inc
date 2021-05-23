;;
; @file
; @fn new_duration
; @brief Calculates a new duration
;
; After changing from decreasing to increasing or
; from changing from increasing to decreasing a new
; duration is choosen to change the intensity of the
; LED slowier of faster.
;;

new_duration:
        call    random16
        movf    RandLo, w
        andlw   0x07
        addlw   0x01
        movwf   sCduration
        return

