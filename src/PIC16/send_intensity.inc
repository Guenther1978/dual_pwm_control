send_intensity:
    movf    intensity_ww_high, w
    movwf   CCPR1L
    btfsc   intensity_ww_low, 1
    bsf     CCP1CON, DC1B1
    btfsc   intensity_ww_low, 0
    bsf     CCP1CON, DC1B0
    movf    intensity_cw_high, w
    movwf   CCPR2L
    btfsc   intensity_cw_low, 1
    bsf     CCP1CON, DC2B1
    btfsc   intensity_cw_low, 0
    bsf     CCP1CON, DC2B0

    return

