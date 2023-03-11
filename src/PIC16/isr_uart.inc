;;
; @file
; @fn isr_uart
; @brief This is the receive interrupt handler.
;;

isr_uart:
        movf    RCREG, W
        movwf   received_byte
        movf    received_byte, W
        subwf   SEND_SINGLE
        btfsc   STATUS, Z
        call    uart_send
        return

