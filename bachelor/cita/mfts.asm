;00 --- 99
;(538) a:1460h  b:1461h  c:1462h  control:1463h
;(534) a:dcc0h  b:dcc4h  c:dcc8h  control:dccch
;multiple-function-timer-system
;mfts.asm
;Harry Wei <harryxiyou@gmail.com>,Wu YanDe <840794156@qq.com> (ASM) 2012 6
DATA  SEGMENT
TABLE    DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H
         DB 7FH,67H,77H,7CH,39H,5EH,79H,71H
DATA_BUF2    db 00h, 00h ;bit control, NOTE: mem is in the sequence ones
DATA_BUF    db 00h, 00h, 00h, 00h ;bit control
DATA_BUF1    db 00h, 00h, 00h, 00h
PLUS_BUF    db 01h, 00h
DATA  ENDS

CODE  SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX
    MOV  AL, 10001001B   ; a and b is output ones, low 4 bits of c input                                          
    MOV DX, 0DCCCH
    OUT DX, AL
    
    call trivial
    
    ; get condition two bits
    ; 00 is nothing, namely preserved
    ; 01 is now time
    ; 10 is positive timer
    ; 11 is negative timer
BEGIN:
    mov dx, 0dcc8h
    in al, dx
    and al, 03h    
    
    push ax
    mov ah, 1   ; if enter one character, exit
    int 16h
    jnz EXIT
    pop ax                    
    
    cmp al, 00h
    jz BEGIN
    cmp al, 01h
    jz NOW_TIME
    cmp al, 02h
    jz POSITIVE_ONE
    cmp al, 03h
    jz NEGATIVE_ONE
NOW_TIME:
    call get_time
    ;call develop
    jmp BEGIN
POSITIVE_ONE:
    ; postive time module
    ; call positive_time
    call led
    jmp BEGIN
NEGATIVE_ONE:                     
    ;call develop
    call reverse
    jmp BEGIN
    
EXIT:
    MOV AH,4CH 
    INT 21H                     

trivial proc
    mov si, offset DATA_BUF2
    mov dx, 0dcc8h
    in al, dx
    mov bl, al
    shr al, 2
    and al, 0fh
    
    mov [si], al
    inc si
    
    mov al, bl
    shr al, 6
    and al, 03h
    mov [si], al
    
    sub si, 1
    mov al, [si]
    cmp al, 0ah
    jc DO_ONES_RE
    inc si
    mov al, [si]
    add al, 1
    mov [si], al
    mov al, bl
    ret
trivial endp

reverse proc
DO_ONES_RE:
;    cmp al, 0ah
;    jc CON
;    add bl, 10h
;CON: 
        
    call minus
    
    push ax
    mov ah, 1   ; if enter one character, exit
    int 16h
    jnz EXIT
    pop ax
    
    call disp_re

    ;;jmp BEGIN
    ;;jmp BEGIN
    ret
reverse endp
 

disp_re proc
    mov cx, 900h
again_re:
    mov si, offset DATA_BUF2
    mov bl, 0feh
dispnext_re:
    push bx   ; for ds:[bx+al] --> al
    mov al, [si]
    mov bx, offset TABLE
    xlat
    MOV DX,0DCC0H ; A is output one, word control
    OUT DX,AL
    pop bx
    mov al, bl
    MOV DX,0DCC4H ; B is output one, bit control
    OUT DX,AL
    push cx
    mov cx, 0efffh
DELAY1_RE:
    loop DELAY1_RE
    pop cx
    cmp bl, 11111101B  ;bit control
    jz DONE_RE
    inc si
    rol bl, 1
    jmp dispnext_re
DONE_RE:
    DEC cx
    JNZ AGAIN_RE
    ret
disp_re endp

develop proc
    mov dl, 37h
    mov ah, 2
    int 21h
    ret
develop endp

led proc    
    call disp
    

    call plus
    ;jmp BEGIN
    ret
led endp

get_time proc
    mov cx, 01h
time_again:
    mov si, offset DATA_BUF1
    push ax
    push bx
    push cx
    mov ah, 02h
    int 1ah    ; ch:hour, cl:minute
    
    mov bl, cl
    and bl, 0fh
    mov al, bl
    mov [si], al
    inc si
    
    mov bl, cl
    shr bl, 4
    and bl, 0fh
    mov al, bl
    mov [si], al
    inc si
    
    mov bh, ch
    and bh, 0fh
    mov ah, bh
    mov [si], ah
    inc si
    
    mov bh, ch
    shr bh, 4
    and bh, 0fh
    mov ah, bh
    mov [si], ah
    sub si, 3
    pop cx
    pop bx
    pop ax
    mov bl, 0feh
time_dispnext:
    push bx   ; for ds:[bx+al] --> al
    mov al, [si]
    mov bx, offset TABLE
    xlat
    MOV DX,0DCC0H ; A is output one, word control
    OUT DX,AL
    pop bx
    mov al, bl
    MOV DX,0DCC4H ; B is output one, bit control
    OUT DX,AL
    push cx
    mov cx, 0efffh
TIME_DELAY1:
    loop TIME_DELAY1
    pop cx
    cmp bl, 11110111B  ;bit control
    jz TIME_DONE
    inc si
    rol bl, 1
    jmp time_dispnext
TIME_DONE:
    DEC cx
    JNZ time_again
    ret
get_time endp

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
    MOV DX,0DCC0H ; A is output one, word control
    OUT DX,AL
    pop bx
    mov al, bl
    MOV DX,0DCC4H ; B is output one, bit control
    OUT DX,AL
    push cx
    mov cx, 0e000h
DELAY1:
    loop DELAY1
    pop cx
    cmp bl, 11110111B  ;bit control
    jz DONE
    inc si
    rol bl, 1
    jmp dispnext
DONE:
    DEC cx
    JNZ AGAIN
    ret
disp endp
    
minus     proc          
          mov si, 0
          mov cx, 2
          clc
next3_minus:   
          mov al, DATA_BUF2[si]
          sbb al, PLUS_BUF[si]
          aas
          mov DATA_BUF2[si], al
          inc si
          loop next3_minus
          ret
minus     endp 

CODE ENDS
    END START
