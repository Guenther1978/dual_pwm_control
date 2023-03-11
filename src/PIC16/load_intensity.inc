load_intensity:
    movf    pointer, w
    movwf   offset
    movlw   LOW(table_high)
    addwf   offset, F
    movlw   HIGH(table_high)
    btfsc   STATUS, C
    addlw   0x01
    movwf   PCLATH
    movf    offset, w
    btfsc   STATUS, Z
    incf    offset, w
    call    table_high
    movwf   intensity_high

    movf    pointer, w
    movwf   offset
    movlw   LOW(table_low)
    addwf   offset, F
    movlw   HIGH(table_low)
    btfsc   STATUS, C
    addlw   0x01
    movwf   PCLATH
    movf    offset, w
    btfsc   STATUS, Z
    incf    offset, w
    call    table_low
    movwf   intensity_low

    return

