;;
; change_pointer
;;
change_pointer:
        movf    darker, w
        andwf   led, w
        btfss   STATUS, Z
        goto    dim_led 
        incf    pointer_ww, f
        movlw   MAX
        subwf   pointer_ww, w
        btfss   STATUS, Z
        goto    change_intensity_return
        movf    led, w
        iorwf   darker, f
        goto    change_intensity_return
dim_led:
        decf    pointer_ww, f
        btfss   STATUS, Z
        goto    change_intensity_return
        comf    led, w
        andwf   darker, f
change_intensity_return:
        movf    pointer_ww, w
        subwf   SIZE / 2
        movwf   pointer_cw
        return
