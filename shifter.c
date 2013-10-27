#include "shifter.h"
#include "sim.h"
#include "helper.h"
#include <stdlib.h>
int shifter(shifttype_t shifttype, int n1, int n2)
{
	int res, C = 0;

	switch(shifttype) {
		case SHIFT_LL:
			if (n2 == 32) {
				res = 0;
			} else if (n2 > 32) {
				res = 0;
			} else {
				res = n1 << n2;
				if (n2) C = B(n1, 32 - n2);
			}
			break;
		case SHIFT_LR:
			if (n2 == 32) {
				res = 0;
			} else if (n2 > 32) {
				res = 0;
			} else {
				res = ((unsigned)n1) >> n2;
				if (n2) C = B(n1, n2-1);
			}
			break;
		case SHIFT_AR:
			if (n2 >= 32) {
				res = n1 >> 31;
			} else {
				res = n1 >> n2;
				if (n2) C = B(n1, n2-1);
			}
			break;
		case SHIFT_LP:
			if (n2 == 32) {
				res = n1;
			} else {
				n2 %= 32;
				res = (((unsigned)n1) >> n2) | (n1 << (32-n2));
			}
			break;
		default:
			printf("unknown shift type!\n");
			exit(0);
	}

	temp_cmsr.C = C;
	return res;
}

