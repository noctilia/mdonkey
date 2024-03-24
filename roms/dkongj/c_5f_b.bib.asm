; reset
; a = 0, nmi = 0
;---------------------------------------------------
000: 3e 00        ld   a,$00
002: 32 84 7d     ld   ($7D84),a
005: c3 66 02     jp   $0266    ; goto init ram, tile ram, sprite ram
;---------------------------------------------------
008: 3a 07 60     ld   a,($6007)
00b: 0f           rrca
00c: d0           ret  nc
00d: 33           inc  sp
00e: 33           inc  sp
00f: c9           ret
;---------------------------------------------------
010: 3a 00 62     ld   a,($6200)
013: 0f           rrca
014: d8           ret  c
015: 33           inc  sp
016: 33           inc  sp
017: c9           ret
;---------------------------------------------------
018: 21 09 60     ld   hl,$6009
01b: 35           dec  (hl)
01c: c8           ret  z
01d: 33           inc  sp
01e: 33           inc  sp
01f: c9           ret
;---------------------------------------------------
020: 21 08 60     ld   hl,$6008
023: 35           dec  (hl)
024: 28 f2        jr   z,$0018
026: e1           pop  hl
027: c9           ret
;---------------------------------------------------
028: 87           add  a,a
029: e1           pop  hl
02a: 5f           ld   e,a
02b: 16 00        ld   d,$00
02d: c3 32 00     jp   $0032
030: 18 12        jr   $0044
032: 19           add  hl,de
033: 5e           ld   e,(hl)
034: 23           inc  hl
035: 56           ld   d,(hl)
036: eb           ex   de,hl
037: e9           jp   (hl)
038: 11 04 00     ld   de,$0004
03b: 06 0a        ld   b,$0A
03d: 79           ld   a,c
03e: 86           add  a,(hl)
03f: 77           ld   (hl),a
040: 19           add  hl,de
041: 10 fa        djnz $003D
043: c9           ret
;---------------------------------------------------
044: 21 27 62     ld   hl,$6227
047: 46           ld   b,(hl)
048: 0f           rrca
049: 10 fd        djnz $0048
04b: d8           ret  c
04c: e1           pop  hl
04d: c9           ret
;---------------------------------------------------
; copy to static sprite ram
04e: 11 08 69     ld   de,$6908
051: 01 28 00     ld   bc,$0028
054: ed b0        ldir
056: c9           ret
;---------------------------------------------------
057: 3a 18 60     ld   a,($6018)
05a: 21 1a 60     ld   hl,$601A
05d: 86           add  a,(hl)
05e: 21 19 60     ld   hl,$6019
061: 86           add  a,(hl)
062: 32 18 60     ld   ($6018),a
065: c9           ret
;---------------------------------------------------
; main vblank or irq?
066: f5           push af
067: c5           push bc
068: d5           push de
069: e5           push hl
06a: dd e5        push ix
06c: fd e5        push iy
06e: af           xor  a
06f: 32 84 7d     ld   ($7D84),a
072: 3a 00 7d     ld   a,($7D00)
075: e6 01        and  $01
077: c2 00 40     jp   nz,$4000
07a: 21 38 01     ld   hl,$0138
07d: cd 41 01     call $0141
080: 3a 07 60     ld   a,($6007)
083: a7           and  a
084: c2 b5 00     jp   nz,$00B5
087: 3a 26 60     ld   a,($6026)
08a: a7           and  a
08b: c2 98 00     jp   nz,$0098
08e: 3a 0e 60     ld   a,($600E)
091: a7           and  a
092: 3a 80 7c     ld   a,($7C80)
095: c2 9b 00     jp   nz,$009B
098: 3a 00 7c     ld   a,($7C00)
09b: 47           ld   b,a
09c: e6 0f        and  $0F
09e: 4f           ld   c,a
09f: 3a 11 60     ld   a,($6011)
0a2: 2f           cpl
0a3: a0           and  b
0a4: e6 10        and  $10
0a6: 17           rla
0a7: 17           rla
0a8: 17           rla
0a9: b1           or   c
0aa: 60           ld   h,b
0ab: 6f           ld   l,a
0ac: 22 10 60     ld   ($6010),hl
0af: 78           ld   a,b
0b0: cb 77        bit  6,a
0b2: c2 00 00     jp   nz,$0000
0b5: 21 1a 60     ld   hl,$601A
0b8: 35           dec  (hl)
0b9: cd 57 00     call $0057
0bc: cd 7b 01     call $017B
0bf: cd e0 00     call $00E0
0c2: 21 d2 00     ld   hl,$00D2
0c5: e5           push hl
0c6: 3a 05 60     ld   a,($6005)
0c9: ef           rst  $28
0ca: c3 01 3c     jp   $3C01
0cd: 07           rlca
0ce: b2           or   d
0cf: 08           ex   af,af'
0d0: fe 06        cp   $06
0d2: fd e1        pop  iy
0d4: dd e1        pop  ix
0d6: e1           pop  hl
0d7: d1           pop  de
0d8: c1           pop  bc
0d9: 3e 01        ld   a,$01
0db: 32 84 7d     ld   ($7D84),a
0de: f1           pop  af
0df: c9           ret
;---------------------------------------------------
0e0: 21 80 60     ld   hl,$6080
0e3: 11 00 7d     ld   de,$7D00
0e6: 3a 07 60     ld   a,($6007)
0e9: a7           and  a
0ea: c0           ret  nz
;---------------------------------------------------
0eb: 06 08        ld   b,$08
0ed: 7e           ld   a,(hl)
0ee: a7           and  a
0ef: ca f5 00     jp   z,$00F5
0f2: 35           dec  (hl)
0f3: 3e 01        ld   a,$01
0f5: 12           ld   (de),a
0f6: 1c           inc  e
0f7: 2c           inc  l
0f8: 10 f3        djnz $00ED
0fa: 21 8b 60     ld   hl,$608B
0fd: 7e           ld   a,(hl)
0fe: a7           and  a
0ff: c2 08 01     jp   nz,$0108
102: 2d           dec  l
103: 2d           dec  l
104: 7e           ld   a,(hl)
105: c3 0b 01     jp   $010B
108: 35           dec  (hl)
109: 2d           dec  l
10a: 7e           ld   a,(hl)
10b: 32 00 7c     ld   ($7C00),a
10e: 21 88 60     ld   hl,$6088
111: af           xor  a
112: be           cp   (hl)
113: ca 18 01     jp   z,$0118
116: 35           dec  (hl)
117: 3c           inc  a
118: 32 80 7d     ld   ($7D80),a
11b: c9           ret

; function init_sound? clear 7d00 sound signals, 6080 
; clear 8 bytes at $7d00??? and $6080
11c: 06 08        ld   b,$08          
11e: af           xor  a
11f: 21 00 7d     ld   hl,$7D00
122: 11 80 60     ld   de,$6080
125: 77           ld   (hl),a
126: 12           ld   (de),a
127: 2c           inc  l
128: 1c           inc  e
129: 10 fa        djnz $0125          

; clear 4 bytes at $6088
12b: 06 04        ld   b,$04
12d: 12           ld   (de),a
12e: 1c           inc  e
12f: 10 fc        djnz $012D
; clear 1 byte at $7D80 (audio), $7C00 (IN0 port)
131: 32 80 7d     ld   ($7D80),a
134: 32 00 7c     ld   ($7C00),a
137: c9           ret
; -------------------------------------
138: 53           ld   d,e
139: 00           nop
13a: 69           ld   l,c
13b: 80           add  a,b
13c: 41           ld   b,c
13d: 00           nop
13e: 70           ld   (hl),b
13f: 80           add  a,b
140: 81           add  a,c
141: af           xor  a
142: 32 85 7d     ld   ($7D85),a
145: 7e           ld   a,(hl)
146: 32 08 78     ld   ($7808),a
149: 23           inc  hl
14a: 7e           ld   a,(hl)
14b: 32 00 78     ld   ($7800),a
14e: 23           inc  hl
14f: 7e           ld   a,(hl)
150: 32 00 78     ld   ($7800),a
153: 23           inc  hl
154: 7e           ld   a,(hl)
155: 32 01 78     ld   ($7801),a
158: 23           inc  hl
159: 7e           ld   a,(hl)
15a: 32 01 78     ld   ($7801),a
15d: 23           inc  hl
15e: 7e           ld   a,(hl)
15f: 32 02 78     ld   ($7802),a
162: 23           inc  hl
163: 7e           ld   a,(hl)
164: 32 02 78     ld   ($7802),a
167: 23           inc  hl
168: 7e           ld   a,(hl)
169: 32 03 78     ld   ($7803),a
16c: 23           inc  hl
16d: 7e           ld   a,(hl)
16e: 32 03 78     ld   ($7803),a
171: 3e 01        ld   a,$01
173: 32 85 7d     ld   ($7D85),a
176: af           xor  a
177: 32 85 7d     ld   ($7D85),a
17a: c9           ret
17b: 3a 00 7d     ld   a,($7D00)
17e: cb 7f        bit  7,a
180: 21 03 60     ld   hl,$6003
183: c2 89 01     jp   nz,$0189
186: 36 01        ld   (hl),$01
188: c9           ret
189: 7e           ld   a,(hl)
18a: a7           and  a
18b: c8           ret  z
18c: e5           push hl
18d: 3a 05 60     ld   a,($6005)
190: fe 03        cp   $03
192: ca 9d 01     jp   z,$019D
195: cd 1c 01     call $011C
198: 3e 03        ld   a,$03
19a: 32 83 60     ld   ($6083),a
19d: e1           pop  hl
19e: 36 00        ld   (hl),$00
1a0: 2b           dec  hl
1a1: 34           inc  (hl)
1a2: 11 24 60     ld   de,$6024
1a5: 1a           ld   a,(de)
1a6: 96           sub  (hl)
1a7: c0           ret  nz
1a8: 77           ld   (hl),a
1a9: 13           inc  de
1aa: 2b           dec  hl
1ab: eb           ex   de,hl
1ac: 1a           ld   a,(de)
1ad: fe 90        cp   $90
1af: d0           ret  nc
1b0: 86           add  a,(hl)
1b1: 27           daa
1b2: 12           ld   (de),a
1b3: 11 00 04     ld   de,$0400
1b6: cd 9f 30     call $309F
1b9: c9           ret
1ba: 00           nop
1bb: 37           scf
1bc: 00           nop
1bd: aa           xor  d
1be: aa           xor  d
1bf: aa           xor  d
1c0: 50           ld   d,b
1c1: 76           halt
1c2: 00           nop
1c3: cd 74 08     call $0874
1c6: 21 ba 01     ld   hl,$01BA
1c9: 11 b2 60     ld   de,$60B2
1cc: 01 09 00     ld   bc,$0009
1cf: ed b0        ldir
1d1: 3e 01        ld   a,$01
1d3: 32 07 60     ld   ($6007),a
1d6: 32 29 62     ld   ($6229),a
1d9: 32 28 62     ld   ($6228),a
1dc: cd b8 06     call $06B8
1df: cd 07 02     call $0207
1e2: 3e 01        ld   a,$01
1e4: 32 82 7d     ld   ($7D82),a
1e7: 32 05 60     ld   ($6005),a
1ea: 32 27 62     ld   ($6227),a
1ed: af           xor  a
1ee: 32 0a 60     ld   ($600A),a
1f1: cd 53 0a     call $0A53
1f4: 11 04 03     ld   de,$0304
1f7: cd 9f 30     call $309F
1fa: 11 02 02     ld   de,$0202
1fd: cd 9f 30     call $309F
200: 11 00 02     ld   de,$0200
203: cd 9f 30     call $309F
206: c9           ret
207: 3a 80 7d     ld   a,($7D80)
20a: 4f           ld   c,a
20b: 21 20 60     ld   hl,$6020
20e: e6 03        and  $03
210: c6 03        add  a,$03
212: 77           ld   (hl),a
213: 23           inc  hl
214: 79           ld   a,c
215: 0f           rrca
216: 0f           rrca
217: e6 03        and  $03
219: 47           ld   b,a
21a: 3e 07        ld   a,$07
21c: ca 26 02     jp   z,$0226
21f: 3e 05        ld   a,$05
221: c6 05        add  a,$05
223: 27           daa
224: 10 fb        djnz $0221
226: 77           ld   (hl),a
227: 23           inc  hl
228: 79           ld   a,c
229: 01 01 01     ld   bc,$0101
22c: 11 02 01     ld   de,$0102
22f: e6 70        and  $70
231: 17           rla
232: 17           rla
233: 17           rla
234: 17           rla
235: ca 47 02     jp   z,$0247
238: da 41 02     jp   c,$0241
23b: 3c           inc  a
23c: 4f           ld   c,a
23d: 5a           ld   e,d
23e: c3 47 02     jp   $0247
241: c6 02        add  a,$02
243: 47           ld   b,a
244: 57           ld   d,a
245: 87           add  a,a
246: 5f           ld   e,a
247: 72           ld   (hl),d
248: 23           inc  hl
249: 73           ld   (hl),e
24a: 23           inc  hl
24b: 70           ld   (hl),b
24c: 23           inc  hl
24d: 71           ld   (hl),c
24e: 23           inc  hl
24f: 3a 80 7d     ld   a,($7D80)
252: 07           rlca
253: 3e 01        ld   a,$01
255: da 59 02     jp   c,$0259
258: 3d           dec  a
259: 77           ld   (hl),a
25a: 21 65 35     ld   hl,$3565
25d: 11 00 61     ld   de,$6100
260: 01 aa 00     ld   bc,$00AA
263: ed b0        ldir
265: c9           ret

