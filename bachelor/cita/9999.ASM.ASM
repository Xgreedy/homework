porta equ 1440h
portb equ 1441h
portcontrol equ 1443h

data  segment
	ledbuf      db   3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh ;����
	datbuf      db   00h,00h,00h,00h         ;���Ҫ��ʾ4λ
	plus        db   01h, 00h, 00h,00h   
data ends

code  segment
	assume cs:code,ds:data
start:  mov ax,data
	    mov ds,ax

        mov dx,portcontrol                  ;��8255��ΪA\B�������AΪ���������BΪλ�����
	    mov al,10000000B
	    out dx,al


dispnew:  call disp                    ;disp�ȶ�����ʾ������������
     
        mov dx, 0ffh                  ;�жϼ����Ƿ��м����£��м������Ƴ�����
        mov ah, 06h
        int 21h
        jnz exit 
               
        call plus1
        jmp dispnew

exit:   mov dx,portb
	    mov al,0ffh                    ;�ص��������ʾ
	    out dx,al
	    mov ah,4ch                  ;����DOS
	    int 21h

disp proc                          ;��������databuf�е������ȶ���ʾ     
          mov cx, 900h
again:    mov si, offset datbuf
          mov bl, 0feh
dispnext:  mov al, [si]
           push bx
           mov bx, offset ledbuf
           xlat
           mov dx, porta
           out dx, al
           pop bx            ;���������
           mov al, bl
           mov dx, portb
           out dx, al            ;�ͳ�λ�������λ
           push cx
           mov cx, 0E000h
delay:     loop delay
           pop cx                ;��ʱ�ȶ�ʱ��
     
           cmp bl,11110111B      ;�ж��Ƿ���λȫ����ʾ
           jz done         
           inc si                ;δȫ����ʾ��ָ��ָ����һ����Ҫ��ʾ�������ı�λ��
           rol bl,1
           jmp dispnext    
done:      dec cx
           jnz again          ;��������ˢ��0900h�Σ�����ʾ�ȶ� �����ֱ�Сˢ��Խ�죬λ��Խ�ͣ���˸Խ��               
           ret         

disp endp


plus1     proc          
          mov si, 0
          mov cx, 4
          clc
 next3:   mov al, datbuf[si]
          adc al, plus[si]
          aaa
          mov datbuf[si], al
          inc si
          loop next3
          ret
plus1     endp                ;cx����ֵ��led�ĸ�����ͬ����

           	
code ends
	end start

;���ߣ�A�� ��Ϊ���������B����Ϊλ�������λ�ض�Ӧ��ϵע�⣺pb0���Ƹ�λ��ʾ���������ƣ�����pb0��x4,pb1��x3,��������

