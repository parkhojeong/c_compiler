	      INT   0, 24
	      SUP   0, main
	      RET   0, 0
fun:
	      INT   0, 16
.global    12  0	      INT   0, 12
	      LDA   0, 12
	      LOD   1, 12
	      POP   0, 5
	     ADDR   0, printf
	      CAL   0, 0
	      RET   0, 0
main:
	      INT   0, 12
	      INT   0, 12
	      POP   0, 3
	     ADDR   0, fun
	      CAL   0, 0
	      LDA   1, -4
	     LITI   0, 0
	      STO   0, 1
	      RET   0, 0
	      RET   0, 0
.literal    12  "a: %d\n"
