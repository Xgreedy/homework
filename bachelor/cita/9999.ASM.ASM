porta equ 1440h
portb equ 1441h
portcontrol equ 1443h

data  segment
	ledbuf      db   3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh ;段码
	datbuf      db   00h,00h,00h,00h         ;存放要显示4位
	plus        db   01h, 00h, 00h,00h   
data ends

code  segment
	assume cs:code,ds:data
start:  mov ax,data
	    mov ds,ax

        mov dx,portcontrol                  ;将8255设为A\B口输出，A为段码输出，B为位码输出
	    mov al,10000000B
	    out dx,al


dispnew:  call disp                    ;disp稳定的显示数据区的数字
     
        mov dx, 0ffh                  ;判断键盘是否有键按下，有键按下推出程序
        mov ah, 06h
        int 21h
        jnz exit 
               
        call plus1
        jmp dispnew

exit:   mov dx,portb
	    mov al,0ffh                    ;关掉数码管显示
	    out dx,al
	    mov ah,4ch                  ;返回DOS
	    int 21h

disp proc                          ;将数据区databuf中的数据稳定显示     
          mov cx, 900h
again:    mov si, offset datbuf
          mov bl, 0feh
dispnext:  mov al, [si]
           push bx
           mov bx, offset ledbuf
           xlat
           mov dx, porta
           out dx, al
           pop bx            ;将段码输出
           mov al, bl
           mov dx, portb
           out dx, al            ;送出位码点亮个位
           push cx
           mov cx, 0E000h
delay:     loop delay
           pop cx                ;延时稳定时间
     
           cmp bl,11110111B      ;判断是否六位全部显示
           jz done         
           inc si                ;未全部显示，指针指向下一个需要显示的数，改变位码
           rol bl,1
           jmp dispnext    
done:      dec cx
           jnz again          ;整个过程刷新0900h次，将显示稳定 ；数字变小刷新越快，位数越低，闪烁越快               
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
plus1     endp                ;cx的数值与led的个数相同即可

           	
code ends
	end start

;接线：A口 作为段码输出，B口作为位码输出，位控对应关系注意：pb0控制个位显示，依次类推，所以pb0接x4,pb1接x3,依次类推