; clear ram at $6000 ($1000 bytes --> region is only $BFF)
; a = 0, b = $10, c = 0 -> $100 * $10 = 0x1000
266: 06 10        ld   b,$10
268: 21 00 60     ld   hl,$6000
26b: af           xor  a
26c: 4f           ld   c,a
26d: 77           ld   (hl),a
26e: 23           inc  hl
26f: 0d           dec  c
270: 20 fb        jr   nz,$026D
272: 10 f8        djnz $026C
; clear sprite ram $7000 ($300 bytes)
; a = 0, b = 4, c = 0 -> $400
274: 06 04        ld   b,$04
276: 21 00 70     ld   hl,$7000
279: 4f           ld   c,a
27a: 77           ld   (hl),a
27b: 23           inc  hl
27c: 0d           dec  c
27d: 20 fb        jr   nz,$027A
27f: 10 f8        djnz $0279
; set tile ram $7400..77ff to $10 -> clear tile screen with spaces ' ' = $10 
; a = $10, b = 4, c = 0 -> 0x400
281: 06 04        ld   b,$04
283: 3e 10        ld   a,$10
285: 21 00 74     ld   hl,$7400
288: 0e 00        ld   c,$00
28a: 77           ld   (hl),a
28b: 23           inc  hl
28c: 0d           dec  c
28d: 20 fb        jr   nz,$028A
28f: 10 f7        djnz $0288
; set main ram region $60c0..$60ff to $ff, size $40
; a = $ff, b = $40
291: 21 c0 60     ld   hl,$60C0
294: 06 40        ld   b,$40
296: 3e ff        ld   a,$FF
298: 77           ld   (hl),a
299: 23           inc  hl
29a: 10 fc        djnz $0298
; a = $c0, set variable1? variable2? to $c0 (192)
29c: 3e c0        ld   a,$C0
29e: 32 b0 60     ld   ($60B0),a
2a1: 32 b1 60     ld   ($60B1),a
; a = 0, 
; 7d83 sprite bank  -> 0
; 7d86 palette bank -> 0
; 7d87 palette bank -> 0
2a4: af           xor  a
2a5: 32 83 7d     ld   ($7D83),a
2a8: 32 86 7d     ld   ($7D86),a
2ab: 32 87 7d     ld   ($7D87),a
; a = 1
; 7d82 flip screen  -> 1
2ae: 3c           inc  a
2af: 32 82 7d     ld   ($7D82),a
; switch stackpointer sp = $6c00
2b2: 31 00 6c     ld   sp,$6C00
; init0
2b5: cd 1c 01     call $011C
; a = 1 nmi = 1
2b8: 3e 01        ld   a,$01
2ba: 32 84 7d     ld   ($7D84),a
; ???
;loop until $6383 change, timer, delay?
; h = 60, a = ($60B1) (c0) -> hl = 60c0
2bd: 26 60        ld   h,$60
2bf: 3a b1 60     ld   a,($60B1)
2c2: 6f           ld   l,a
; hl = 60c0
2c3: 7e           ld   a,(hl)
; a = ff -> a*2 
2c4: 87           add  a,a
; a = fe -> carry=1
2c5: 30 1c        jr   nc,$02E3   ; jump if carry=0
; draw numer of player 1UP to tile map  
2c7: cd 15 03     call $0315  
; draw lives to tile map L=00
2ca: cd 50 03     call $0350
;
2cd: 21 19 60     ld   hl,$6019
2d0: 34           inc  (hl)
2d1: 21 83 63     ld   hl,$6383
2d4: 3a 1a 60     ld   a,($601A)
2d7: be           cp   (hl)
2d8: 28 e3        jr   z,$02BD ; wait sound play?
; 
2da: 77           ld   (hl),a
;---------------------------------------------
; display 
;              insert coin
;             player    coin
;               1        1
;               2        2  
2db: cd 7f 03     call $037F
2de: cd a2 03     call $03A2
; draw 
;              CREDIT 00
2e1: 18 da        jr   $02BD
; draw hig score table
2e3: e6 1f        and  $1F
2e5: 5f           ld   e,a
2e6: 16 00        ld   d,$00
2e8: 36 ff        ld   (hl),$FF
2ea: 2c           inc  l
2eb: 4e           ld   c,(hl)
2ec: 36 ff        ld   (hl),$FF
2ee: 2c           inc  l
2ef: 7d           ld   a,l
2f0: fe c0        cp   $C0
2f2: 30 02        jr   nc,$02F6
2f4: 3e c0        ld   a,$C0
2f6: 32 b1 60     ld   ($60B1),a
2f9: 79           ld   a,c
2fa: 21 bd 02     ld   hl,$02BD
2fd: e5           push hl
2fe: 21 07 03     ld   hl,$0307
301: 19           add  hl,de
302: 5e           ld   e,(hl)
303: 23           inc  hl
304: 56           ld   d,(hl)
305: eb           ex   de,hl
306: e9           jp   (hl)
307: 1c           inc  e
308: 05           dec  b
309: 9b           sbc  a,e
30a: 05           dec  b
30b: c6 05        add  a,$05
30d: e9           jp   (hl)
30e: 05           dec  b
30f: 11 06 2a     ld   de,$2A06
312: 06 b8        ld   b,$B8
314: 06 3a        ld   b,$3A
316: 1a           ld   a,(de)
317: 60           ld   h,b
318: 47           ld   b,a
319: e6 0f        and  $0F
31b: c0           ret  nz
31c: cf           rst  $08
31d: 3a 0d 60     ld   a,($600D)
320: cd 47 03     call $0347
323: 11 e0 ff     ld   de,$FFE0
326: cb 60        bit  4,b
328: 28 14        jr   z,$033E
32a: 3e 10        ld   a,$10
32c: 77           ld   (hl),a
32d: 19           add  hl,de
32e: 77           ld   (hl),a
32f: 19           add  hl,de
330: 77           ld   (hl),a
331: 3a 0f 60     ld   a,($600F)
334: a7           and  a
335: c8           ret  z
336: 3a 0d 60     ld   a,($600D)
339: ee 01        xor  $01
33b: cd 47 03     call $0347
33e: 3c           inc  a
33f: 77           ld   (hl),a
340: 19           add  hl,de
341: 36 25        ld   (hl),$25
343: 19           add  hl,de
344: 36 20        ld   (hl),$20
346: c9           ret
347: 21 40 77     ld   hl,$7740
34a: a7           and  a
34b: c8           ret  z
34c: 21 e0 74     ld   hl,$74E0
34f: c9           ret
350: 3a 2d 62     ld   a,($622D)
353: a7           and  a
354: c0           ret  nz
355: 21 b3 60     ld   hl,$60B3
358: 3a 0d 60     ld   a,($600D)
35b: a7           and  a
35c: 28 03        jr   z,$0361
35e: 21 b6 60     ld   hl,$60B6
361: 7e           ld   a,(hl)
362: e6 f0        and  $F0
364: 47           ld   b,a
365: 23           inc  hl
366: 7e           ld   a,(hl)
367: e6 0f        and  $0F
369: b0           or   b
36a: 0f           rrca
36b: 0f           rrca
36c: 0f           rrca
36d: 0f           rrca
36e: 21 21 60     ld   hl,$6021
371: be           cp   (hl)
372: d8           ret  c
373: 3e 01        ld   a,$01
375: 32 2d 62     ld   ($622D),a
378: 21 28 62     ld   hl,$6228
37b: 34           inc  (hl)
37c: c3 b8 06     jp   $06B8
37f: 21 84 63     ld   hl,$6384
382: 7e           ld   a,(hl)
383: 34           inc  (hl)
384: a7           and  a
385: c0           ret  nz
386: 21 81 63     ld   hl,$6381
389: 7e           ld   a,(hl)
38a: 47           ld   b,a
38b: 34           inc  (hl)
38c: e6 07        and  $07
38e: c0           ret  nz
38f: 78           ld   a,b
390: 0f           rrca
391: 0f           rrca
392: 0f           rrca
393: 47           ld   b,a
394: 3a 29 62     ld   a,($6229)
397: 80           add  a,b
398: fe 05        cp   $05
39a: 38 02        jr   c,$039E
39c: 3e 05        ld   a,$05
39e: 32 80 63     ld   ($6380),a
3a1: c9           ret
3a2: 3e 03        ld   a,$03
3a4: f7           rst  $30
3a5: d7           rst  $10
3a6: 3a 50 63     ld   a,($6350)
3a9: 0f           rrca
3aa: d8           ret  c
3ab: 21 b8 62     ld   hl,$62B8
3ae: 35           dec  (hl)
3af: c0           ret  nz
3b0: 36 04        ld   (hl),$04
3b2: 3a b9 62     ld   a,($62B9)
3b5: 0f           rrca
3b6: d0           ret  nc
3b7: 21 29 6a     ld   hl,$6A29
3ba: 06 40        ld   b,$40
3bc: dd 21 a0 66  ld   ix,$66A0
3c0: 0f           rrca
3c1: d2 e4 03     jp   nc,$03E4
3c4: dd 36 09 02  ld   (ix+$09),$02
3c8: dd 36 0a 02  ld   (ix+$0a),$02
3cc: 04           inc  b
3cd: 04           inc  b
3ce: cd f2 03     call $03F2
3d1: 21 ba 62     ld   hl,$62BA
3d4: 35           dec  (hl)
3d5: c0           ret  nz
3d6: 3e 01        ld   a,$01
3d8: 32 b9 62     ld   ($62B9),a
3db: 32 a0 63     ld   ($63A0),a
3de: 3e 10        ld   a,$10
3e0: 32 ba 62     ld   ($62BA),a
3e3: c9           ret
3e4: dd 36 09 02  ld   (ix+$09),$02
3e8: dd 36 0a 00  ld   (ix+$0a),$00
3ec: cd f2 03     call $03F2
3ef: c3 de 03     jp   $03DE
3f2: 70           ld   (hl),b
3f3: 3a 19 60     ld   a,($6019)
3f6: 0f           rrca
3f7: d8           ret  c
3f8: 04           inc  b
3f9: 70           ld   (hl),b
3fa: c9           ret
3fb: 3a 27 62     ld   a,($6227)
3fe: fe 02        cp   $02
400: c2 13 04     jp   nz,$0413
403: 21 08 69     ld   hl,$6908
406: 3a a3 63     ld   a,($63A3)
409: 4f           ld   c,a
40a: ff           rst  $38
40b: 3a 10 69     ld   a,($6910)
40e: d6 3b        sub  $3B
410: 32 b7 63     ld   ($63B7),a
413: 3a 91 63     ld   a,($6391)
416: a7           and  a
417: c2 26 04     jp   nz,$0426
41a: 3a 1a 60     ld   a,($601A)
41d: a7           and  a
41e: c2 86 04     jp   nz,$0486
421: 3e 01        ld   a,$01
423: 32 91 63     ld   ($6391),a
426: 21 90 63     ld   hl,$6390
429: 34           inc  (hl)
42a: 7e           ld   a,(hl)
42b: fe 80        cp   $80
42d: ca 64 04     jp   z,$0464
430: 3a 93 63     ld   a,($6393)
433: a7           and  a
434: c2 86 04     jp   nz,$0486
437: 7e           ld   a,(hl)
438: 47           ld   b,a
439: e6 1f        and  $1F
43b: c2 86 04     jp   nz,$0486
43e: 21 cf 39     ld   hl,$39CF
441: cb 68        bit  5,b
443: 20 03        jr   nz,$0448
445: 21 f7 39     ld   hl,$39F7
448: cd 4e 00     call $004E
44b: 3e 03        ld   a,$03
44d: 32 82 60     ld   ($6082),a
450: 3a 27 62     ld   a,($6227)
453: 0f           rrca
454: d2 78 04     jp   nc,$0478
457: 0f           rrca
458: da 86 04     jp   c,$0486
45b: 21 0b 69     ld   hl,$690B
45e: 0e fc        ld   c,$FC
460: ff           rst  $38
461: c3 86 04     jp   $0486
464: af           xor  a
465: 77           ld   (hl),a
466: 23           inc  hl
467: 77           ld   (hl),a
468: 3a 93 63     ld   a,($6393)
46b: a7           and  a
46c: c2 86 04     jp   nz,$0486
46f: 21 5c 38     ld   hl,$385C
472: cd 4e 00     call $004E
475: c3 50 04     jp   $0450
478: 21 08 69     ld   hl,$6908
47b: 0e 44        ld   c,$44
47d: 0f           rrca
47e: d2 85 04     jp   nc,$0485
481: 3a b7 63     ld   a,($63B7)
484: 4f           ld   c,a
485: ff           rst  $38
486: 3a 90 63     ld   a,($6390)
489: 4f           ld   c,a
48a: 11 20 00     ld   de,$0020
48d: 3a 27 62     ld   a,($6227)
490: fe 04        cp   $04
492: ca be 04     jp   z,$04BE
495: 79           ld   a,c
496: a7           and  a
497: ca a1 04     jp   z,$04A1
49a: 3e ef        ld   a,$EF
49c: cb 71        bit  6,c
49e: c2 a3 04     jp   nz,$04A3
4a1: 3e 10        ld   a,$10
4a3: 21 c4 75     ld   hl,$75C4
4a6: cd 14 05     call $0514
4a9: 3a 05 69     ld   a,($6905)
4ac: 32 05 69     ld   ($6905),a
4af: cb 71        bit  6,c
4b1: c8           ret  z
4b2: 47           ld   b,a
4b3: 79           ld   a,c
4b4: e6 07        and  $07
4b6: c0           ret  nz
4b7: 78           ld   a,b
4b8: ee 03        xor  $03
4ba: 32 05 69     ld   ($6905),a
4bd: c9           ret
4be: 3e 10        ld   a,$10
4c0: 21 23 76     ld   hl,$7623
4c3: cd 14 05     call $0514
4c6: 21 83 75     ld   hl,$7583
4c9: cd 14 05     call $0514
4cc: cb 71        bit  6,c
4ce: ca 09 05     jp   z,$0509
4d1: 3a 03 62     ld   a,($6203)
4d4: fe 80        cp   $80
4d6: d2 f1 04     jp   nc,$04F1
4d9: 3e df        ld   a,$DF
4db: 21 23 76     ld   hl,$7623
4de: cd 14 05     call $0514
4e1: 3a 01 69     ld   a,($6901)
4e4: f6 80        or   $80
4e6: 32 01 69     ld   ($6901),a
4e9: 3a 05 69     ld   a,($6905)
4ec: f6 80        or   $80
4ee: c3 ac 04     jp   $04AC
4f1: 3e ef        ld   a,$EF
4f3: 21 83 75     ld   hl,$7583
4f6: cd 14 05     call $0514
4f9: 3a 01 69     ld   a,($6901)
4fc: e6 7f        and  $7F
4fe: 32 01 69     ld   ($6901),a
501: 3a 05 69     ld   a,($6905)
504: e6 7f        and  $7F
506: c3 ac 04     jp   $04AC
509: 3a 03 62     ld   a,($6203)
50c: fe 80        cp   $80
50e: d2 f9 04     jp   nc,$04F9
511: c3 e1 04     jp   $04E1
514: 06 03        ld   b,$03
516: 77           ld   (hl),a
517: 19           add  hl,de
518: 3d           dec  a
519: 10 fb        djnz $0516
51b: c9           ret
51c: 4f           ld   c,a
51d: cf           rst  $08
51e: cd 5f 05     call $055F
521: 79           ld   a,c
522: 81           add  a,c
523: 81           add  a,c
524: 4f           ld   c,a
525: 21 29 35     ld   hl,$3529
528: 06 00        ld   b,$00
52a: 09           add  hl,bc
52b: a7           and  a
52c: 06 03        ld   b,$03
52e: 1a           ld   a,(de)
52f: 8e           adc  a,(hl)
530: 27           daa
531: 12           ld   (de),a
532: 13           inc  de
533: 23           inc  hl
534: 10 f8        djnz $052E
536: d5           push de
537: 1b           dec  de
538: 3a 0d 60     ld   a,($600D)
53b: cd 6b 05     call $056B
53e: d1           pop  de
53f: 1b           dec  de
540: 21 ba 60     ld   hl,$60BA
543: 06 03        ld   b,$03
545: 1a           ld   a,(de)
546: be           cp   (hl)
547: d8           ret  c
548: c2 50 05     jp   nz,$0550
54b: 1b           dec  de
54c: 2b           dec  hl
54d: 10 f6        djnz $0545
54f: c9           ret
550: cd 5f 05     call $055F
553: 21 b8 60     ld   hl,$60B8
556: 1a           ld   a,(de)
557: 77           ld   (hl),a
558: 13           inc  de
559: 23           inc  hl
55a: 10 fa        djnz $0556
55c: c3 da 05     jp   $05DA
55f: 11 b2 60     ld   de,$60B2
562: 3a 0d 60     ld   a,($600D)
565: a7           and  a
566: c8           ret  z
567: 11 b5 60     ld   de,$60B5
56a: c9           ret
56b: dd 21 81 77  ld   ix,$7781
56f: a7           and  a
570: 28 0a        jr   z,$057C
572: dd 21 21 75  ld   ix,$7521
576: 18 04        jr   $057C
578: dd 21 41 76  ld   ix,$7641
57c: eb           ex   de,hl
57d: 11 e0 ff     ld   de,$FFE0
580: 01 04 03     ld   bc,$0304
; write high score points 007650
583: 7e           ld   a,(hl)
584: 0f           rrca
585: 0f           rrca
586: 0f           rrca
587: 0f           rrca
; one digit
588: cd 93 05     call $0593
58b: 7e           ld   a,(hl)
; second digit
58c: cd 93 05     call $0593
58f: 2b           dec  hl
590: 10 f1        djnz $0583
592: c9           ret

