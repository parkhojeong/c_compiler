	      INT   0, 56
	      SUP   0, main
	      RET   0, 0
.global    12  0main:
	      INT   0, 16
	      LDA   1, 12
	      LOD   0, 12
	      STX   0, 1
	      POP   0, 1
	      INT   0, 12
	      LDA   0, 16
	      LOD   0, 12
	      POP   0, 5
	     ADDR   0, printf
	      CAL   0, 0
	      INT   0, 12
	      LDA   0, 36
	      LOD   1, 12
	      POP   0, 5
	     ADDR   0, printf
	      CAL   0, 0
	      LDA   1, -4
	     LITI   0, 0
	      STO   0, 1
	      RET   0, 0
	      RET   0, 0
.literal    16  "global_a : %d\n"
.literal    36  "local_b : %d\n"
