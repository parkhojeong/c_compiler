	      INT   0, 28
	      SUP   0, main
	      RET   0, 0
max:
	      INT   0, 24
	      LOD   1, 12
	      LOD   1, 16
	     GTRI   0, 0
	      JPC   0, L1
	      LDA   1, 20
	      LOD   1, 12
	      STX   0, 1
	      POP   0, 1
	      JMP   0, L2
L1:
	      LDA   1, 20
	      LOD   1, 16
	      STX   0, 1
	      POP   0, 1
L2:
	      LDA   1, -4
	      LOD   1, 20
	      STO   0, 1
	      RET   0, 0
	      RET   0, 0
main:
	      INT   0, 16
	      LDA   1, 12
	      INT   0, 16
	     LITI   0, 3
	     LITI   0, 5
	      POP   0, 5
	     ADDR   0, max
	      CAL   0, 0
	      STX   0, 1
	      POP   0, 1
	      INT   0, 12
	      LDA   0, 12
	      LOD   1, 12
	      POP   0, 5
	     ADDR   0, printf
	      CAL   0, 0
	      LDA   1, -4
	     LITI   0, 0
	      STO   0, 1
	      RET   0, 0
	      RET   0, 0
.literal    12  "result : %d"
