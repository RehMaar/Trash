cseg at 0x0
	ljmp start

cseg at 0x3
	reti
	 
cseg at 0x4
	ret_test:
		dec a ; test "dec a" (a <- 0x3C, P <- 0)
		ret   ; test "ret"
	start:
		; the initial state
		mov ie,   #0x81
		mov 0x40, #0xDE
		mov 0x41, #0x3E
		mov 0x20, #0x0F ; Set bits 0-3 to 1, 4-7 to 0.
		mov r1,   #0x41
		anl c,     0x04 ; c <- 0

		dec @R1     ; test "dec @ri"     (0x41 <- 0x3D)
		mov a, 0x40 ; test "mov a, ad"   (a <- 0xDE, P <- 0)
		mov a, @R1  ; test "mov a, @ri"  (a <- 0x3D, P <- 1)
		orl c, 0x1  ; test "orl c, bit"  (c <- 1)
		anl c, 0x4
		orl c, /0x4 ; test "orl c, /bit" (c <- 1)
		
		acall ret_test
		
		jb 0x1, pas ; test "jb TRUE, rel"
	err:
		ljmp err	
	pas:
		jb 0x4, err ; test "jb FALSE, rel"
	suc:
		ljmp suc
end
