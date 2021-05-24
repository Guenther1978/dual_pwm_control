;;
; @brief This file contains registeres used as variables
;;

        cblock 0x20
status_temp         ; 0x20
w_temp              ; 0x21
led                 ; 0x22
darker              ; 0x23
intensity_high      ; 0x24
intensity_low       ; 0x25
intensity_ww_high   ; 0x26
intensity_ww_low    ; 0x27
intensity_cw_high   ; 0x28
intensity_cw_low    ; 0x29
pointer             ; 0x2a
pointer_ww          ; 0x2b
pointer_cw          ; 0x2c
pointer_sub_high    ; 0x2d
pointer_sub_low     ; 0x2e
sCcounter           ; 0x2f
sCduration          ; 0x30
sCflag              ; 0x31
RandHi              ; 0x32
RandLo              ; 0x33
received_byte       ; 0x34
pointer_min         ; 0x35
pointer_max         ; 0x36
offset              ; 0x37
        endc
