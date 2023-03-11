;;
; change_pointer
;;
change_pointer:
        movf    led, w
        andlw   LED_WW
        btfsc   STATUS, Z
        goto    change_led_cw
        movf    darker, w
        andwf   led, w
        btfss   STATUS, Z
        goto    dim_led 
        incf    pointer, f
        incf    pointer, w
        subwf   pointer_max, w
        btfsc   STATUS, C
        goto    return_change_pointer
        movf    led, w
        iorwf   darker, f
        call    new_duration
        call    new_min_pointer
        goto    return_change_pointer
dim_led:
        decf    pointer, f
        decf    pointer, w
        subwf   pointer_min, w
        btfss   STATUS, Z
        goto    return_change_pointer
        comf    led, w
        andwf   darker, f
        call    new_duration
        call    new_max_pointer
        goto    return_change_pointer
change_led_cw:
        movf    pointer_ww, w   
        sublw   MAX
        movwf   pointer
return_change_pointer:
        return
