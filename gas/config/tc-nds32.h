/* tc-nds32.h -- Header file for tc-nds32.c.
   Copyright (C) 2012-2013 Free Software Foundation, Inc.
   Contributed by Andes Technology Corporation.

   This file is part of GAS.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to the Free
   Software Foundation, 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

#ifndef TC_NDS32
#define TC_NDS32

#include "bfd_stdint.h"

#define LISTING_HEADER \
  (target_big_endian ? "NDS32 GAS" : "NDS32 GAS Little Endian")

/* The target BFD architecture.  */
#define TARGET_ARCH		bfd_arch_nds32

/* mapping to mach_table[5] */
#define ISA_V1      bfd_mach_n1h
#define ISA_V2      bfd_mach_n1h_v2
#define ISA_V3      bfd_mach_n1h_v3
#define ISA_V3M     bfd_mach_n1h_v3m

/* Default to big endian. Please note that for Andes architecture,
   instructions are always in big-endian format.  */
#ifndef TARGET_BYTES_BIG_ENDIAN
#define TARGET_BYTES_BIG_ENDIAN	1
#endif

/* This is used to construct expressions out of @GOTOFF, @PLT and @GOT
   symbols.  The relocation type is stored in X_md.  */
#define O_PIC_reloc O_md1

/* as.c.  */
/* Extend GAS command line option handling capability.  */
extern int nds32_parse_option (int, char *);
extern void nds32_after_parse_args (void);
/* The endianness of the target format may change based on command
   line arguments.  */
extern const char * nds32_target_format (void);

#define md_parse_option(optc, optarg)	nds32_parse_option (optc, optarg)
#define md_after_parse_args()		nds32_after_parse_args ()
#define TARGET_FORMAT nds32_target_format()

/* expr.c */
extern int nds32_parse_name (char const *, expressionS *, enum expr_mode, char *);
extern bfd_boolean nds32_allow_local_subtract (expressionS *, expressionS *, segT);
#define md_parse_name(name, exprP, mode, nextcharP) \
	nds32_parse_name (name, exprP, mode, nextcharP)
#define md_allow_local_subtract(lhs,rhs,sect)	nds32_allow_local_subtract (lhs, rhs, sect)

/* dwarf2dbg.c.  */
#define DWARF2_USE_FIXED_ADVANCE_PC		1

/* write.c.  */
extern long nds32_pcrel_from_section (struct fix *, segT);
extern bfd_boolean nds32_fix_adjustable (struct fix *);
extern void nds32_frob_file (void);
extern void nds32_post_relax_hook (void);
extern void nds32_frob_file_before_fix (void);
extern void elf_nds32_final_processing (void);
extern int nds32_validate_fix_sub (struct fix *, segT);
extern int nds32_force_relocation (struct fix *);
extern void nds32_set_section_relocs (asection *, arelent ** , unsigned int);

/* Fill in rs_align_code fragments.  TODO: Review this.  */
extern void nds32_handle_align (fragS *);
extern int nds32_relax_frag (segT, fragS *, long);
extern int tc_nds32_regname_to_dw2regnum (char *);
extern void tc_nds32_frame_initial_instructions (void);

#define MD_PCREL_FROM_SECTION(fix, sect)	nds32_pcrel_from_section (fix, sect)
#define TC_FINALIZE_SYMS_BEFORE_SIZE_SEG	0
#define tc_fix_adjustable(FIX)			nds32_fix_adjustable (FIX)
#define md_apply_fix(fixP, addn, seg)		nds32_apply_fix (fixP, addn, seg)
#define md_post_relax_hook			nds32_post_relax_hook ()
#define tc_frob_file_before_fix()		nds32_frob_file_before_fix ()
#define elf_tc_final_processing()		elf_nds32_final_processing ()
/* For DIFF relocations.  The default behavior is inconsistent with the
   asm internal document.  */
#define TC_FORCE_RELOCATION_SUB_SAME(FIX, SEC)		\
  (! SEG_NORMAL (SEC) || TC_FORCE_RELOCATION (FIX))
#define TC_FORCE_RELOCATION(fix)		nds32_force_relocation (fix)
#define TC_VALIDATE_FIX_SUB(FIX,SEG)		nds32_validate_fix_sub (FIX,SEG)
#define SET_SECTION_RELOCS(sec, relocs, n)	nds32_set_section_relocs (sec, relocs, n)
/* Values passed to md_apply_fix don't include the symbol value.  */
#define MD_APPLY_SYM_VALUE(FIX)			0
#define HANDLE_ALIGN(f)				nds32_handle_align (f)
#undef DIFF_EXPR_OK				/* They should be fixed in linker.  */
#define md_relax_frag(segment, fragP, stretch)	nds32_relax_frag (segment, fragP, stretch)
#define WORKING_DOT_WORD			/* We don't need to handle .word strangely.  */
/* Using to chain fixup with previous fixup.  */
#define TC_FIX_TYPE struct fix *
#define TC_INIT_FIX_DATA(fixP)		\
  do					\
    {					\
      fixP->tc_fix_data = NULL;		\
    }					\
  while (0)

/* read.c.  */
/* Extend GAS macro handling capability.  */
extern void nds32_macro_start (void);
extern void nds32_macro_end (void);
extern void nds32_macro_info (void *);
extern void nds32_start_line_hook (void);
extern void nds32_elf_section_change_hook (void);
extern void md_begin (void);
extern void md_end (void);
extern int nds32_start_label (int, int);
extern void nds32_cleanup (void);
extern void nds32_flush_pending_output (void);
extern void nds32_cons_align (int);
extern void nds32_check_label (symbolS *);
extern void nds32_frob_label (symbolS *);
extern void nds32_pre_do_align (int, char *, int, int);
extern void nds32_do_align (int);

