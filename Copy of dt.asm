; interrupt and global discriptor tables
	
	org 0x100

; -----------------
;  IDT
; -----------------

; first one is div zero error #de

	dw 0


	; pack it out to full size
    times 0x7ff-($-$$) db 0


; -----------------
;  GDT
; -----------------

    times 0x17ff+0x7ff-($-$$) db 0

	


