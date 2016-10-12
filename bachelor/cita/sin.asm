data segment
	SIN	db 80h, 96h, 0aeh, 0c5h, 0d8h, 0e9h, 0f5h, 0fdh, 0ffh, 0fdh, 0f5h, 0e9h, 0d8h, 0c5h, 0aeh, 96h, 80h, 66h, 4eh, 38h, 25h, 15h, 09h, 04h, 00h, 04h, 09h, 15h, 25h, 38h, 4eh, 66h
data ends
code segment
assume cs:code, ds:data
start:
	mov ax, data
	mov ds, ax
	mov dx, 1400h
again:
	mov si, offset SIN
	mov cl, 20h
next:
	mov al, [si]
	out dx, al
	call delay
	dec cl
	inc si
	cmp cl, 00h
	jz again
	mov ah, 1
	int 16h
	jnz exit
	jmp next
exit:	
	mov ah, 4ch
	int 21h
	
delay proc
	push ax
	push cx
	push dx
	mov cx, 10000
delay1:
	loop delay1
	pop dx
	pop cx
	pop ax
	ret
	delay endp 
code ends
	end start 