#define md_macro_start()			nds32_macro_start ()
#define md_macro_end()				nds32_macro_end ()
#define md_macro_info(args)			nds32_macro_info (args)
#define TC_START_LABEL(C, S, STR)		(C == ':' && nds32_start_label (0, 0))
#define tc_check_label(label)			nds32_check_label (label)
#define tc_frob_label(label)			nds32_frob_label (label)
#define md_end					md_end
#define md_start_line_hook()			nds32_start_line_hook ()
#define md_cons_align(n)			nds32_cons_align (n)
/* COLE: TODO: Review md_do_align.  */
#define md_do_align(N, FILL, LEN, MAX, LABEL)	\
  nds32_pre_do_align (N, FILL, LEN, MAX);	\
  if ((N) > 1 && (subseg_text_p (now_seg)	\
      || strncmp (now_seg->name, ".gcc_except_table", sizeof(".gcc_except_table") - 1) == 0)) \
    nds32_do_align (N);				\
  goto LABEL;
#define md_elf_section_change_hook()		nds32_elf_section_change_hook ()
#define md_flush_pending_output()		nds32_flush_pending_output ()
#define md_cleanup()				nds32_cleanup ()
#define LOCAL_LABELS_FB				1 /* Permit temporary numeric labels.  */

/* frags.c.  */
struct nds32_frag_type
{
  relax_substateT flag;
  struct nds32_opcode *opcode;
  uint32_t insn;
  /* To Save previos label fixup if existence.  */
  struct fix *fixup;
};

extern void nds32_frag_init (fragS *);

#define TC_FRAG_TYPE				struct nds32_frag_type
#define TC_FRAG_INIT(fragP)			nds32_frag_init (fragP)

/* CFI directive.  */
extern void nds32_elf_frame_initial_instructions (void);
extern int tc_nds32_regname_to_dw2regnum (char *);

#define TARGET_USE_CFIPOP			1
#define DWARF2_DEFAULT_RETURN_COLUMN		30
#define DWARF2_CIE_DATA_ALIGNMENT		-4
#define DWARF2_LINE_MIN_INSN_LENGTH		2

#define tc_regname_to_dw2regnum			tc_nds32_regname_to_dw2regnum
#define tc_cfi_frame_initial_instructions	tc_nds32_frame_initial_instructions

/* COLE: TODO: Review These. They seem to be obsoleted.  */
#if 1
#define TC_RELOC_RTSYM_LOC_FIXUP(FIX)				\
   ((FIX)->fx_addsy == NULL					\
    || (! S_IS_EXTERNAL ((FIX)->fx_addsy)			\
	&& ! S_IS_WEAK ((FIX)->fx_addsy)			\
	&& S_IS_DEFINED ((FIX)->fx_addsy)			\
	&& ! S_IS_COMMON ((FIX)->fx_addsy)))
#define TC_HANDLES_FX_DONE
/* This arranges for gas/write.c to not apply a relocation if
   obj_fix_adjustable() says it is not adjustable.  */
#define TC_FIX_ADJUSTABLE(fixP) obj_fix_adjustable (fixP)
#endif

/* Because linker may relax the code, assemble-time expression
   optimization is not allowed.  */
#define md_allow_eh_opt 0

/* For nds32 relax.  */
enum nds32_br_range
{
  BR_RANGE_S256 = 0,
  BR_RANGE_S16K,
  BR_RANGE_S64K,
  BR_RANGE_S16M,
  BR_RANGE_U4G,
  BR_RANGE_NUM
};

enum nds32_ramp
{
  NDS32_CREATE_LABLE = 1,
  NDS32_RELAX = 2,
  NDS32_ORIGIN = 4,
  NDS32_CONVERT = 8
};

typedef struct nds32_relax_fixup_info
{
  int offset;
  int size;
  /* Reverse branch has to jump to the end of instruction pattern.  */
  int ramp;
  enum bfd_reloc_code_real r_type;
} nds32_relax_fixup_info_t;

typedef struct nds32_cond_field
{
  int offset;
  int bitpos; /* Register position.  */
  int bitmask; /* Number of register bits.  */
} nds32_cond_field_t;

/* The max relaxation pattern is 20-bytes including the nop.  */
#define NDS32_MAXCHAR 20
/* In current, the max entend number of instruction for one pseudo instruction
   is 4, but its number of relocation may be 5.  */
#define MAX_RELAX_NUM 8

typedef struct nds32_relax_info
{
  /* Opcode for the instruction.  */
  const char *opcode;
  enum nds32_br_range br_range;
  nds32_cond_field_t cond_field[MAX_RELAX_NUM]; /* TODO: Reuse nds32_field?  */
  /* Code sequences for different branch range.  */
  uint32_t relax_code_seq[BR_RANGE_NUM][MAX_RELAX_NUM];
  nds32_cond_field_t relax_code_condition[BR_RANGE_NUM][MAX_RELAX_NUM];
  int relax_code_size[BR_RANGE_NUM];
  int relax_branch_isize[BR_RANGE_NUM];
  nds32_relax_fixup_info_t relax_fixup[BR_RANGE_NUM][MAX_RELAX_NUM];
} relax_info_t;

/* Relocation table.  */
struct nds32_relocation_map
{
  unsigned int main_type;
  /* Number of instructions, {relocations type, instruction type}.  */
  unsigned int reloc_insn[6][6][3];
};

#endif /* TC_NDS32 */
