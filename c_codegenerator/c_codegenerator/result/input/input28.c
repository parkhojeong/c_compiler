	      INT   0, 24
	      SUP   0, main
	      RET   0, 0
bubble_sort:
	      INT   0, 32
	      LDA   1, 20
	      LOD   1, 16
	     LITI   0, 1
	     SUBI   0, 0
	      STX   0, 1
	      POP   0, 1
L2:
	      LOD   1, 20
	     LITI   0, 0
	     GTRI   0, 0
	      JPC   0, L3
	      LDA   1, 24
	     LITI   0, 0
	      STX   0, 1
	      POP   0, 1
L5:
	      LOD   1, 24
	      LOD   1, 20
	     LSSI   0, 0
	      JPC   0, L6
	      LOD   1, 12
	      LOD   1, 24
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	      LDI   0, 1
	      LOD   1, 12
	      LOD   1, 24
	     LITI   0, 1
	     ADDI   0, 0
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	      LDI   0, 1
	     LSSI   0, 0
	      JPC   0, L7
	      LDA   1, 28
	      LOD   1, 12
	      LOD   1, 24
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	      LDI   0, 1
	      STX   0, 1
	      POP   0, 1
	      LOD   1, 12
	      LOD   1, 24
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	      LOD   1, 12
	      LOD   1, 24
	     LITI   0, 1
	     ADDI   0, 0
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	      LDI   0, 1
	      STX   0, 1
	      POP   0, 1
	      LOD   1, 12
	      LOD   1, 24
	     LITI   0, 1
	     ADDI   0, 0
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	      LOD   1, 28
	      STX   0, 1
	      POP   0, 1
L7:
L4:
	      LOD   1, 24
	      LDA   1, 24
	      LDX   0, 1
	     INCI   0, 0
	      STO   0, 1
	      POP   0, 1
	      JMP   0, L5
L6:
L1:
	      LOD   1, 20
	      LDA   1, 20
	      LDX   0, 1
	     DECI   0, 0
	      STO   0, 1
	      POP   0, 1
	      JMP   0, L2
L3:
	      RET   0, 0
	      RET   0, 0
main:
	      INT   0, 40
	      LDA   0, 12
	     LITI   0, 5
	      STX   0, 1
	      POP   0, 1
	      LDA   1, 16
	      LOD   0, 12
	      STX   0, 1
	      POP   0, 1
	      LDA   1, 20
	     LITI   0, 0
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	     LITI   0, 7
	      STX   0, 1
	      POP   0, 1
	      LDA   1, 20
	     LITI   0, 1
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	     LITI   0, 5
	      STX   0, 1
	      POP   0, 1
	      LDA   1, 20
	     LITI   0, 2
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	     LITI   0, 3
	      STX   0, 1
	      POP   0, 1
	      LDA   1, 20
	     LITI   0, 3
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	     LITI   0, 1
	      STX   0, 1
	      POP   0, 1
	      LDA   1, 20
	     LITI   0, 4
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	     LITI   0, 4
	      STX   0, 1
	      POP   0, 1
	      LDA   1, 12
	     LITI   0, 0
	      STX   0, 1
	      POP   0, 1
L9:
	      LOD   1, 12
	      LOD   1, 16
	     LSSI   0, 0
	      JPC   0, L10
	      INT   0, 12
	      LDA   0, 16
	      LDA   1, 20
	      LOD   1, 12
	     LITI   0, 4
	     MULI   0, 0
	   OFFSET   0, 0
	      LDI   0, 1
	      POP   0, 5
	     ADDR   0, printf
	      CAL   0, 0
L8:
	      LOD   1, 12
	      LDA   1, 12
	      LDX   0, 1
	     INCI   0, 0
	      STO   0, 1
	      POP   0, 1
	      JMP   0, L9
L10:
	      RET   0, 0
.literal    16  "%d\n"