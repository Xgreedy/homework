;定义基地址寄存器地址
INTCSR_BYTE0   EQU  1838H
INTCSR_BYTE1   EQU  1839H
INTCSR_BYTE2   EQU  183AH
INTCSR_BYTE3   EQU  183BH
IMB4_BYTE3     EQU   181FH

;数据段定义
DATA SEGMENT
	KEEP_CS DW 0
	KEEP_IP	DW 0
	OLD_IMR1 DB 0
	OLD_IMR2 DB 0
	INT_SEG  DW ?
	INT_OFF  DW ?
        STAA DB 'This is a Interruption Service Program !',13,10,'$'
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE,DS:DATA	
START PROC FAR
BEGIN:	PUSH DS
	MOV AX,0
	PUSH AX
	CLI		;关中断
	MOV AX,DATA
	MOV DS,AX

;初始化PCI寄存器
	MOV DX,INTCSR_BYTE0
	MOV AL,00H
	OUT DX,AL
	MOV DX,INTCSR_BYTE1
	MOV AL,1FH
	OUT DX,AL
	MOV DX,INTCSR_BYTE2
	MOV AL,3FH
	OUT DX,AL
	MOV DX,INTCSR_BYTE3
	MOV AL,00H
	OUT DX,AL
;替换中断服务程序入口地址
MOV AL, 73h
MOV AH, 35H
INT 21H   ;获取中断向量
MOV AX, ES
MOV INT_SEG, AX
MOV INT_OFF, BX

;根据中断类型号73H将中断向量置入中断向量表中（自己完成）
push ds
CLI
MOV AL, 73h
MOV AH, 25H
MOV DX, SEG MYINIT
MOV DS, DX
MOV DX, OFFSET MYINIT
INT 21H
pop ds
; 设置IMR

in al, 21h ;This is main 8259a
mov OLD_IMR1, al
and al, 00000000B ;keep all the irqs
out 21h, al

in al, 0a1h ; this is slave one
mov OLD_IMR2, al
and al, 00000000B 
out 0a1h, al
; 将从片8259A的原来IMR保存到OLD_IMR变量中，再将对应的IRQ3位开中断（自己完成）
        STI			;开中断	
       	MOV CX,5
LOOP1:	CMP CX,0
	JNE LOOP1
	CLI			;关中断	

mov al, OLD_IMR1
out 21h, al

mov al, OLD_IMR2
out 0a1h, al

;设置IMR（自己完成）
;恢复原来的中断向量表的内容（自己完成）

CLI    ;恢复中断向量前关中断
MOV AL, 73h
MOV AH, 25H
MOV DX, INT_OFF
MOV BX, INT_SEG
MOV DS, BX
INT 21H

        MOV     DX,INTCSR_BYTE1	;
       	MOV     AL,00H
       	OUT     DX,AL
	STI			;开中断
	RET
START ENDP

MYINIT PROC NEAR
	PUSH DS
	PUSH AX
	PUSH DX

	;显示信息
	MOV DX,OFFSET STAA
	MOV AH,9
	INT 21H
	DEC CX

;清PCI板中的中断
        MOV DX,IMB4_BYTE3
        IN  AL,DX
        MOV DX,INTCSR_BYTE2
        MOV AL,3FH
        OUT DX,AL
       
;清8259A中的中断标志，先清从片再清主片	
        MOV AL,20H
        OUT 0A0H,AL
        OUT 20H,AL
        POP DX
        POP AX                                            
        POP DS
        IRET
MYINIT ENDP

CODE	ENDS
	END BEGIN
