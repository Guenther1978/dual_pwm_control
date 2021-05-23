;;
; @file
; @fn new_max_pointer
; @brief Calculates a new duration
;
; After changing from decreasing to increasing
; a new maximal pointer is calculated. The high
; byte of the pseudo random generator is added
; to the minimal pointer.
; And if no overflow occured, this sum is the
; new maximal pointer.
;;

new_max_pointer:
        call    random16
        movf    RandHi, W
        subwf   pointer_min, W
        btfsc   STATUS, C
        goto    return_new_max_pointer
        movwf   pointer_max
return_new_max_pointer:
        return

