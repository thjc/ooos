	BITS 32
	section .text isr

	;extern ?Count@KeyboardDriver@@2EC
	;extern ?Tail@KeyboardDriver@@0EC
	;extern ?Head@KeyboardDriver@@0EC
	;extern ?Buffer@KeyboardDriver@@0RC_WC
	
	extern ?KeyboardISR@KeyboardDriver@@SAXXZ
	extern ?TimerISR@TimerDriver@@SAXXZ
	extern ?Exception13_CPP@@YAXXZ
	extern ?Exception10_CPP@@YAXXZ
	extern ?pDump@@3PAXA
	
	global ?RawISR@KeyboardDriver@@SAXXZ
	global ?RawISR@TimerDriver@@SAXXZ
	
	global ?Exception0@@YAXXZ
	
	?Exception0@@YAXXZ
	
	MOV Al, 0 + 48
	MOV [0xB8000], al
	
	TempLab0:
	JMP TempLab0
	
	global ?Exception1@@YAXXZ
	
	?Exception1@@YAXXZ
	
	MOV Al, 1 + 48
	MOV [0xB8000], al
	
	TempLab1:
	JMP TempLab1
	
	global ?Exception2@@YAXXZ
	
	?Exception2@@YAXXZ
	
	MOV Al, 2 + 48
	MOV [0xB8000], al
	
	TempLab2:
	JMP TempLab2
	
	global ?Exception3@@YAXXZ
	
	?Exception3@@YAXXZ
	
	MOV Al, 3 + 48
	MOV [0xB8000], al
	
	TempLab3:
	JMP TempLab3
	
	global ?Exception4@@YAXXZ
	
	?Exception4@@YAXXZ
	
	MOV Al, 4 + 48
	MOV [0xB8000], al
	
	TempLab4:
	JMP TempLab4
	
	global ?Exception5@@YAXXZ
	
	?Exception5@@YAXXZ
	
	MOV Al, 5 + 48
	MOV [0xB8000], al
	
	TempLab5:
	JMP TempLab5
	
	global ?Exception6@@YAXXZ
	
	?Exception6@@YAXXZ
	
	MOV Al, 6 + 48
	MOV [0xB8000], al
	
	TempLab6:
	JMP TempLab6
	
	global ?Exception7@@YAXXZ
	
	?Exception7@@YAXXZ
	
	MOV Al, 7 + 48
	MOV [0xB8000], al
	
	TempLab7:
	JMP TempLab7
	
	global ?Exception8@@YAXXZ
	
	?Exception8@@YAXXZ
	
	MOV Al, 8 + 48
	MOV [0xB8000], al
	
	TempLab8:
	JMP TempLab8
	
	global ?Exception9@@YAXXZ
	
	?Exception9@@YAXXZ
	
	MOV Al, 9 + 48
	MOV [0xB8000], al
	
	TempLab9:
	JMP TempLab9
	
	global ?Exception10@@YAXXZ
	
	?Exception10@@YAXXZ
	PUSH EAX
	MOV EAX, [?pDump@@3PAXA]
	MOV [EAX+4], EBX
	POP EAX

	MOV EBX, [?pDump@@3PAXA]
	MOV [EBX], EAX
	MOV [EBX+8], ECX
	MOV [EBX+12], EDX
	MOV [EBX+16], EDI
	MOV [EBX+20], ESI
	MOV [EBX+24], EBP
	MOV [EBX+28], ESP
	MOV EAX, [ESP]
	MOV [EBX+32], EAX
	MOV EAX, [ESP+4]
	MOV [EBX+36], EAX
	MOV EAX, [ESP+8]
	MOV [EBX+40], EAX
	MOV EAX, [ESP+12]
	MOV [EBX+44], EAX

	
	call ?Exception10_CPP@@YAXXZ	
	;MOV Al, 10 + 48
	;MOV [0xB8000], al

	;TempLab10:
	;JMP TempLab10
	IRET
	
	global ?Exception11@@YAXXZ
	
	?Exception11@@YAXXZ
	
	MOV Al, 11 + 48
	MOV [0xB8000], al
	
	TempLab11:
	JMP TempLab11
	
	global ?Exception12@@YAXXZ
	
	?Exception12@@YAXXZ
	
	MOV Al, 12 + 48
	MOV [0xB8000], al
	
	TempLab12:
	JMP TempLab12
	
;Store:  RESD 1
	
	global ?Exception13@@YAXXZ
	
	?Exception13@@YAXXZ
	
	PUSH EAX
	MOV EAX, [?pDump@@3PAXA]
	MOV [EAX+4], EBX
	POP EAX

	MOV EBX, [?pDump@@3PAXA]
	MOV [EBX], EAX
	MOV [EBX+8], ECX
	MOV [EBX+12], EDX
	MOV [EBX+16], EDI
	MOV [EBX+20], ESI
	MOV [EBX+24], EBP
	MOV [EBX+28], ESP
	MOV EAX, [ESP]
	MOV [EBX+32], EAX
	MOV EAX, [ESP+4]
	MOV [EBX+36], EAX
	MOV EAX, [ESP+8]
	MOV [EBX+40], EAX
	MOV EAX, [ESP+12]
	MOV [EBX+44], EAX

	
	call ?Exception13_CPP@@YAXXZ
	
	;MOV Al, 13 + 48
	;MOV [0xB8000], al
	
	;TempLab13:
	;JMP TempLab13
	IRET
	
	global ?Exception14@@YAXXZ
	
	?Exception14@@YAXXZ
	
	MOV Al, 14 + 48
	MOV [0xB8000], al
	
	TempLab14:
	JMP TempLab14
	
	
	
	
	;global ?Exception@@YAXXZ


	;?Exception@@YAXXZ:
	
	;MOV EAX, ip
	;MOV [0xB8000], EAX
	
	;TempLab:
	;JMP TempLab

	?RawISR@KeyboardDriver@@SAXXZ:

	;INC BYTE [?Count@KeyboardDriver@@2EC]
	
	PUSH ax
	call ?KeyboardISR@KeyboardDriver@@SAXXZ
	

	; Read data byte from keyboard controller
	;MOV al, 0xD0
	;OUT 0x64, al
	
	;IN al, 0x60

	; Read KeyStroke from Keyboard Controller (Clears Interrupt flag on controller)
	;IN al, 0x60
	

	; Clear EOI in pic
	MOV al, 0x20
	OUT 0x20, al
		
	POP ax

	IRETD



	?RawISR@TimerDriver@@SAXXZ:
	;CLI
	call ?TimerISR@TimerDriver@@SAXXZ

	PUSH ax


	; Clear EOI in pic
	MOV al, 0x20
	OUT 0x20, al
	
		
	POP ax
	IRETD
	JMP ?RawISR@TimerDriver@@SAXXZ

	
	
	