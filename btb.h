#ifndef BTB_H
#define BTB_H

#define BTB_ENTRY_SIZE

typedef {
	int inst_addr;
	int target;
	int history;
} btbe_t;

int btb_predicate(PC)

extern btbe_t 

extern btb_t btb;

#endif