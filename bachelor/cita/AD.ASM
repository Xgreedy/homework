; 1440 -- 145f
code segment
	assume cs:code
start:
again:
	mov dx, 1440h	; port IN0
	mov al, 88h
	out dx, al		; begin ad, it is none of al business
	mov bx, 65535
wt:		
	dec bx			; delay time 100us
	jnz wt
	in al, dx		; read a data
	
	
	mov cl, 4		; shift right bits
;	mov al, 00h
;	add al, 1
	mov bl, al		
	and al, 0f0h		; high 4 bits
	shr al, 4
	add al, 30h			; 2 ascii (0--9)
	cmp al, 3ah			; 2 ascii (a--f)
	jc trans1
	add al, 07h
trans1:
;	push dx
	mov dl, al		; bug here
	mov ah, 2
	int 21h
	
	mov al, bl		
	and al, 00fh	; high 4 bits
	add al, 30h
	cmp al, 3ah
	jc trans2
	add al, 07h
trans2:
	mov dl, al		; bug here
	mov ah, 2
	int 21h
	
	mov dl, 0ah		; enter 
	mov ah, 2
	int 21h
	mov dl, 0dh		; another line
	mov ah, 2
	int 21h
	
;	mov ah, 1		; check character enter
;	int 16h
;	jnz exit
;	pop dx
	jmp again
	
exit:				; exit this application
	mov ah, 4ch
	int 21h
code ends
	end start