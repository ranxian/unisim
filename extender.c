#include "extender.h"
#include "helper.h"
int extend(int bits, int len, int S)
{
	if (S) {
		int b = B(bits, len-1);
		if (b) {
			int i;
			for (i = 31; i >= len; i--) {
				bits = bits | (1 << i);
			}
			return bits;
		} else {
			return (unsigned)bits;
		}
	} else {
		return (unsigned)bits;
	}
	
}