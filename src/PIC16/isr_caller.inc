;;
; @file
; @fn isr_caller
; @brief This ISR calls the interrupt handlers
;;

isr_handler:
        movwf   w_temp
        swapf   STATUS, w
        bcf     STATUS, RP0
        bcf     STATUS, RP1
        movwf   status_temp
        
        btfsc   PIR1, RCIF
        call    isr_uart
 
        btfsc   PIR1, TMR1IF
        call    isr_timer_1

Exit_ISR:
        swapf   status_temp,w       ; Restore context
        movwf   STATUS
        swapf   w_temp,f            ; swapf doesn't affect Status bits, but MOVF would
        swapf   w_temp,w
        retfie

