#### D_IMM_SH_INST, D_REG_SH_INST, D_IMM_INST

Fetch:
	inst_type;
	split_inst;
	pc += 4;
Decode:
	op1 = rn;
	op2 = rm <shifttype> shift_imm;
	// D_REG_SH_INST:	op2 = rm <shifttype>> rs;
	// D_IMM_INST:		op2 = imm <> rotate;
	set_cc;
Execute:
	valE = op1 OP op2;
	set_cc;
Memory:

Write-back:
	if (!LOG_INST) 
		rd = valE;
		if (rd == 31 && S) cmsr = smsr;
		else if (S) update cmsr;
	else cmsr update;

#### MUL_INST

Fetch:
	inst_type;
	split_inst;
	pc += 4;
Decode:
	op1 = rn;
	op2 = rm;
	op3 = rs;
Execute:
	valE = op1 mul op2 + op3;
Memory:

Write-back:
	rd = valE;

#### BRX_INST:

Fetch:
	inst_type;
	split_inst;
	pc += 4;
Decode:
	op2 = rm;
Execute:
	valE = op2;
Memory:

Write-back:
	if (L)
		lr = pc;
		pc  = valE;
		regs[30, 1:0] = 0;
	else pc = valE;

#### LSR_OFF_INST, LSI_OFF_INST:

Fetch:
	the same.
Decode:
	op1 = rn;
	op2 = imm14; // LSI_OFF_INST;
	// op2 = rm <shifttype> shift_imm;
Execute:
	if (U) valE = op1 + op2;
	else valE = op1 - op2;
Memory:
	addr = P ? valE : rn;
	if (load)  valM = B ? M[addr, 1] : M[addr, 4];
	if (write) B ? M[addr, 1] = regs[rn] : M[addr, 4] = regs[rn];
Execute:
	if (load) rd = valM;
	if (!P || W) rn = valE; 

#### LSHWR_OFF_INST, LSHWI_OFF_INST:	

Fetch:
	the same.
Decode:
	op1 = rn;
	op2 = imm10;
	// op2 = rm;
Execute:
	if (U) valE = op1 + op2;
	else valE = op1 - op2;
Memory:
	addr = P ? valE : rn;
	if (load) //;
	if (write) //;
Execute:
	if (load) rd = valM;
	if (!P || W) rn = valE;

#### BRLK_INST

Fetch:
	the same.
Decode:
	op1 = imm24 << 2;
	op2 = pc;
Execute:
	valE = op1 + op2;
Memory:
	//
Execute:
	if (L) lr = pc; pc = valE;
	else pc = valE;

#### ST_INST

Fetch:
	the same.
Decode: 
	
Execute:

Memory:

Write-back:
	R30_svc = pc;
	rs_svc = CMSR
	CMSR[4:0] = 10011
	CMSR[5] = 0
	CMSR[7] = 1
	PC = 0x8
