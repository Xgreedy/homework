CODE SEGMENT
	ASSUME CS:CODE
START:
	MOV DX, 1463H
	MOV AL, 10000010B
	OUT DX, AL
READ:
	MOV DX, 1461H
	IN AL, DX
	MOV DX, 1460H
	OUT DX, AL
	JMP READ

	MOV AL, 4CH	
	INT 21H

CODE ENDS
	END START