593: e6 0f        and  $0F
595: dd 77 00     ld   (ix+$00),a
598: dd 19        add  ix,de
59a: c9           ret
59b: fe 03        cp   $03
59d: d2 bd 05     jp   nc,$05BD
5a0: f5           push af
5a1: 21 b2 60     ld   hl,$60B2
5a4: a7           and  a
5a5: ca ab 05     jp   z,$05AB
5a8: 21 b5 60     ld   hl,$60B5
5ab: fe 02        cp   $02
5ad: c2 b3 05     jp   nz,$05B3
5b0: 21 b8 60     ld   hl,$60B8
5b3: af           xor  a
5b4: 77           ld   (hl),a
5b5: 23           inc  hl
5b6: 77           ld   (hl),a
5b7: 23           inc  hl
5b8: 77           ld   (hl),a
5b9: f1           pop  af
5ba: c3 c6 05     jp   $05C6
5bd: 3d           dec  a
5be: f5           push af
5bf: cd 9b 05     call $059B
5c2: f1           pop  af
5c3: c8           ret  z
5c4: 18 f7        jr   $05BD
5c6: fe 03        cp   $03
5c8: ca e0 05     jp   z,$05E0
5cb: 11 b4 60     ld   de,$60B4
5ce: a7           and  a
5cf: ca d5 05     jp   z,$05D5
5d2: 11 b7 60     ld   de,$60B7
5d5: fe 02        cp   $02
5d7: c2 6b 05     jp   nz,$056B
5da: 11 ba 60     ld   de,$60BA
5dd: c3 78 05     jp   $0578
5e0: 3d           dec  a
5e1: f5           push af
5e2: cd c6 05     call $05C6
5e5: f1           pop  af
5e6: c8           ret  z
5e7: 18 f7        jr   $05E0
5e9: 21 4b 36     ld   hl,$364B
5ec: 87           add  a,a
5ed: f5           push af
5ee: e6 7f        and  $7F
5f0: 5f           ld   e,a
5f1: 16 00        ld   d,$00
5f3: 19           add  hl,de
5f4: 5e           ld   e,(hl)
5f5: 23           inc  hl
5f6: 56           ld   d,(hl)
5f7: eb           ex   de,hl
5f8: 5e           ld   e,(hl)
5f9: 23           inc  hl
5fa: 56           ld   d,(hl)
5fb: 23           inc  hl
5fc: 01 e0 ff     ld   bc,$FFE0
5ff: eb           ex   de,hl
600: 1a           ld   a,(de)
601: fe 3f        cp   $3F  ; string end reached?
603: ca 26 00     jp   z,$0026  ; yes jump to $0026
; print HIGH  see $36b4:  $18 $19 $17 $18 $10  $23 $13 $1f $22 $15 $3F
;                         H   I   G   H   Spc  S   C   O   R   E   StrEnd
606: 77           ld   (hl),a
607: f1           pop  af
608: 30 02        jr   nc,$060C
60a: 36 10        ld   (hl),$10
60c: f5           push af
60d: 13           inc  de
60e: 09           add  hl,bc
60f: 18 ef        jr   $0600
611: 3a 07 60     ld   a,($6007)
614: 0f           rrca
615: d0           ret  nc
616: 3e 05        ld   a,$05
618: cd e9 05     call $05E9
61b: 21 01 60     ld   hl,$6001
61e: 11 e0 ff     ld   de,$FFE0
621: dd 21 bf 74  ld   ix,$74BF
625: 06 01        ld   b,$01
627: c3 83 05     jp   $0583
62a: a7           and  a
62b: ca 91 06     jp   z,$0691
62e: 3a 8c 63     ld   a,($638C)
631: a7           and  a
632: c2 a8 06     jp   nz,$06A8
635: 3a b8 63     ld   a,($63B8)
638: a7           and  a
639: c0           ret  nz
63a: 3a b0 62     ld   a,($62B0)
63d: 01 0a 00     ld   bc,$000A
640: 04           inc  b
641: 91           sub  c
642: c2 40 06     jp   nz,$0640
645: 78           ld   a,b
646: 07           rlca
647: 07           rlca
648: 07           rlca
649: 07           rlca
64a: 32 8c 63     ld   ($638C),a
64d: 21 4a 38     ld   hl,$384A
650: 11 65 74     ld   de,$7465
653: 3e 06        ld   a,$06
655: dd 21 1d 00  ld   ix,$001D
659: 01 03 00     ld   bc,$0003
65c: ed b0        ldir
65e: dd 19        add  ix,de
660: dd e5        push ix
662: d1           pop  de
663: 3d           dec  a
664: c2 55 06     jp   nz,$0655
667: 3a 8c 63     ld   a,($638C)
66a: 4f           ld   c,a
66b: e6 0f        and  $0F
66d: 47           ld   b,a
66e: 79           ld   a,c
66f: 0f           rrca
670: 0f           rrca
671: 0f           rrca
672: 0f           rrca
673: e6 0f        and  $0F
675: c2 89 06     jp   nz,$0689
678: 3e 03        ld   a,$03
67a: 32 89 60     ld   ($6089),a
67d: 3e 70        ld   a,$70
67f: 32 86 74     ld   ($7486),a
682: 32 a6 74     ld   ($74A6),a
685: 80           add  a,b
686: 47           ld   b,a
687: 3e 10        ld   a,$10
689: 32 e6 74     ld   ($74E6),a
68c: 78           ld   a,b
68d: 32 c6 74     ld   ($74C6),a
690: c9           ret
691: 3a 8c 63     ld   a,($638C)
694: 47           ld   b,a
695: e6 0f        and  $0F
697: c5           push bc
698: cd 1c 05     call $051C
69b: c1           pop  bc
69c: 78           ld   a,b
69d: 0f           rrca
69e: 0f           rrca
69f: 0f           rrca
6a0: 0f           rrca
6a1: e6 0f        and  $0F
6a3: c6 0a        add  a,$0A
6a5: c3 1c 05     jp   $051C
6a8: d6 01        sub  $01
6aa: 20 05        jr   nz,$06B1
6ac: 21 b8 63     ld   hl,$63B8
6af: 36 01        ld   (hl),$01
6b1: 27           daa
6b2: 32 8c 63     ld   ($638C),a
6b5: c3 6a 06     jp   $066A
6b8: 4f           ld   c,a
6b9: cf           rst  $08
6ba: 06 06        ld   b,$06
6bc: 11 e0 ff     ld   de,$FFE0
6bf: 21 83 77     ld   hl,$7783
6c2: 36 10        ld   (hl),$10
6c4: 19           add  hl,de
6c5: 10 fb        djnz $06C2
6c7: 3a 28 62     ld   a,($6228)
6ca: 91           sub  c
6cb: ca d7 06     jp   z,$06D7
6ce: 47           ld   b,a
6cf: 21 83 77     ld   hl,$7783
6d2: 36 ff        ld   (hl),$FF
6d4: 19           add  hl,de
6d5: 10 fb        djnz $06D2
; write 'L' to screen
6d7: 21 03 75     ld   hl,$7503
6da: 36 1c        ld   (hl),$1C
; write '=' to screen
6dc: 21 e3 74     ld   hl,$74E3
6df: 36 34        ld   (hl),$34
; load number lives var at $6229
6e1: 3a 29 62     ld   a,($6229)
; >= 100?
6e4: fe 64        cp   $64
6e6: 38 05        jr   c,$06ED
; limit to 99
6e8: 3e 63        ld   a,$63
; save number lives var at $6229
6ea: 32 29 62     ld   ($6229),a
; hex to number
6ed: 01 0a ff     ld   bc,$FF0A
6f0: 04           inc  b
6f1: 91           sub  c
6f2: d2 f0 06     jp   nc,$06F0
6f5: 81           add  a,c
; write lives '03' to screen 
; a =  1-digit
6f6: 32 a3 74     ld   ($74A3),a
; a = 10-digit
6f9: 78           ld   a,b
6fa: 32 c3 74     ld   ($74C3),a
6fd: c9           ret
;
6fe: 3a 0a 60     ld   a,($600A)
701: ef           rst  $28
702: 86           add  a,(hl)
703: 09           add  hl,bc
704: ab           xor  e
705: 09           add  hl,bc
706: d6 09        sub  $09
708: fe 09        cp   $09
70a: 1b           dec  de
70b: 0a           ld   a,(bc)
70c: 37           scf
70d: 0a           ld   a,(bc)
70e: 63           ld   h,e
70f: 0a           ld   a,(bc)
710: 76           halt
711: 0a           ld   a,(bc)
712: da 0b 00     jp   c,$000B
715: 00           nop
716: 91           sub  c
717: 0c           inc  c
718: 3c           inc  a
719: 12           ld   (de),a
71a: 7a           ld   a,d
71b: 19           add  hl,de
71c: 7c           ld   a,h
71d: 12           ld   (de),a
71e: f2 12 44     jp   p,$4412
721: 13           inc  de
722: 8f           adc  a,a
723: 13           inc  de
724: a1           and  c
725: 13           inc  de
726: aa           xor  d
727: 13           inc  de
728: bb           cp   e
729: 13           inc  de
72a: 1e 14        ld   e,$14
72c: 86           add  a,(hl)
72d: 14           inc  d
72e: 15           dec  d
72f: 16 6b        ld   d,$6B
731: 19           add  hl,de
732: 00           nop
733: 00           nop
734: 00           nop
735: 00           nop
736: 00           nop
737: 00           nop
738: 00           nop
739: 00           nop
73a: 00           nop
73b: 00           nop
73c: 21 0a 60     ld   hl,$600A
73f: 3a 01 60     ld   a,($6001)
742: a7           and  a
743: c2 5c 07     jp   nz,$075C
746: 7e           ld   a,(hl)
747: ef           rst  $28
748: 79           ld   a,c
749: 07           rlca
74a: 63           ld   h,e
74b: 07           rlca
74c: 3c           inc  a
74d: 12           ld   (de),a
74e: 77           ld   (hl),a
74f: 19           add  hl,de
750: 7c           ld   a,h
751: 12           ld   (de),a
752: c3 07 cb     jp   $CB07
755: 07           rlca
756: 4b           ld   c,e
757: 08           ex   af,af'
758: 00           nop
759: 00           nop
75a: 00           nop
75b: 00           nop
75c: 36 00        ld   (hl),$00
75e: 21 05 60     ld   hl,$6005
761: 34           inc  (hl)
762: c9           ret
763: e7           rst  $20
764: af           xor  a
765: 32 92 63     ld   ($6392),a
768: 32 a0 63     ld   ($63A0),a
76b: 3e 01        ld   a,$01
76d: 32 27 62     ld   ($6227),a
770: 32 29 62     ld   ($6229),a
773: 32 28 62     ld   ($6228),a
776: c3 92 0c     jp   $0C92
779: 21 86 7d     ld   hl,$7D86
77c: 36 00        ld   (hl),$00
77e: 23           inc  hl
77f: 36 00        ld   (hl),$00
781: 11 1b 03     ld   de,$031B
784: cd 9f 30     call $309F
787: 1c           inc  e
788: cd 9f 30     call $309F
78b: cd 65 09     call $0965
78e: 21 09 60     ld   hl,$6009
791: 36 02        ld   (hl),$02
793: 23           inc  hl
794: 34           inc  (hl)
795: cd 74 08     call $0874
798: cd 53 0a     call $0A53
79b: 3a 0f 60     ld   a,($600F)
79e: fe 01        cp   $01
7a0: cc ee 09     call z,$09EE
7a3: ed 5b 22 60  ld   de,($6022)
7a7: 21 6c 75     ld   hl,$756C
7aa: cd ad 07     call $07AD
7ad: 73           ld   (hl),e
7ae: 23           inc  hl
7af: 23           inc  hl
7b0: 72           ld   (hl),d
7b1: 7a           ld   a,d
7b2: d6 0a        sub  $0A
7b4: c2 bc 07     jp   nz,$07BC
7b7: 77           ld   (hl),a
7b8: 3c           inc  a
7b9: 32 8e 75     ld   ($758E),a
7bc: 11 01 02     ld   de,$0201
7bf: 21 8c 76     ld   hl,$768C
7c2: c9           ret
7c3: cd 74 08     call $0874
7c6: 21 0a 60     ld   hl,$600A
7c9: 34           inc  (hl)
7ca: c9           ret
7cb: 3a 8a 63     ld   a,($638A)
7ce: fe 00        cp   $00
7d0: c2 2d 08     jp   nz,$082D
7d3: 3e 60        ld   a,$60
7d5: 32 8a 63     ld   ($638A),a
7d8: 0e 5f        ld   c,$5F
7da: fe 00        cp   $00
7dc: ca 3b 08     jp   z,$083B
7df: 21 86 7d     ld   hl,$7D86
7e2: 36 00        ld   (hl),$00
7e4: 79           ld   a,c
7e5: cb 07        rlc  a
7e7: 30 02        jr   nc,$07EB
7e9: 36 01        ld   (hl),$01
7eb: 23           inc  hl
7ec: 36 00        ld   (hl),$00
7ee: cb 07        rlc  a
7f0: 30 02        jr   nc,$07F4
7f2: 36 01        ld   (hl),$01
7f4: 32 8b 63     ld   ($638B),a
7f7: 21 08 3d     ld   hl,$3D08
7fa: 3e b0        ld   a,$B0
7fc: 46           ld   b,(hl)
7fd: 23           inc  hl
7fe: 5e           ld   e,(hl)
7ff: 23           inc  hl
800: 56           ld   d,(hl)
801: 12           ld   (de),a
802: 13           inc  de
803: 10 fc        djnz $0801
805: 23           inc  hl
806: 7e           ld   a,(hl)
807: fe 00        cp   $00
809: c2 fa 07     jp   nz,$07FA
80c: 11 1e 03     ld   de,$031E
80f: cd 9f 30     call $309F
812: 13           inc  de
813: cd 9f 30     call $309F
816: 21 cf 39     ld   hl,$39CF
819: 00           nop
81a: 00           nop
81b: 00           nop
81c: 00           nop
81d: cd 4e 00     call $004E
820: 21 08 69     ld   hl,$6908
823: 0e 44        ld   c,$44
825: ff           rst  $38
826: 21 0b 69     ld   hl,$690B
829: 0e 78        ld   c,$78
82b: ff           rst  $38
82c: c9           ret
82d: 3a 8b 63     ld   a,($638B)
830: 4f           ld   c,a
831: 3a 8a 63     ld   a,($638A)
834: 3d           dec  a
835: 32 8a 63     ld   ($638A),a
838: c3 da 07     jp   $07DA
83b: 21 09 60     ld   hl,$6009
83e: 36 02        ld   (hl),$02
840: 23           inc  hl
841: 34           inc  (hl)
842: 21 8a 63     ld   hl,$638A
845: 36 00        ld   (hl),$00
847: 23           inc  hl
848: 36 00        ld   (hl),$00
84a: c9           ret
84b: e7           rst  $20
84c: 21 0a 60     ld   hl,$600A
84f: 36 00        ld   (hl),$00
851: c9           ret

