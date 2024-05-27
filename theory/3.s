	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 3
	.globl	_routine                        ; -- Begin function routine
	.p2align	2
_routine:                               ; @routine
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16                     ; =16
	.cfi_def_cfa_offset 16
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #12]
	mov	w9, #16960
	movk	w9, #15, lsl #16
	subs	w8, w8, w9
	b.ge	LBB0_3
; %bb.2:                                ;   in Loop: Header=BB0_1 Depth=1
	adrp	x8, _mails@PAGE
	ldr	w9, [x8, _mails@PAGEOFF]
	add	w9, w9, #1                      ; =1
	str	w9, [x8, _mails@PAGEOFF]
	ldr	w9, [sp, #12]
	add	w9, w9, #1                      ; =1
	str	w9, [sp, #12]
	b	LBB0_1
LBB0_3:
	mov	x8, #0
	mov	x0, x8
	add	sp, sp, #16                     ; =16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #64                     ; =64
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48                    ; =48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	wzr, [x29, #-4]
	sub	x0, x29, #16                    ; =16
	mov	x8, #0
	mov	x1, x8
	adrp	x2, _routine@PAGE
	add	x2, x2, _routine@PAGEOFF
	mov	x3, x8
	bl	_pthread_create
	cbz	w0, LBB1_2
; %bb.1:
	mov	w8, #1
	stur	w8, [x29, #-4]
	b	LBB1_9
LBB1_2:
	add	x0, sp, #24                     ; =24
	mov	x8, #0
	mov	x1, x8
	adrp	x2, _routine@PAGE
	add	x2, x2, _routine@PAGEOFF
	mov	x3, x8
	bl	_pthread_create
	cbz	w0, LBB1_4
; %bb.3:
	mov	w8, #2
	stur	w8, [x29, #-4]
	b	LBB1_9
LBB1_4:
	ldur	x0, [x29, #-16]
	mov	x8, #0
	mov	x1, x8
	bl	_pthread_join
	cbz	w0, LBB1_6
; %bb.5:
	mov	w8, #3
	stur	w8, [x29, #-4]
	b	LBB1_9
LBB1_6:
	ldr	x0, [sp, #24]
	mov	x8, #0
	mov	x1, x8
	bl	_pthread_join
	cbz	w0, LBB1_8
; %bb.7:
	mov	w8, #4
	stur	w8, [x29, #-4]
	b	LBB1_9
LBB1_8:
	adrp	x8, _mails@PAGE
	ldr	w9, [x8, _mails@PAGEOFF]
                                        ; implicit-def: $x0
	mov	x0, x9
	adrp	x8, l_.str@PAGE
	add	x8, x8, l_.str@PAGEOFF
	str	x0, [sp, #16]                   ; 8-byte Folded Spill
	mov	x0, x8
	mov	x8, sp
	ldr	x10, [sp, #16]                  ; 8-byte Folded Reload
	str	x10, [x8]
	bl	_printf
	stur	wzr, [x29, #-4]
LBB1_9:
	ldur	w0, [x29, #-4]
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64                     ; =64
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_mails                          ; @mails
.zerofill __DATA,__common,_mails,4,2
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Mails nb : %d\n"

.subsections_via_symbols
