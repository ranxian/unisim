#### D_IMM_SH_INST, D_REG_SH_INST, D_IMM_INST

Fetch:
	inst_type;
	split_inst;
	valP = pc + 4;
Decode:
	op1 = rn;
	op2 = rm <shifttype> shift_imm;
	// D_REG_SH_INST:	op2 = rm <shifttype> rs;
	// D_IMM_INST:		op2 = imm <> rotate;
	set_cc;
Execute:
	valE = op1 OP op2;
	set_cc;
Memory:

Write-back:
	pc = valP;
	if (!LOG_INST) 
		regs[rd] = valE;
		/* no such condition in user program
		 * if (rd == 31 && S) cmsr = smsr;
		 */
		if (S && rd != 31) update cmsr;
	else cmsr update;

#### MUL_INST

Fetch:
	inst_type;
	split_inst;
	valP = pc + 4;
Decode:
	op1 = rn;
	op2 = rm;
	op3 = rs;
Execute:
	valE = op1 mul op2 + op3;
Memory:

Write-back:
	pc = valP;
	regs[rd] = valE;

#### BRX_INST:

Fetch:
	inst_type;
	split_inst;
	valP = pc + 4;
Decode:
	op2 = rm;
Execute:
	valE = op2;
Memory:

Write-back:
	pc = valP;
	if (L)
		lr = valP & 0xfffffffe;
		pc = valE;
	else pc = valE;

#### LSR_OFF_INST, LSI_OFF_INST:

Fetch:
	the same.
Decode:
	op1 = rn;
	op2 = imm14; // LSI_OFF_INST;
	// op2 = rm <shifttype> shift_imm;
	valD = regs[rd];
Execute:
	if (U) valE = op1 + op2;
	else valE = op1 - op2;
Memory:
	addr = P ? valE : rn;
	if (L)  valM = B ? M[addr, 1] : M[addr, 4];
	else B ? M[addr, 1] = valD : M[addr, 4] = valD;
Write-back:
	pc = valP;
	if (L) rd = valM;
	if (!P || W) rn = valE; 

#### LSHWR_OFF_INST, LSHWI_OFF_INST:	

Fetch:
	the same.
Decode:
	op1 = rn;
	op2 = imm10;
	// op2 = rm;
	valD = regs[rd];
Execute:
	if (U) valE = op1 + op2;
	else valE = op1 - op2;
Memory:
	addr = P ? valE : op1;
	if (L) valM = H ? M[addr, 2] : M[addr, 4];
	else H ? M[addr, 2] = valD : M[addr, 4] = valD;
Write-back:
	pc = valP;
	if (load) rd = valM; // look at S2 to see if sign extend is needed
	if (!P || W) rn = valE;

#### BRLK_INST

Fetch:
	the same.
Decode:
	op1 = imm24 << 2;
	op2 = valP;
Execute:
	valE = op1 + op2;
Memory:
	//
Write-back:
	pc = valP;
	if (L) lr = valP; pc = valE;
	else pc = valE;

#### ST_INST

Fetch:
	the same.
Decode: 
	
Execute:

Memory:

Write-back:
	pc = valP;
	R30_svc = valP;
	rs_svc = CMSR;
	CMSR[4:0] = 10011;
	CMSR[5] = 0;
	CMSR[7] = 1;
	pc = 0x8;
