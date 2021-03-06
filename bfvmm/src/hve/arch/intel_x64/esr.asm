;
; Bareflank Extended APIs
;
; Copyright (C) 2018 Assured Information Security, Inc.
;
; This library is free software; you can redistribute it and/or
; modify it under the terms of the GNU Lesser General Public
; License as published by the Free Software Foundation; either
; version 2.1 of the License, or (at your option) any later version.
;
; This library is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
; Lesser General Public License for more details.
;
; You should have received a copy of the GNU Lesser General Public
; License along with this library; if not, write to the Free Software
; Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

bits 64
default rel

extern default_esr

section .text

%macro PUSHALL 0
    sub rsp, 16
    movups [rsp], xmm0
    sub rsp, 16
    movups [rsp], xmm1
    sub rsp, 16
    movups [rsp], xmm2
    sub rsp, 16
    movups [rsp], xmm3
    sub rsp, 16
    movups [rsp], xmm4
    sub rsp, 16
    movups [rsp], xmm5
    sub rsp, 16
    movups [rsp], xmm6
    sub rsp, 16
    movups [rsp], xmm7

    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    ;
    ; make the irq_manager available from the IDT
    ;
    mov r15, [gs:0x0088]
    push r15

%endmacro

%macro POPALL 0
    pop r15
    mov [gs:0x0088], r15
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax

    movups xmm7, [rsp]
    add rsp, 16
    movups xmm6, [rsp]
    add rsp, 16
    movups xmm5, [rsp]
    add rsp, 16
    movups xmm4, [rsp]
    add rsp, 16
    movups xmm3, [rsp]
    add rsp, 16
    movups xmm2, [rsp]
    add rsp, 16
    movups xmm1, [rsp]
    add rsp, 16
    movups xmm0, [rsp]
    add rsp, 16
%endmacro

%macro ESR_NOERRCODE 1
    global _esr%1
    _esr%1:
        PUSHALL
        mov rdi, %1
        mov rsi, 0
        mov rdx, 0
        mov rcx, rsp
        call default_esr wrt ..plt
        POPALL
        iretq
%endmacro

%macro ESR_ERRCODE 1
    global _esr%1
    _esr%1:
        PUSHALL
        mov rdi, %1
        mov rsi, [rsp + 248]
        mov rdx, 1
        mov rcx, rsp
        call default_esr wrt ..plt
        POPALL
        add rsp, 8
        iretq
%endmacro

ESR_NOERRCODE 0
ESR_NOERRCODE 1
ESR_NOERRCODE 2
ESR_NOERRCODE 3
ESR_NOERRCODE 4
ESR_NOERRCODE 5
ESR_NOERRCODE 6
ESR_NOERRCODE 7
ESR_ERRCODE   8
ESR_NOERRCODE 9
ESR_ERRCODE   10
ESR_ERRCODE   11
ESR_ERRCODE   12
ESR_ERRCODE   13
ESR_ERRCODE   14
ESR_NOERRCODE 15
ESR_NOERRCODE 16
ESR_ERRCODE   17
ESR_NOERRCODE 18
ESR_NOERRCODE 19
ESR_NOERRCODE 20
ESR_NOERRCODE 21
ESR_NOERRCODE 22
ESR_NOERRCODE 23
ESR_NOERRCODE 24
ESR_NOERRCODE 25
ESR_NOERRCODE 26
ESR_NOERRCODE 27
ESR_NOERRCODE 28
ESR_NOERRCODE 29
ESR_NOERRCODE 30
ESR_NOERRCODE 31
