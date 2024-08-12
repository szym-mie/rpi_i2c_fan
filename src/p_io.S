.section .text

_io_sleep:
	mov r19, r21
	mov r20, r22
_io_sleep_loop:
	/* loop takes 4 cycles incl. branch */
	subi r19, 4
	sbci r20, 0
	brpl _io_sleep_loop
	/* if less than 0 */
	mov r19, r21
	mov r20, r22
	subi r23, 1
	sbci r24, 0
	brpl _io_sleep_loop
	/* on 0 ms return */
	ret

io_tsleep:
	/* loop takes 4 cycles incl. branch */
	subi r23, 1
	subi r24, 0
	brne io_tsleep
	ret
