	BITS 32
	section .text isr

	extern ?Count@KeyboardDriver@@2EC
	global ?KeyboardISR@KeyboardDriver@@SAXXZ

	?KeyboardISR@KeyboardDriver@@SAXXZ:

	INC BYTE [?Count@KeyboardDriver@@2EC]
	
	PUSH ax

	; Read data byte from keyboard controller
	MOV al, 0xD0
	OUT 0x64, al
	
	IN al, 0x60
	
	; Clear EOI in pic
	MOV al, 0x20
	OUT 0x20, al
		
	POP ax

	IRETD

