;;
; Load data
;;
load_data:
    movlw       LOW (table_high)
    addwf       pointer_sub_high, F
    movlw       HIGH (table_high)
    btfsc       STATUS, C
    addlw       1
    movwf       PCLATH
    movf        pointer_sub_high, w
    call        table_high
    movwf       intensity_high
    movlw       LOW (table_low)
    addwf       pointer_sub_low, F
    movlw       HIGH (table_low)
    btfsc       STATUS, C
    addlw       1
    movwf       PCLATH
    movf        pointer_sub_low, w
    call        table_low
    movwf       intensity_low
    return
