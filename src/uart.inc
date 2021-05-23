;;
; @file
; @fn uart_init
; @brief Initializes the UART.
;
; Registers in Bank 0: RCSTA, TXREG
; Registers in Bank 1: TXl, SPBRG, TRISC
;;

uart_init:
; switch to bank 1
        bsf     STATUS, RP0
        bcf     STATUS, RP1
        bsf     TRISB, RX
        bsf     TRISB, TX
        movlw   0x19
        movwf   SPBRG
        bcf     TXSTA, TX9
        bsf     TXSTA, TXEN
        bcf     TXSTA, SYNC
        bsf     TXSTA, BRGH
        bsf     PIE1, RCIE


; switch to bank 0
        bcf     STATUS, RP0
        bcf     STATUS, RP1
        bsf     RCSTA, CREN
        bsf     RCSTA, SPEN
        return

uart_read:
        movf    RCREG, w
        movwf   received_byte
        return

uart_test:
        movlw   SEND_CONTINEOUS
        subwf   received_byte
        btfsc   STATUS, Z
        call    uart_send
        return
        
uart_send:
        movlw   0x28
        movwf   FSR
next_byte:    
        btfss   PIR1, TXIF
        goto    next_byte
        movf    INDF, w
        movwf   TXREG
        incf    FSR, f
        movlw   0x2F
        subwf   FSR, w
        btfss   STATUS, Z
        goto    next_byte
        movlw   WAIT
        movwf   received_byte
return_uart_send:
        return
