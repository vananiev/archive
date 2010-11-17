;----------------------------------------------------------------------
; Define macro of Entry Point

Point_main          equ 0
Point_WinMain       equ 1
Point_DllMain       equ 2
Point_DllEntryPoint equ 3

; Macro to extern

ExternPoint macro pointtype

 if pointtype eq Point_main
EXTRN           main :NEAR
 else
 if pointtype eq Point_WinMain
EXTRN           WinMain :NEAR
 else
 if pointtype eq Point_DllMain
EXTRN           DllMain :NEAR
 else
 if pointtype eq Point_DllEntryPoint
EXTRN           DllEntryPoint :NEAR
 endif
 endif
 endif
 endif
endm

; Macro to jump

jmpTo macro pointtype

 if pointtype eq Point_main
  jmp main
 else
 if pointtype eq Point_WinMain
  jmp WinMain
 else
 if pointtype eq Point_DllMain
  jmp DllMain
 else
 if pointtype eq Point_DllEntryPoint
  jmp DllEntryPoint
 endif
 endif
 endif
 endif
endm

;----------------------------------------------------------------------
; User's declaration of Entry Point

MyPoint equ Point_WinMain

;----------------------------------------------------------------------

                .386P
ifndef MASM
                model flat
LOCALS
endif
                ASSUME   CS: FLAT, DS: FLAT, SS: FLAT, ES: FLAT

;----------------------------------------------------------------------
; Code segment

_TEXT           SEGMENT PUBLIC DWORD USE32 PUBLIC 'CODE'
_TEXT           ENDS

;----------------------------------------------------------------------
; External function definitions

_TEXT           SEGMENT PUBLIC DWORD USE32 PUBLIC 'CODE'

           ExternPoint MyPoint

_TEXT           ENDS


;----------------------------------------------------------------------
; Startup code

_TEXT           SEGMENT  DWORD USE32 PUBLIC 'CODE'

                public __acrtused
__acrtused      PROC NEAR

                jmpTo MyPoint

__acrtused      ENDP

_TEXT           ENDS

                END     __acrtused
