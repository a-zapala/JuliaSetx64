    section .data

    section .text
    global julia
julia:
    push rbp
    mov rbp,rsp
    mov r8,0
    mov r9,0
    mov r10,0x000000
    mov r11,0xffffff
    movsd xmm13,xmm0 ; actual x
    movsd xmm14,xmm1 ; actual y


loopPixel:
   cmp r8,rsi
   je nextLine
   cmp r9,rdx
   je end
   mov rax,0 ; iteration
   mov rcx,100; max of iteration
   movsd xmm8,xmm13
   movsd xmm9,xmm14

loopJulia:
   movsd xmm10,xmm8; actual x
   mulsd xmm10,xmm10 ; x^2

   movsd xmm11,xmm9; actual y
   mulsd xmm11,xmm11; y^2
   movsd xmm12,xmm10
   addsd xmm12,xmm11 ; x^2 + y^2
   ucomisd xmm12,xmm5 ;xmm5 is 4
   ja colourWhitePixel
   jp colourWhitePixel


   movsd xmm12, xmm10
   subsd xmm12,xmm11 ; x^2-y^2

   addsd xmm9,xmm9 ;2*y
   mulsd xmm9,xmm8 ;2*x*y
   addsd xmm9,xmm4;2*x*y+cy

   movsd xmm8,xmm12
   addsd xmm8,xmm3;x^2-y^2+cx

   add rax,1
   cmp rax,rcx
   jge colourBlackPixel

   jmp loopJulia

colourWhitePixel:
   mov [rdi],r10
   jmp next

colourBlackPixel:
    mov[rdi],r11

next:
   inc r8
   add rdi,3
   addsd xmm13,xmm2
   jmp loopPixel

nextLine:
    mov r8,0
    inc r9
    movsd xmm13,xmm0
    addsd xmm14,xmm2
    jmp loopPixel

end:
    mov rsp,rbp
    pop rbp
    ret