; function: init vram 7400..78ff with $10
; init vram and clear sprite area?
init_vram:
852: 21 00 74     ld   hl,$7400              ; load base vram hl=$7400   
855: 0e 04        ld   c,$04                 ; 4 * 0x100 bytes
; cloop1
857: 06 00        ld   b,$00                 ; 
859: 3e 10        ld   a,$10                 ; a=$10 
; cloop2
85b: 77           ld   (hl),a                ; (hl)=a
85c: 23           inc  hl                    ; hl=hl+1 next fill address
85d: 10 fc        djnz $085B                 ; b=b-1 if nz jump 085b next cloop2
85f: 0d           dec  c                     ; c=c-1
860: c2 57 08     jp   nz,$0857              ; jp nz next c  -> cloop1

; function: clear sprite init ram 6900..6a7f (6a80) with $10
; $6900 - local sprite ram 
863: 21 00 69     ld   hl,$6900              ; load base vram hl=$6900    ???
866: 0e 02        ld   c,$02                 ; 2 * 0xc0 bytes = $180 bytes
; cloop3
868: 06 c0        ld   b,$C0
86a: af           xor  a                     ; clear a
; cloop4
86b: 77           ld   (hl),a                ; (hl)=0 
86c: 23           inc  hl                    ; hl=hl+1 next fill address
86d: 10 fc        djnz $086B                 ; b=b-1 if nz jump 085b next cloop4
86f: 0d           dec  c                     ; c=c-1 
870: c2 68 08     jp   nz,$0868              ; jp nz next c -> cloop3  
873: c9           ret                         

