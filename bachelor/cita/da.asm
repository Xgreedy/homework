code segment
assume cs:code
start:
	mov dx, 1400h
	mov al, 00h
next:
	out dx, al
	dec al
	call delay
	push ax
	mov ah, 1
	int 16h
	jnz exit
	pop ax
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