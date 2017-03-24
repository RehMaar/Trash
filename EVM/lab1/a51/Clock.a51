cseg at 0b
	jmp main
cseg at 0bh
	jmp intt0
cseg at 0030h
count equ r0
time equ r1
sec equ r2
min equ r3
;Turn on bank reg 1
USING 1
main:
	; Setup params interrupt
	MOV	TMOD, #01H
	; mask TF0
	SETB ET0
	SETB TR0
	; turn on interrupt
	SETB EA
	;cycle
	whl:
	MOV P1, sec
	SJMP whl
	; FUNCTION main (END)
intt0:
	PUSH ACC
	PUSH PSW 
	
	MOV P2, #00H
	; setup params for timer
	MOV TH0, #03CH
	; const recalc for timer
	MOV TL0, #0B0H
	; counter overflow
	INC count
	MOV A, #0AH
	ADD A, time
	MOV time, A
	MOV A, count
	CJNE A, #014H, ifcount
	INC sec
	MOV count, #00H
	ifcount:
	MOV A, sec
	CJNE A, #03CH,ifsec
	INC min
	MOV sec, #00H
	ifsec:
	MOV P2, #07FH
	POP PSW
	POP ACC
RETI
END