ARCH="aarch64:ilp32"
MACHINE=
NOP=0

SCRIPT_NAME=elf
ELFSIZE=32
OUTPUT_FORMAT="elf32-littleaarch64"
BIG_OUTPUT_FORMAT="elf32-bigaarch64"
LITTLE_OUTPUT_FORMAT="elf32-littleaarch64"
NO_REL_RELOCS=yes

TEMPLATE_NAME=elf32
EXTRA_EM_FILE=aarch64elf

GENERATE_SHLIB_SCRIPT=yes
MAXPAGESIZE="CONSTANT (MAXPAGESIZE)"

ENTRY=_start
EMBEDDED=yes
SEPARATE_GOTPLT=24
TEXT_START_ADDR=0x00400000

DATA_START_SYMBOLS='__data_start = . ;';

# AArch64 does not support .s* sections.
NO_SMALL_DATA=yes

OTHER_BSS_SYMBOLS='__bss_start__ = .;'
OTHER_BSS_END_SYMBOLS='_bss_end__ = . ; __bss_end__ = . ;'
OTHER_END_SYMBOLS='__end__ = . ;'

OTHER_SECTIONS='.note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }'
ATTRS_SECTIONS='.ARM.attributes 0 : { KEEP (*(.ARM.attributes)) KEEP (*(.gnu.attributes)) }'

# This sets the stack to the top of the simulator memory (2^19 bytes).
STACK_ADDR=0x80000