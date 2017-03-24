iseg at 30h
Stack: ds 10
cseg at 0
ljmp start

cseg at 3h
ljmp ex00
cseg at 13h
ljmp ex01

cseg at 40h
start: 
mov SP, #Stack-1
clr A
mov P3, A
clr c
cpl c
mov EA, c
cikl: inc a
jmp cikl

ex00: 
  push ACC
  mov A, P3
  inc A
  mov P3, A
  pop ACC
  Reti

ex01:
  push ACC
  mov A, P3
  dec A
  mov P3, A
  pop ACC
  Reti

end
