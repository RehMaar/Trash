iseg at 30h
Stack: ds 10
cseg at 0
ljmp start

cseg at 0Bh
ljmp ex00

cseg at 13h
ljmp ex01

cseg at 40h
start:
mov P3, #0
mov SP, #Stack-1
mov TMOD, #11h
setb EA
setb EX1
setb IT1
setb TR1
setb TR0
setb ET0
setb IE0
cikl: jmp cikl

ex00: 
  push ACC
  mov TL0, #0xEF
  mov TH0, #0xD8
  mov a, P3
  subb a, #0x7E
  jz zero
  mov P3, #0x7F
  jmp nzero
  zero: mov P3, #0
  nzero:
  pop ACC
  Reti

ex01:
  push ACC
  mov P2, TH1
  mov P1, TL1
  mov TH1, #0
  mov TL1, #0
  pop ACC
  Reti

end
