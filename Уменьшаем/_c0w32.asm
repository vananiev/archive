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

;;;; EXTRN           main:NEAR
EXTRN           WinMain:NEAR
;;;; EXTRN          DllMain:NEAR
;;;; EXTRN          DllEntryPoint:NEAR

_TEXT           ENDS


;----------------------------------------------------------------------
; Startup code

_TEXT           SEGMENT  DWORD USE32 PUBLIC 'CODE'

                public __acrtused
__acrtused      PROC NEAR

;;;;                jmp     main
jmp     WinMain
;;;;                jmp     DllMain
;;;;                jmp     DllEntryPoint

__acrtused      ENDP

_TEXT           ENDS

                END     __acrtused
