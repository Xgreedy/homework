;00 --- 99
; a:1460h  b:1461h  c:1462h  control:1463h
DATA  SEGMENT
TABLE    DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H
         DB 7FH,67H,77H,7CH,39H,5EH,79H,71H
DATA_BUF	db 00h, 00h ;bit control
PLUS_BUF	db 01h, 00h
DATA  ENDS

CODE  SEGMENT
ASSUME CS:CODE, DS:DATA

START:
	MOV AX, DATA
	MOV DS, AX
	MOV  AL, 10000000B   ; a and b is output ones                                          
	MOV DX, 1463H
	OUT DX, AL                       

DO_ONES:	
	call disp
	
	mov ah, 1   ; if enter one character, exit
	int 16h
	jnz EXIT

	call plus
	jmp DO_ONES
EXIT:
	MOV AH,4CH 
	INT 21H
	
plus     proc          
          mov si, 0
          mov cx, 4
          clc
next3:   mov al, DATA_BUF[si]
          adc al, PLUS_BUF[si]
          aaa
          mov DATA_BUF[si], al
          inc si
          loop next3
          ret
plus     endp  

disp proc
	mov cx, 900h
again:
	mov si, offset DATA_BUF
	mov bl, 0feh
dispnext:
	push bx   ; for ds:[bx+al] --> al
	mov al, [si]
	mov bx, offset TABLE
	xlat
	MOV DX,1460H ; A is output one, word control
	OUT DX,AL
	pop bx
	mov al, bl
	MOV DX,1461H ; B is output one, bit control
	OUT DX,AL
	push cx
	mov cx, 0e000h
DELAY1:
	loop DELAY1
	pop cx
	cmp bl, 11111101B
	jz DONE
	inc si
	rol bl, 1
	jmp dispnext
DONE:
	DEC cx
	JNZ AGAIN
	ret
disp endp
CODE ENDS
	END START 