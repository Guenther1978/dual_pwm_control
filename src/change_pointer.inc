;;
; change_intensity
;;
change_intensity:
        movf    darker, w
        andwf   led, w
        btfss   STATUS, Z
        goto    dim_led 
        incf    pointer, f
        movlw   MAX
        subwf   pointer, w
        btfss   STATUS, Z
        goto    change_intensity_return
        movf    led, w
        iorwf   darker, f
        goto    change_intensity_return
dim_led:
        decf    pointer, f
        btfss   STATUS, Z
        goto    change_intensity_return
        comf    led, w
        andwf   darker, f
change_intensity_return:
        return
