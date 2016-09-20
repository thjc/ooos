	org 0x91000

	section .text kernel
	bits 32
;--------------------------
; Kernel code ....
;-------------------------
kernel:
	mov ax, 0x10	; set up data segment
	mov ds, ax
	mov es, ax	

	mov ss, ax	; and stack segment
	mov eax, 0x80000
	mov esp, eax	; and stack pointer

	cld

        mov esi, msginpmode
	mov ah, 04
	call write_string
	;call 0x90200

infinity:
	nop
	jmp infinity


;--------------------------
; call to write a string to video memory
;--------------------------
write_string:
	mov edi, 0xb8000
	
loop_write:
        lodsb                   ; load byte at ds:si into al
        or al,al                ; test if character is 0 (end)
        jz done_write;
	stosw
;	mov [ebx], ax
        jmp loop_write
done_write:
        ret		


;write_string:
;	mov ebx, msginpmode + 0x7c00
;	mov edx, 0xb8000
	
;loop_write:
        ;lodsb                   ; load byte at ds:si into al
;	mov al, [ebx]
;        or al,al                ; test if character is 0 (end)
;        jz done_write
;	add ebx, 1
;	mov [edx], ax
;	add edx, 2
;	stosw
;	mov [ebx], ax
;        jmp loop_write
;done_write:
;        ret		



;-----------------------
; kernel data
;-----------------------
	msginpmode	db 'We are in PMode',10,0



; this doesnt have to be 512 bytes, but it makes life easier for writing to disk
        times 512-($-$$) db 0
        ;dw 0xAA55


