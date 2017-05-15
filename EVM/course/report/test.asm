cseg at 0x0
	ljmp start
cseg at 0x3
	reti
	 
cseg at 0x4
	start:
    	mov 0xAA, #0x04
		mov a, 0xAA
		dec a
		orl c, /ACC.1
		mov @R0, #0xAA
		dec @R0
		mov a, @R0
		orl c, ACC.1
		jb ACC.1, ok; test "jb TRUE, rel"
	err:
		ljmp err	
	ok:
		jb ACC.7, err ; test "jb FALSE, rel"
	fin:
		ljmp fin
end