874: 21 04 74     ld   hl,$7404
877: 0e 20        ld   c,$20
879: 06 1c        ld   b,$1C
87b: 3e 10        ld   a,$10
87d: 11 04 00     ld   de,$0004
880: 77           ld   (hl),a
881: 23           inc  hl
882: 10 fc        djnz $0880
884: 19           add  hl,de
885: 0d           dec  c
886: c2 79 08     jp   nz,$0879
889: 21 22 75     ld   hl,$7522
88c: 11 20 00     ld   de,$0020
88f: 0e 02        ld   c,$02
891: 3e 10        ld   a,$10
893: 06 0e        ld   b,$0E
895: 77           ld   (hl),a
896: 19           add  hl,de
897: 10 fc        djnz $0895
899: 21 23 75     ld   hl,$7523
89c: 0d           dec  c
89d: c2 93 08     jp   nz,$0893
8a0: 21 00 69     ld   hl,$6900
8a3: 06 00        ld   b,$00
8a5: 3e 00        ld   a,$00
8a7: 77           ld   (hl),a
8a8: 23           inc  hl
8a9: 10 fc        djnz $08A7
8ab: 06 80        ld   b,$80
8ad: 77           ld   (hl),a
8ae: 23           inc  hl
8af: 10 fc        djnz $08AD
8b1: c9           ret
8b2: 3a 0a 60     ld   a,($600A)
8b5: ef           rst  $28
8b6: ba           cp   d
8b7: 08           ex   af,af'
8b8: f8           ret  m
8b9: 08           ex   af,af'
8ba: cd 74 08     call $0874
8bd: af           xor  a
8be: 32 07 60     ld   ($6007),a
8c1: 11 0c 03     ld   de,$030C
8c4: cd 9f 30     call $309F
8c7: 21 0a 60     ld   hl,$600A
8ca: 34           inc  (hl)
8cb: cd 65 09     call $0965
8ce: af           xor  a
8cf: 21 86 7d     ld   hl,$7D86
8d2: 77           ld   (hl),a
8d3: 2c           inc  l
8d4: 77           ld   (hl),a
8d5: 06 04        ld   b,$04
8d7: 1e 09        ld   e,$09
8d9: 3a 01 60     ld   a,($6001)
8dc: fe 01        cp   $01
8de: ca e4 08     jp   z,$08E4
8e1: 06 0c        ld   b,$0C
8e3: 1c           inc  e
8e4: 3a 1a 60     ld   a,($601A)
8e7: e6 07        and  $07
8e9: c2 f3 08     jp   nz,$08F3
8ec: 7b           ld   a,e
8ed: cd e9 05     call $05E9
8f0: cd 16 06     call $0616
8f3: 3a 00 7d     ld   a,($7D00)
8f6: a0           and  b
8f7: c9           ret
8f8: cd d5 08     call $08D5
8fb: fe 04        cp   $04
8fd: ca 06 09     jp   z,$0906
900: fe 08        cp   $08
902: ca 19 09     jp   z,$0919
905: c9           ret
906: cd 77 09     call $0977
909: 21 48 60     ld   hl,$6048
90c: 06 08        ld   b,$08
90e: af           xor  a
90f: 77           ld   (hl),a
910: 2c           inc  l
911: 10 fc        djnz $090F
913: 21 00 00     ld   hl,$0000
916: c3 38 09     jp   $0938
919: cd 77 09     call $0977
91c: cd 77 09     call $0977
91f: 11 48 60     ld   de,$6048
922: 3a 20 60     ld   a,($6020)
925: 12           ld   (de),a
926: 1c           inc  e
927: 21 5e 09     ld   hl,$095E
92a: 01 07 00     ld   bc,$0007
92d: ed b0        ldir
92f: 11 01 01     ld   de,$0101
932: cd 9f 30     call $309F
935: 21 00 01     ld   hl,$0100
938: 22 0e 60     ld   ($600E),hl
93b: cd 74 08     call $0874
93e: 11 40 60     ld   de,$6040
941: 3a 20 60     ld   a,($6020)
944: 12           ld   (de),a
945: 1c           inc  e
946: 21 5e 09     ld   hl,$095E
949: 01 07 00     ld   bc,$0007
94c: ed b0        ldir
94e: 11 00 01     ld   de,$0100
951: cd 9f 30     call $309F
954: af           xor  a
955: 32 0a 60     ld   ($600A),a
958: 3e 03        ld   a,$03
95a: 32 05 60     ld   ($6005),a
95d: c9           ret
95e: 01 65 3a     ld   bc,$3A65
961: 01 00 00     ld   bc,$0000
964: 00           nop
965: 11 00 04     ld   de,$0400
968: cd 9f 30     call $309F
96b: 11 14 03     ld   de,$0314
96e: 06 06        ld   b,$06
970: cd 9f 30     call $309F
973: 1c           inc  e
974: 10 fa        djnz $0970
976: c9           ret
977: 21 01 60     ld   hl,$6001
97a: 3e 99        ld   a,$99
97c: 86           add  a,(hl)
97d: 27           daa
97e: 77           ld   (hl),a
97f: 11 00 04     ld   de,$0400
982: cd 9f 30     call $309F
985: c9           ret
;---------------------------
986: cd 52 08     call $0852                                ; call init_vram
989: cd 1c 01     call $011C                                ; cal ???
98c: 11 82 7d     ld   de,$7D82
98f: 3e 01        ld   a,$01
991: 12           ld   (de),a
992: 21 0a 60     ld   hl,$600A
995: 3a 0e 60     ld   a,($600E)
998: a7           and  a
999: c2 9f 09     jp   nz,$099F
99c: 36 01        ld   (hl),$01
99e: c9           ret
99f: 3a 26 60     ld   a,($6026)
9a2: 3d           dec  a
9a3: ca a8 09     jp   z,$09A8
9a6: af           xor  a
9a7: 12           ld   (de),a
9a8: 36 03        ld   (hl),$03
9aa: c9           ret
9ab: 21 40 60     ld   hl,$6040
9ae: 11 28 62     ld   de,$6228
9b1: 01 08 00     ld   bc,$0008
9b4: ed b0        ldir
9b6: 2a 2a 62     ld   hl,($622A)
9b9: 7e           ld   a,(hl)
9ba: 32 27 62     ld   ($6227),a
9bd: 3a 0f 60     ld   a,($600F)
9c0: a7           and  a
9c1: 21 09 60     ld   hl,$6009
9c4: 11 0a 60     ld   de,$600A
9c7: ca d0 09     jp   z,$09D0
9ca: 36 78        ld   (hl),$78
9cc: eb           ex   de,hl
9cd: 36 02        ld   (hl),$02
9cf: c9           ret
9d0: 36 01        ld   (hl),$01
9d2: eb           ex   de,hl
9d3: 36 05        ld   (hl),$05
9d5: c9           ret
9d6: af           xor  a
9d7: 32 86 7d     ld   ($7D86),a
9da: 32 87 7d     ld   ($7D87),a
9dd: 11 02 03     ld   de,$0302
9e0: cd 9f 30     call $309F
9e3: 11 01 02     ld   de,$0201
9e6: cd 9f 30     call $309F
9e9: 3e 05        ld   a,$05
9eb: 32 0a 60     ld   ($600A),a
9ee: 3e 02        ld   a,$02
9f0: 32 e0 74     ld   ($74E0),a
9f3: 3e 25        ld   a,$25
9f5: 32 c0 74     ld   ($74C0),a
9f8: 3e 20        ld   a,$20
9fa: 32 a0 74     ld   ($74A0),a
9fd: c9           ret
9fe: 21 48 60     ld   hl,$6048
a01: 11 28 62     ld   de,$6228
a04: 01 08 00     ld   bc,$0008
a07: ed b0        ldir
a09: 2a 2a 62     ld   hl,($622A)
a0c: 7e           ld   a,(hl)
a0d: 32 27 62     ld   ($6227),a
a10: 3e 78        ld   a,$78
a12: 32 09 60     ld   ($6009),a
a15: 3e 04        ld   a,$04
a17: 32 0a 60     ld   ($600A),a
a1a: c9           ret
a1b: af           xor  a
a1c: 32 86 7d     ld   ($7D86),a
a1f: 32 87 7d     ld   ($7D87),a
a22: 11 03 03     ld   de,$0303
a25: cd 9f 30     call $309F
a28: 11 01 02     ld   de,$0201
a2b: cd 9f 30     call $309F
a2e: cd ee 09     call $09EE
a31: 3e 05        ld   a,$05
a33: 32 0a 60     ld   ($600A),a
a36: c9           ret
a37: 11 04 03     ld   de,$0304
a3a: cd 9f 30     call $309F
a3d: 11 02 02     ld   de,$0202
a40: cd 9f 30     call $309F
a43: 11 00 02     ld   de,$0200
a46: cd 9f 30     call $309F
a49: 11 00 06     ld   de,$0600
a4c: cd 9f 30     call $309F
a4f: 21 0a 60     ld   hl,$600A
a52: 34           inc  (hl)
a53: 3e 01        ld   a,$01
a55: 32 40 77     ld   ($7740),a
a58: 3e 25        ld   a,$25
a5a: 32 20 77     ld   ($7720),a
a5d: 3e 20        ld   a,$20
a5f: 32 00 77     ld   ($7700),a
a62: c9           ret
a63: df           rst  $18
a64: cd 74 08     call $0874
a67: 21 09 60     ld   hl,$6009
a6a: 36 01        ld   (hl),$01
a6c: 2c           inc  l
a6d: 34           inc  (hl)
a6e: 11 2c 62     ld   de,$622C
a71: 1a           ld   a,(de)
a72: a7           and  a
a73: c0           ret  nz
a74: 34           inc  (hl)
a75: c9           ret
a76: 3a 85 63     ld   a,($6385)
a79: ef           rst  $28
a7a: 8a           adc  a,d
a7b: 0a           ld   a,(bc)
a7c: bf           cp   a
a7d: 0a           ld   a,(bc)
a7e: e8           ret  pe
a7f: 0a           ld   a,(bc)
a80: 69           ld   l,c
a81: 30 06        jr   nc,$0A89
a83: 0b           dec  bc
a84: 69           ld   l,c
a85: 30 68        jr   nc,$0AEF
a87: 0b           dec  bc
a88: b3           or   e
a89: 0b           dec  bc
a8a: af           xor  a
a8b: 32 86 7d     ld   ($7D86),a
a8e: 3c           inc  a
a8f: 32 87 7d     ld   ($7D87),a
a92: 11 0d 38     ld   de,$380D
a95: cd a7 0d     call $0DA7
a98: 3e 10        ld   a,$10
a9a: 32 a3 76     ld   ($76A3),a
a9d: 32 63 76     ld   ($7663),a
aa0: 3e d4        ld   a,$D4
aa2: 32 aa 75     ld   ($75AA),a
aa5: af           xor  a
aa6: 32 af 62     ld   ($62AF),a
aa9: 21 b4 38     ld   hl,$38B4
aac: 22 c2 63     ld   ($63C2),hl
aaf: 21 cb 38     ld   hl,$38CB
ab2: 22 c4 63     ld   ($63C4),hl
ab5: 3e 40        ld   a,$40
ab7: 32 09 60     ld   ($6009),a
aba: 21 85 63     ld   hl,$6385
abd: 34           inc  (hl)
abe: c9           ret
abf: df           rst  $18
ac0: 21 8c 38     ld   hl,$388C
ac3: cd 4e 00     call $004E
ac6: 21 08 69     ld   hl,$6908
ac9: 0e 30        ld   c,$30
acb: ff           rst  $38
acc: 21 0b 69     ld   hl,$690B
acf: 0e 99        ld   c,$99
ad1: ff           rst  $38
ad2: 3e 1f        ld   a,$1F
ad4: 32 8e 63     ld   ($638E),a
ad7: af           xor  a
ad8: 32 0c 69     ld   ($690C),a
adb: 21 8a 60     ld   hl,$608A
ade: 36 01        ld   (hl),$01
ae0: 23           inc  hl
ae1: 36 03        ld   (hl),$03
ae3: 21 85 63     ld   hl,$6385
ae6: 34           inc  (hl)
ae7: c9           ret
ae8: cd 6f 30     call $306F
aeb: 3a af 62     ld   a,($62AF)
aee: e6 0f        and  $0F
af0: cc 4a 30     call z,$304A
af3: 3a 0b 69     ld   a,($690B)
af6: fe 5d        cp   $5D
af8: d0           ret  nc
af9: 3e 20        ld   a,$20
afb: 32 09 60     ld   ($6009),a
afe: 21 85 63     ld   hl,$6385
b01: 34           inc  (hl)
b02: 22 c0 63     ld   ($63C0),hl
b05: c9           ret
b06: 3a 1a 60     ld   a,($601A)
b09: 0f           rrca
b0a: d8           ret  c
b0b: 2a c2 63     ld   hl,($63C2)
b0e: 7e           ld   a,(hl)
b0f: fe 7f        cp   $7F
b11: ca 1e 0b     jp   z,$0B1E
b14: 23           inc  hl
b15: 22 c2 63     ld   ($63C2),hl
b18: 4f           ld   c,a
b19: 21 0b 69     ld   hl,$690B
b1c: ff           rst  $38
b1d: c9           ret
b1e: 21 5c 38     ld   hl,$385C
b21: cd 4e 00     call $004E
b24: 11 00 69     ld   de,$6900
b27: 01 08 00     ld   bc,$0008
b2a: ed b0        ldir
b2c: 21 08 69     ld   hl,$6908
b2f: 0e 50        ld   c,$50
b31: ff           rst  $38
b32: 21 0b 69     ld   hl,$690B
b35: 0e fc        ld   c,$FC
b37: ff           rst  $38
b38: cd 4a 30     call $304A
b3b: 3a 8e 63     ld   a,($638E)
b3e: fe 0a        cp   $0A
b40: c2 38 0b     jp   nz,$0B38
b43: 3e 03        ld   a,$03
b45: 32 82 60     ld   ($6082),a
b48: 11 2c 39     ld   de,$392C
b4b: cd a7 0d     call $0DA7
b4e: 3e 10        ld   a,$10
b50: 32 aa 74     ld   ($74AA),a
b53: 32 8a 74     ld   ($748A),a
b56: 3e 05        ld   a,$05
b58: 32 8d 63     ld   ($638D),a
b5b: 3e 20        ld   a,$20
b5d: 32 09 60     ld   ($6009),a
b60: 21 85 63     ld   hl,$6385
b63: 34           inc  (hl)
b64: 22 c0 63     ld   ($63C0),hl
b67: c9           ret
b68: 3a 1a 60     ld   a,($601A)
b6b: 0f           rrca
b6c: d8           ret  c
b6d: 2a c4 63     ld   hl,($63C4)
b70: 7e           ld   a,(hl)
b71: fe 7f        cp   $7F
b73: ca 86 0b     jp   z,$0B86
b76: 23           inc  hl
b77: 22 c4 63     ld   ($63C4),hl
b7a: 21 0b 69     ld   hl,$690B
b7d: 4f           ld   c,a
b7e: ff           rst  $38
b7f: 21 08 69     ld   hl,$6908
b82: 0e ff        ld   c,$FF
b84: ff           rst  $38
b85: c9           ret
b86: 21 cb 38     ld   hl,$38CB
b89: 22 c4 63     ld   ($63C4),hl
b8c: 3e 03        ld   a,$03
b8e: 32 82 60     ld   ($6082),a
b91: 21 dc 38     ld   hl,$38DC
b94: 3a 8d 63     ld   a,($638D)
b97: 3d           dec  a
b98: 07           rlca
b99: 07           rlca
b9a: 07           rlca
b9b: 07           rlca
b9c: 5f           ld   e,a
b9d: 16 00        ld   d,$00
b9f: 19           add  hl,de
ba0: eb           ex   de,hl
ba1: cd a7 0d     call $0DA7
ba4: 21 8d 63     ld   hl,$638D
ba7: 35           dec  (hl)
ba8: c0           ret  nz
ba9: 3e b0        ld   a,$B0
bab: 32 09 60     ld   ($6009),a
bae: 21 85 63     ld   hl,$6385
bb1: 34           inc  (hl)
bb2: c9           ret
bb3: 21 8a 60     ld   hl,$608A
bb6: 3a 09 60     ld   a,($6009)
bb9: fe 90        cp   $90
bbb: 20 0b        jr   nz,$0BC8
bbd: 36 0f        ld   (hl),$0F
bbf: 23           inc  hl
bc0: 36 03        ld   (hl),$03
bc2: 21 19 69     ld   hl,$6919
bc5: 34           inc  (hl)
bc6: 18 09        jr   $0BD1
bc8: fe 18        cp   $18
bca: 20 05        jr   nz,$0BD1
bcc: 21 19 69     ld   hl,$6919
bcf: 35           dec  (hl)
bd0: 00           nop
bd1: df           rst  $18
bd2: af           xor  a
bd3: 32 85 63     ld   ($6385),a
bd6: 34           inc  (hl)
bd7: 23           inc  hl
bd8: 34           inc  (hl)
bd9: c9           ret
bda: cd 1c 01     call $011C
bdd: df           rst  $18
bde: cd 74 08     call $0874
be1: 16 06        ld   d,$06
be3: 3a 00 62     ld   a,($6200)
be6: 5f           ld   e,a
be7: cd 9f 30     call $309F
bea: 21 86 7d     ld   hl,$7D86
bed: 36 01        ld   (hl),$01
bef: 23           inc  hl
bf0: 36 00        ld   (hl),$00
bf2: 21 8a 60     ld   hl,$608A
bf5: 36 02        ld   (hl),$02
bf7: 23           inc  hl
bf8: 36 03        ld   (hl),$03
bfa: 21 a7 63     ld   hl,$63A7
bfd: 36 00        ld   (hl),$00
bff: 21 dc 76     ld   hl,$76DC
c02: 22 a8 63     ld   ($63A8),hl
c05: 3a 2e 62     ld   a,($622E)
c08: fe 06        cp   $06
c0a: 38 05        jr   c,$0C11
c0c: 3e 05        ld   a,$05
c0e: 32 2e 62     ld   ($622E),a
c11: 3a 2f 62     ld   a,($622F)
c14: 47           ld   b,a
c15: 3a 2a 62     ld   a,($622A)
c18: b8           cp   b
c19: 28 04        jr   z,$0C1F
c1b: 21 2e 62     ld   hl,$622E
c1e: 34           inc  (hl)
c1f: 32 2f 62     ld   ($622F),a
c22: 3a 2e 62     ld   a,($622E)
c25: 47           ld   b,a
c26: 21 bc 75     ld   hl,$75BC
c29: 0e 50        ld   c,$50
c2b: 71           ld   (hl),c
c2c: 0c           inc  c
c2d: 2b           dec  hl
c2e: 71           ld   (hl),c
c2f: 0c           inc  c
c30: 2b           dec  hl
c31: 71           ld   (hl),c
c32: 0c           inc  c
c33: 2b           dec  hl
c34: 71           ld   (hl),c
c35: 79           ld   a,c
c36: fe 67        cp   $67
c38: ca 43 0c     jp   z,$0C43
c3b: 0c           inc  c
c3c: 11 23 00     ld   de,$0023
c3f: 19           add  hl,de
c40: c3 2b 0c     jp   $0C2B
c43: 3a a7 63     ld   a,($63A7)
c46: 3c           inc  a
c47: 32 a7 63     ld   ($63A7),a
c4a: 3d           dec  a
c4b: cb 27        sla  a
c4d: cb 27        sla  a
c4f: e5           push hl
c50: 21 f0 3c     ld   hl,$3CF0
c53: c5           push bc
c54: dd 2a a8 63  ld   ix,($63A8)
c58: 4f           ld   c,a
c59: 06 00        ld   b,$00
c5b: 09           add  hl,bc
c5c: 7e           ld   a,(hl)
c5d: dd 77 60     ld   (ix+$60),a
c60: 23           inc  hl
c61: 7e           ld   a,(hl)
c62: dd 77 40     ld   (ix+$40),a
c65: 23           inc  hl
c66: 7e           ld   a,(hl)
c67: dd 77 20     ld   (ix+$20),a
c6a: dd 36 e0 8b  ld   (ix-$20),$8B
c6e: c1           pop  bc
c6f: dd e5        push ix
c71: e1           pop  hl
c72: 11 fc ff     ld   de,$FFFC
c75: 19           add  hl,de
c76: 22 a8 63     ld   ($63A8),hl
c79: e1           pop  hl
c7a: 11 5f ff     ld   de,$FF5F
c7d: 19           add  hl,de
c7e: 05           dec  b
c7f: c2 29 0c     jp   nz,$0C29
c82: 11 07 03     ld   de,$0307
c85: cd 9f 30     call $309F
c88: 21 09 60     ld   hl,$6009
c8b: 36 a0        ld   (hl),$A0
c8d: 23           inc  hl
c8e: 34           inc  (hl)
c8f: 34           inc  (hl)
c90: c9           ret
c91: df           rst  $18
c92: cd 74 08     call $0874
c95: af           xor  a
c96: 32 8c 63     ld   ($638C),a
c99: 11 01 05     ld   de,$0501
c9c: cd 9f 30     call $309F
c9f: 21 86 7d     ld   hl,$7D86
ca2: 36 00        ld   (hl),$00
ca4: 23           inc  hl
ca5: 36 01        ld   (hl),$01
ca7: 3a 27 62     ld   a,($6227)
caa: 3d           dec  a
cab: ca d4 0c     jp   z,$0CD4
cae: 3d           dec  a
caf: ca df 0c     jp   z,$0CDF
cb2: 3d           dec  a
cb3: ca f2 0c     jp   z,$0CF2
cb6: cd 43 0d     call $0D43
cb9: 21 86 7d     ld   hl,$7D86
cbc: 36 01        ld   (hl),$01
cbe: 3e 0b        ld   a,$0B
cc0: 32 89 60     ld   ($6089),a
cc3: 11 8b 3c     ld   de,$3C8B
cc6: cd a7 0d     call $0DA7
cc9: 3a 27 62     ld   a,($6227)
ccc: fe 04        cp   $04
cce: cc 00 0d     call z,$0D00
cd1: c3 a0 3f     jp   $3FA0
cd4: 11 e4 3a     ld   de,$3AE4
cd7: 3e 08        ld   a,$08
cd9: 32 89 60     ld   ($6089),a
cdc: c3 c6 0c     jp   $0CC6
cdf: 11 5d 3b     ld   de,$3B5D
ce2: 21 86 7d     ld   hl,$7D86
ce5: 36 01        ld   (hl),$01
ce7: 23           inc  hl
ce8: 36 00        ld   (hl),$00
cea: 3e 09        ld   a,$09
cec: 32 89 60     ld   ($6089),a
cef: c3 c6 0c     jp   $0CC6
cf2: cd 27 0d     call $0D27
cf5: 3e 0a        ld   a,$0A
cf7: 32 89 60     ld   ($6089),a
cfa: 11 e5 3b     ld   de,$3BE5
cfd: c3 c6 0c     jp   $0CC6
d00: 06 08        ld   b,$08
d02: 21 17 0d     ld   hl,$0D17
d05: 3e b8        ld   a,$B8
d07: 0e 02        ld   c,$02
d09: 5e           ld   e,(hl)
d0a: 23           inc  hl
d0b: 56           ld   d,(hl)
d0c: 23           inc  hl
d0d: 12           ld   (de),a
d0e: 3d           dec  a
d0f: 13           inc  de
d10: 0d           dec  c
d11: c2 0d 0d     jp   nz,$0D0D
d14: 10 ef        djnz $0D05
d16: c9           ret
d17: ca 76 cf     jp   z,$CF76
d1a: 76           halt
d1b: d4 76 d9     call nc,$D976
d1e: 76           halt
d1f: 2a 75 2f     ld   hl,($2F75)
d22: 75           ld   (hl),l
d23: 34           inc  (hl)
d24: 75           ld   (hl),l
d25: 39           add  hl,sp
d26: 75           ld   (hl),l
d27: 21 0d 77     ld   hl,$770D
d2a: cd 30 0d     call $0D30
d2d: 21 0d 76     ld   hl,$760D
d30: 06 11        ld   b,$11
d32: 36 fd        ld   (hl),$FD
d34: 23           inc  hl
d35: 10 fb        djnz $0D32
d37: 11 0f 00     ld   de,$000F
d3a: 19           add  hl,de
d3b: 06 11        ld   b,$11
d3d: 36 fc        ld   (hl),$FC
d3f: 23           inc  hl
d40: 10 fb        djnz $0D3D
d42: c9           ret
d43: 21 87 76     ld   hl,$7687
d46: cd 4c 0d     call $0D4C
d49: 21 47 75     ld   hl,$7547
d4c: 06 04        ld   b,$04
d4e: 36 fd        ld   (hl),$FD
d50: 23           inc  hl
d51: 10 fb        djnz $0D4E
d53: 11 1c 00     ld   de,$001C
d56: 19           add  hl,de
d57: 06 04        ld   b,$04
d59: 36 fc        ld   (hl),$FC
d5b: 23           inc  hl
d5c: 10 fb        djnz $0D59
d5e: c9           ret
d5f: cd 56 0f     call $0F56
d62: cd 41 24     call $2441
d65: 21 09 60     ld   hl,$6009
d68: 36 40        ld   (hl),$40
d6a: 23           inc  hl
d6b: 34           inc  (hl)
d6c: 21 5c 38     ld   hl,$385C
d6f: cd 4e 00     call $004E
; copy 3885 to 6900 8 bytes (static sprites)
d72: 11 00 69     ld   de,$6900
d75: 01 08 00     ld   bc,$0008
d78: ed b0        ldir
d7a: 3a 27 62     ld   a,($6227)
d7d: fe 04        cp   $04
d7f: 28 0a        jr   z,$0D8B
d81: 0f           rrca
d82: 0f           rrca
d83: d8           ret  c
d84: 21 0b 69     ld   hl,$690B
d87: 0e fc        ld   c,$FC
d89: ff           rst  $38
d8a: c9           ret
d8b: 21 08 69     ld   hl,$6908
d8e: 0e 44        ld   c,$44
d90: ff           rst  $38
d91: 11 04 00     ld   de,$0004
d94: 01 10 02     ld   bc,$0210
d97: 21 00 69     ld   hl,$6900
d9a: cd 3d 00     call $003D
d9d: 01 f8 02     ld   bc,$02F8
da0: 21 03 69     ld   hl,$6903
da3: cd 3d 00     call $003D
da6: c9           ret
da7: 1a           ld   a,(de)
da8: 32 b3 63     ld   ($63B3),a
dab: fe aa        cp   $AA
dad: c8           ret  z
dae: 13           inc  de
daf: 1a           ld   a,(de)
db0: 67           ld   h,a
db1: 44           ld   b,h
db2: 13           inc  de
db3: 1a           ld   a,(de)
db4: 6f           ld   l,a
db5: 4d           ld   c,l
db6: d5           push de
db7: cd f0 2f     call $2FF0
dba: d1           pop  de
dbb: 22 ab 63     ld   ($63AB),hl
dbe: 78           ld   a,b
dbf: e6 07        and  $07
dc1: 32 b4 63     ld   ($63B4),a
dc4: 79           ld   a,c
dc5: e6 07        and  $07
dc7: 32 af 63     ld   ($63AF),a
dca: 13           inc  de
dcb: 1a           ld   a,(de)
dcc: 67           ld   h,a
dcd: 90           sub  b
dce: d2 d3 0d     jp   nc,$0DD3
dd1: ed 44        neg
dd3: 32 b1 63     ld   ($63B1),a
dd6: 13           inc  de
dd7: 1a           ld   a,(de)
dd8: 6f           ld   l,a
dd9: 91           sub  c
dda: 32 b2 63     ld   ($63B2),a
ddd: 1a           ld   a,(de)
dde: e6 07        and  $07
de0: 32 b0 63     ld   ($63B0),a
de3: d5           push de
de4: cd f0 2f     call $2FF0
de7: d1           pop  de
de8: 22 ad 63     ld   ($63AD),hl
deb: 3a b3 63     ld   a,($63B3)
dee: fe 02        cp   $02
df0: f2 4f 0e     jp   p,$0E4F
df3: 3a b2 63     ld   a,($63B2)
df6: d6 10        sub  $10
df8: 47           ld   b,a
df9: 3a af 63     ld   a,($63AF)
dfc: 80           add  a,b
dfd: 32 b2 63     ld   ($63B2),a
e00: 3a af 63     ld   a,($63AF)
e03: c6 f0        add  a,$F0
e05: 2a ab 63     ld   hl,($63AB)
e08: 77           ld   (hl),a
e09: 2c           inc  l
e0a: d6 30        sub  $30
e0c: 77           ld   (hl),a
e0d: 3a b3 63     ld   a,($63B3)
e10: fe 01        cp   $01
e12: c2 19 0e     jp   nz,$0E19
e15: af           xor  a
e16: 32 b2 63     ld   ($63B2),a
e19: 3a b2 63     ld   a,($63B2)
e1c: d6 08        sub  $08
e1e: 32 b2 63     ld   ($63B2),a
e21: da 2a 0e     jp   c,$0E2A
e24: 2c           inc  l
e25: 36 c0        ld   (hl),$C0
e27: c3 19 0e     jp   $0E19
e2a: 3a b0 63     ld   a,($63B0)
e2d: c6 d0        add  a,$D0
e2f: 2a ad 63     ld   hl,($63AD)
e32: 77           ld   (hl),a
e33: 3a b3 63     ld   a,($63B3)
e36: fe 01        cp   $01
e38: c2 3f 0e     jp   nz,$0E3F
e3b: 2d           dec  l
e3c: 36 c0        ld   (hl),$C0
e3e: 2c           inc  l
e3f: 3a b0 63     ld   a,($63B0)
e42: fe 00        cp   $00
e44: ca 4b 0e     jp   z,$0E4B
e47: c6 e0        add  a,$E0
e49: 2c           inc  l
e4a: 77           ld   (hl),a
e4b: 13           inc  de
e4c: c3 a7 0d     jp   $0DA7
e4f: 3a b3 63     ld   a,($63B3)
e52: fe 02        cp   $02
e54: c2 e8 0e     jp   nz,$0EE8
e57: 3a af 63     ld   a,($63AF)
e5a: c6 f0        add  a,$F0
e5c: 32 b5 63     ld   ($63B5),a
e5f: 2a ab 63     ld   hl,($63AB)
e62: 3a b5 63     ld   a,($63B5)
e65: 77           ld   (hl),a
e66: 23           inc  hl
e67: 7d           ld   a,l
e68: e6 1f        and  $1F
e6a: ca 78 0e     jp   z,$0E78
e6d: 3a b5 63     ld   a,($63B5)
e70: fe f0        cp   $F0
e72: ca 78 0e     jp   z,$0E78
e75: d6 10        sub  $10
e77: 77           ld   (hl),a
e78: 01 1f 00     ld   bc,$001F
e7b: 09           add  hl,bc
e7c: 3a b1 63     ld   a,($63B1)
e7f: d6 08        sub  $08
e81: da cf 0e     jp   c,$0ECF
e84: 32 b1 63     ld   ($63B1),a
e87: 3a b2 63     ld   a,($63B2)
e8a: fe 00        cp   $00
e8c: ca 62 0e     jp   z,$0E62
e8f: 3a b5 63     ld   a,($63B5)
e92: 77           ld   (hl),a
e93: 23           inc  hl
e94: 7d           ld   a,l
e95: e6 1f        and  $1F
e97: ca a0 0e     jp   z,$0EA0
e9a: 3a b5 63     ld   a,($63B5)
e9d: d6 10        sub  $10
e9f: 77           ld   (hl),a
ea0: 01 1f 00     ld   bc,$001F
ea3: 09           add  hl,bc
ea4: 3a b1 63     ld   a,($63B1)
ea7: d6 08        sub  $08
ea9: da cf 0e     jp   c,$0ECF
eac: 32 b1 63     ld   ($63B1),a
eaf: 3a b2 63     ld   a,($63B2)
eb2: cb 7f        bit  7,a
eb4: c2 d3 0e     jp   nz,$0ED3
eb7: 3a b5 63     ld   a,($63B5)
eba: 3c           inc  a
ebb: 32 b5 63     ld   ($63B5),a
ebe: fe f8        cp   $F8
ec0: c2 c9 0e     jp   nz,$0EC9
ec3: 23           inc  hl
ec4: 3e f0        ld   a,$F0
ec6: 32 b5 63     ld   ($63B5),a
ec9: 7d           ld   a,l
eca: e6 1f        and  $1F
ecc: c2 62 0e     jp   nz,$0E62
ecf: 13           inc  de
ed0: c3 a7 0d     jp   $0DA7
ed3: 3a b5 63     ld   a,($63B5)
ed6: 3d           dec  a
ed7: 32 b5 63     ld   ($63B5),a
eda: fe f0        cp   $F0
edc: f2 e5 0e     jp   p,$0EE5
edf: 2b           dec  hl
ee0: 3e f7        ld   a,$F7
ee2: 32 b5 63     ld   ($63B5),a
ee5: c3 62 0e     jp   $0E62
ee8: 3a b3 63     ld   a,($63B3)
eeb: fe 03        cp   $03
eed: c2 1b 0f     jp   nz,$0F1B
ef0: 2a ab 63     ld   hl,($63AB)
ef3: 3e b3        ld   a,$B3
ef5: 77           ld   (hl),a
ef6: 01 20 00     ld   bc,$0020
ef9: 09           add  hl,bc
efa: 3a b1 63     ld   a,($63B1)
efd: d6 10        sub  $10
eff: da 14 0f     jp   c,$0F14
f02: 32 b1 63     ld   ($63B1),a
f05: 3e b1        ld   a,$B1
f07: 77           ld   (hl),a
f08: 01 20 00     ld   bc,$0020
f0b: 09           add  hl,bc
f0c: 3a b1 63     ld   a,($63B1)
f0f: d6 08        sub  $08
f11: c3 ff 0e     jp   $0EFF
f14: 3e b2        ld   a,$B2
f16: 77           ld   (hl),a
f17: 13           inc  de
f18: c3 a7 0d     jp   $0DA7
f1b: 3a b3 63     ld   a,($63B3)
f1e: fe 07        cp   $07
f20: f2 cf 0e     jp   p,$0ECF
f23: fe 04        cp   $04
f25: ca 4c 0f     jp   z,$0F4C
f28: fe 05        cp   $05
f2a: ca 51 0f     jp   z,$0F51
f2d: 3e fe        ld   a,$FE
f2f: 32 b5 63     ld   ($63B5),a
f32: 2a ab 63     ld   hl,($63AB)
f35: 3a b5 63     ld   a,($63B5)
f38: 77           ld   (hl),a
f39: 01 20 00     ld   bc,$0020
f3c: 09           add  hl,bc
f3d: 3a b1 63     ld   a,($63B1)
f40: d6 08        sub  $08
f42: 32 b1 63     ld   ($63B1),a
f45: d2 35 0f     jp   nc,$0F35
f48: 13           inc  de
f49: c3 a7 0d     jp   $0DA7
f4c: 3e e0        ld   a,$E0
f4e: c3 2f 0f     jp   $0F2F
f51: 3e b0        ld   a,$B0
f53: c3 2f 0f     jp   $0F2F
f56: 06 27        ld   b,$27
f58: 21 00 62     ld   hl,$6200
f5b: af           xor  a
f5c: 77           ld   (hl),a
f5d: 2c           inc  l
f5e: 10 fc        djnz $0F5C
f60: 0e 11        ld   c,$11
f62: 16 80        ld   d,$80
f64: 21 80 62     ld   hl,$6280
f67: 42           ld   b,d
f68: 77           ld   (hl),a
f69: 23           inc  hl
f6a: 10 fc        djnz $0F68
f6c: 0d           dec  c
f6d: 20 f8        jr   nz,$0F67
f6f: 21 9c 3d     ld   hl,$3D9C
f72: 11 80 62     ld   de,$6280
f75: 01 40 00     ld   bc,$0040
f78: ed b0        ldir
f7a: 3a 29 62     ld   a,($6229)
f7d: 47           ld   b,a
f7e: a7           and  a
f7f: 17           rla
f80: a7           and  a
f81: 17           rla
f82: a7           and  a
f83: 17           rla
f84: 80           add  a,b
f85: 80           add  a,b
f86: c6 28        add  a,$28
f88: fe 51        cp   $51
f8a: 38 02        jr   c,$0F8E
f8c: 3e 50        ld   a,$50
f8e: 21 b0 62     ld   hl,$62B0
f91: 06 03        ld   b,$03
f93: 77           ld   (hl),a
f94: 2c           inc  l
f95: 10 fc        djnz $0F93
f97: 87           add  a,a
f98: 47           ld   b,a
f99: 3e dc        ld   a,$DC
f9b: 90           sub  b
f9c: fe 28        cp   $28
f9e: 30 02        jr   nc,$0FA2
fa0: 3e 28        ld   a,$28
fa2: 77           ld   (hl),a
fa3: 2c           inc  l
fa4: 77           ld   (hl),a
fa5: 21 09 62     ld   hl,$6209
fa8: 36 04        ld   (hl),$04
faa: 2c           inc  l
fab: 36 08        ld   (hl),$08
fad: 3a 27 62     ld   a,($6227)
fb0: 4f           ld   c,a
fb1: cb 57        bit  2,a
fb3: 20 16        jr   nz,$0FCB
fb5: 21 00 6a     ld   hl,$6A00
fb8: 3e 4f        ld   a,$4F
fba: 06 03        ld   b,$03
fbc: 77           ld   (hl),a
fbd: 2c           inc  l
fbe: 36 3a        ld   (hl),$3A
fc0: 2c           inc  l
fc1: 36 0f        ld   (hl),$0F
fc3: 2c           inc  l
fc4: 36 18        ld   (hl),$18
fc6: 2c           inc  l
fc7: c6 10        add  a,$10
fc9: 10 f1        djnz $0FBC
fcb: 79           ld   a,c
fcc: ef           rst  $28
fcd: 00           nop
fce: 00           nop
fcf: d7           rst  $10
fd0: 0f           rrca
fd1: 1f           rra
fd2: 10 87        djnz $0F5B
fd4: 10 31        djnz $1007
fd6: 11 21 dc     ld   de,$DC21
fd9: 3d           dec  a
fda: 11 a8 69     ld   de,$69A8
fdd: 01 10 00     ld   bc,$0010
fe0: ed b0        ldir
fe2: 21 ec 3d     ld   hl,$3DEC
fe5: 11 07 64     ld   de,$6407
fe8: 0e 1c        ld   c,$1C
fea: 06 05        ld   b,$05
fec: cd 2a 12     call $122A
fef: 21 f4 3d     ld   hl,$3DF4
ff2: cd fa 11     call $11FA
ff5: 21 00 3e     ld   hl,$3E00
ff8: 11 fc 69     ld   de,$69FC
ffb: 01 04 00     ld   bc,$0004
ffe: ed b0        ldir
