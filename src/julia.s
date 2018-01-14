    section .data

    section .text
    global julia

;rdi - pixelBuffer
;rsi -width
;rdx - high
;xmm0 - zoom
;xmm1 - x0
;xmm2 - y0
;xmm3 - real of Complex
;xmm4 - imaginary of Complex


julia:
    push rbp
    mov rbp,rsp
    mov r8,0
    mov r9,0
    movsd xmm13,xmm0 ; curent x
    movsd xmm14,xmm1 ; curent y


loopPixel:
   cmp r8,rsi
   je nextLine
   cmp r9,rdx
   je end
   mov rax,0x000000 ; iteration
   mov rcx,0xffffff; max of iteration
   movsd xmm8,xmm13
   movsd xmm9,xmm14

loopJulia:
   movsd xmm10,xmm8; curent xz
   mulsd xmm10,xmm10 ; xz^2

   movsd xmm11,xmm9; curent yz
   mulsd xmm11,xmm11; yz^2
   movsd xmm12,xmm10
   addsd xmm12,xmm11 ; xz^2 + yz^2
   ucomisd xmm12,xmm5 ;xmm5 is 4
   ja next
   jp next


   movsd xmm12, xmm10
   subsd xmm12,xmm11 ; xz^2-yz^2

   addsd xmm9,xmm9 ;2*yz
   mulsd xmm9,xmm8 ;2*xz*yz
   addsd xmm9,xmm4;2*xz*yz+cy

   movsd xmm8,xmm12
   addsd xmm8,xmm3;xz^2-yz^2+cx

   add rax,0x010101
   cmp rax,rcx
   jge next

   jmp loopJulia


next:
   mov [rdi],rax
   inc r8
   add rdi,3
   addsd xmm13,xmm2 ; actual x + zoom
   jmp loopPixel

nextLine:
    mov r8,0
    inc r9
    movsd xmm13,xmm0 ; acual x = x0
    addsd xmm14,xmm2    ;actual x + zoom
    jmp loopPixel

end:
    mov rsp,rbp
    pop rbp
    ret