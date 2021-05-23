send_intensity:
    movf    intensity_high, w
    movwf   CCPR1L
    btfsc   intensity_low, 1
    bsf     CCP1CON, CCP1Y
    btfsc   intensity_low, 0
    bsf     CCP1CON, CCP1X

    return

