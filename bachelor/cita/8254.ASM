; 1440, 1441, 1442, 1443
code segment
	assume cs:code
start:
	mov dx, 1443h
	mov al, 00010000B
	out dx, al
	mov dx, 1440h
	mov al, 06H
	out dx, al
	
	mov ah, 4ch
	int 21h
code ends
	end start