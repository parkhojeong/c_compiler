	      INT   0, 36
	      SUP   0, main
	      RET   0, 0
main:
	      INT   0, 12
	      LDA   0, 12
	      LDA   0, 12
	      LDI   0, 1
	     LITI   0, 3
	      STX   0, 1
	      POP   0, 1
	      LDA   0, 12
	      LDA   0, 12
	      LDI   0, 1
	      LOD   0, 16
	      STX   0, 1
	      POP   0, 1
	      INT   0, 12
	      LDA   0, 20
	      LDA   0, 12
	      LDI   0, 1
	      POP   0, 5
	     ADDR   0, printf
	      CAL   0, 0
	      RET   0, 0
.literal    16  3.500000
.literal    20  "myvar: %f\n"
