;data segment
;data ends
; 1460h, 1461h, 1462h, 1463h
CODE SEGMENT
	ASSUME CS:CODE
start:
	;mov ax, data
	;mov ds, ax
	; init control port
	mov dx, 1463h
	mov al, 10000010B
	out dx, al
	
READ:
	mov dx, 1461h ;B is input one
	in al, dx
	mov dx, 1460h ;A is output one
	out dx, al
	mov ah, 1
	int 16h
	jnz EXIT
	JMP READ

EXIT:
	mov ah, 4ch
	int 21h
code ends
	end start