
.include x86_16b.inc
.include IBM_PC.inc

.=0x7C00

; Set segment registers and stack.

MOV( AX, IM16( 0 ) )
MOV( DS, AX )
MOV( ES, AX )
CLI()
MOV( SS, AX )
MOV( SP, IM16( 0x7BFE ) )
STI()

; display string.

MOV( AX, IM16( 0x1300 ) )             ; service code (13h) and write mode.
MOV( BX, IM16( 0x0047 ) )             ; video page (0) and attribute byte.
MOV( CX, IM16( msg1_length ) )        ; message length.
MOV( DX, IM16( 0 ) )                  ; row and column.
MOV( BP, IM16( msg1 ) )
INT( 0x10 )                           ; call BIOS video service interrupt.


MOV( AX, IM16( 0xB800 ) )
MOV( DS, AX )
MOV( AT_DISP16( 0 ), IM16( ( ATTRIBUTE( light_cyan, green ) << 8 ) + 'H' ) )

wfe:                                  ; loop forever.
JMP(wfe)

msg1:

"Hi from below again!"

end_msg1:

msg1_length = end_msg1 - msg1

FILL_UNTIL( (0x7C00 + 510), 42)

0x55 0xAA

; INT 10H service used here:

; AH = 13h
; AL = write mode
;   bit 0:
;   Update cursor after writing
;   bit 1:
;   String contains alternating characters and attributes
;   bits 2-7:
; BH = page number.
; BL = attribute if string contains only characters.
; CX = number of characters in string.
; DH,DL = row,column at which to start writing.
; ES:BP -> string to write
