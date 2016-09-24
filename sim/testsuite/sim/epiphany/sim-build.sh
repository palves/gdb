#/bin/sh
# Generate test result data for epiphany simulator testing.
# This script is machine generated.
# It is intended to be run in the testsuite source directory.
#
# Syntax: /bin/sh sim-build.sh

# Put results here, so we preserve the existing set for comparison.
rm -rf tmpdir
mkdir tmpdir
cd tmpdir

cat <<EOF > beq16.cgs
# epiphany testcase for beq \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global beq16
beq16:
	beq footext

	pass
EOF

cat <<EOF > beq.cgs
# epiphany testcase for beq \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global beq
beq:
	beq footext

	pass
EOF

cat <<EOF > bne16.cgs
# epiphany testcase for bne \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bne16
bne16:
	bne footext

	pass
EOF

cat <<EOF > bne.cgs
# epiphany testcase for bne \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bne
bne:
	bne footext

	pass
EOF

cat <<EOF > bgt16.cgs
# epiphany testcase for bgt \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bgt16
bgt16:
	bgt footext

	pass
EOF

cat <<EOF > bgt.cgs
# epiphany testcase for bgt \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bgt
bgt:
	bgt footext

	pass
EOF

cat <<EOF > bgtu16.cgs
# epiphany testcase for bgtu \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bgtu16
bgtu16:
	bgtu footext

	pass
EOF

cat <<EOF > bgtu.cgs
# epiphany testcase for bgtu \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bgtu
bgtu:
	bgtu footext

	pass
EOF

cat <<EOF > bgte16.cgs
# epiphany testcase for bgte \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bgte16
bgte16:
	bgte footext

	pass
EOF

cat <<EOF > bgte.cgs
# epiphany testcase for bgte \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bgte
bgte:
	bgte footext

	pass
EOF

cat <<EOF > bgteu16.cgs
# epiphany testcase for bgteu \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bgteu16
bgteu16:
	bgteu footext

	pass
EOF

cat <<EOF > bgteu.cgs
# epiphany testcase for bgteu \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bgteu
bgteu:
	bgteu footext

	pass
EOF

cat <<EOF > blt16.cgs
# epiphany testcase for blt \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global blt16
blt16:
	blt footext

	pass
EOF

cat <<EOF > blt.cgs
# epiphany testcase for blt \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global blt
blt:
	blt footext

	pass
EOF

cat <<EOF > bltu16.cgs
# epiphany testcase for bltu \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bltu16
bltu16:
	bltu footext

	pass
EOF

cat <<EOF > bltu.cgs
# epiphany testcase for bltu \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bltu
bltu:
	bltu footext

	pass
EOF

cat <<EOF > blte16.cgs
# epiphany testcase for blte \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global blte16
blte16:
	blte footext

	pass
EOF

cat <<EOF > blte.cgs
# epiphany testcase for blte \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global blte
blte:
	blte footext

	pass
EOF

cat <<EOF > blteu16.cgs
# epiphany testcase for blteu \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global blteu16
blteu16:
	blteu footext

	pass
EOF

cat <<EOF > blteu.cgs
# epiphany testcase for blteu \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global blteu
blteu:
	blteu footext

	pass
EOF

cat <<EOF > b16.cgs
# epiphany testcase for b \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global b16
b16:
	b footext

	pass
EOF

cat <<EOF > b.cgs
# epiphany testcase for b \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global b
b:
	b footext

	pass
EOF

cat <<EOF > bbeq16.cgs
# epiphany testcase for bbeq \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bbeq16
bbeq16:
	bbeq footext

	pass
EOF

cat <<EOF > bbeq.cgs
# epiphany testcase for bbeq \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bbeq
bbeq:
	bbeq footext

	pass
EOF

cat <<EOF > bbne16.cgs
# epiphany testcase for bbne \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bbne16
bbne16:
	bbne footext

	pass
EOF

cat <<EOF > bbne.cgs
# epiphany testcase for bbne \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bbne
bbne:
	bbne footext

	pass
EOF

cat <<EOF > bblt16.cgs
# epiphany testcase for bblt \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bblt16
bblt16:
	bblt footext

	pass
EOF

cat <<EOF > bblt.cgs
# epiphany testcase for bblt \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bblt
bblt:
	bblt footext

	pass
EOF

cat <<EOF > bblte16.cgs
# epiphany testcase for bblte \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bblte16
bblte16:
	bblte footext

	pass
EOF

cat <<EOF > bblte.cgs
# epiphany testcase for bblte \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bblte
bblte:
	bblte footext

	pass
EOF

cat <<EOF > bl16.cgs
# epiphany testcase for bl \$simm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bl16
bl16:
	bl footext

	pass
EOF

cat <<EOF > bl.cgs
# epiphany testcase for bl \$simm24 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bl
bl:
	bl footext

	pass
EOF

cat <<EOF > jr16.cgs
# epiphany testcase for jr \$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global jr16
jr16:
	jr r0

	pass
EOF

cat <<EOF > jr.cgs
# epiphany testcase for jr \$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global jr
jr:
	jr r0

	pass
EOF

cat <<EOF > jalr16.cgs
# epiphany testcase for jalr \$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global jalr16
jalr16:
	jalr r0

	pass
EOF

cat <<EOF > jalr.cgs
# epiphany testcase for jalr \$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global jalr
jalr:
	jalr r0

	pass
EOF

cat <<EOF > ldrbx16.cgs
# epiphany testcase for ldrb \$rd,[\$rn,\$rm] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrbx16
ldrbx16:
	ldrb r0,[r0,r0]

	pass
EOF

cat <<EOF > ldrbp16.cgs
# epiphany testcase for ldrb \$rd,[\$rn],\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrbp16
ldrbp16:
	ldrb r0,[r0],r0

	pass
EOF

cat <<EOF > ldrbx.cgs
# epiphany testcase for ldrb \$rd6,[\$rn6,\$rm6] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrbx
ldrbx:
	ldrb r0,[r0,r0]

	pass
EOF

cat <<EOF > ldrbp.cgs
# epiphany testcase for ldrb \$rd6,[\$rn6],\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrbp
ldrbp:
	ldrb r0,[r0],r0

	pass
EOF

cat <<EOF > ldrbd16.cgs
# epiphany testcase for ldrb \$rd,[\$rn,\$disp3] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrbd16
ldrbd16:
	ldrb r0,[r0,0]

	pass
EOF

cat <<EOF > ldrbd.cgs
# epiphany testcase for ldrb \$rd6,[\$rn6,\$disp11] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrbd
ldrbd:
	ldrb r0,[r0,0]

	pass
EOF

cat <<EOF > ldrwx16.cgs
# epiphany testcase for ldrw \$rd,[\$rn,\$rm] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrwx16
ldrwx16:
	ldrw r0,[r0,r0]

	pass
EOF

cat <<EOF > ldrwp16.cgs
# epiphany testcase for ldrw \$rd,[\$rn],\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrwp16
ldrwp16:
	ldrw r0,[r0],r0

	pass
EOF

cat <<EOF > ldrwx.cgs
# epiphany testcase for ldrw \$rd6,[\$rn6,\$rm6] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrwx
ldrwx:
	ldrw r0,[r0,r0]

	pass
EOF

cat <<EOF > ldrwp.cgs
# epiphany testcase for ldrw \$rd6,[\$rn6],\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrwp
ldrwp:
	ldrw r0,[r0],r0

	pass
EOF

cat <<EOF > ldrwd16.cgs
# epiphany testcase for ldrw \$rd,[\$rn,\$disp3] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrwd16
ldrwd16:
	ldrw r0,[r0,0]

	pass
EOF

cat <<EOF > ldrwd.cgs
# epiphany testcase for ldrw \$rd6,[\$rn6,\$disp11] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrwd
ldrwd:
	ldrw r0,[r0,0]

	pass
EOF

cat <<EOF > ldrx16.cgs
# epiphany testcase for ldr \$rd,[\$rn,\$rm] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrx16
ldrx16:
	ldr r0,[r0,r0]

	pass
EOF

cat <<EOF > ldrp16.cgs
# epiphany testcase for ldr \$rd,[\$rn],\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrp16
ldrp16:
	ldr r0,[r0],r0

	pass
EOF

cat <<EOF > ldrx.cgs
# epiphany testcase for ldr \$rd6,[\$rn6,\$rm6] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrx
ldrx:
	ldr r0,[r0,r0]

	pass
EOF

cat <<EOF > ldrp.cgs
# epiphany testcase for ldr \$rd6,[\$rn6],\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrp
ldrp:
	ldr r0,[r0],r0

	pass
EOF

cat <<EOF > ldrd16.cgs
# epiphany testcase for ldr \$rd,[\$rn,\$disp3] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrd16
ldrd16:
	ldr r0,[r0,0]

	pass
EOF

cat <<EOF > ldrd.cgs
# epiphany testcase for ldr \$rd6,[\$rn6,\$disp11] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrd
ldrd:
	ldr r0,[r0,0]

	pass
EOF

cat <<EOF > ldrdx16.cgs
# epiphany testcase for ldrd \$rd,[\$rn,\$rm] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrdx16
ldrdx16:
	ldrd r0,[r0,r0]

	pass
EOF

cat <<EOF > ldrdp16.cgs
# epiphany testcase for ldrd \$rd,[\$rn],\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrdp16
ldrdp16:
	ldrd r0,[r0],r0

	pass
EOF

cat <<EOF > ldrdx.cgs
# epiphany testcase for ldrd \$rd6,[\$rn6,\$rm6] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrdx
ldrdx:
	ldrd r0,[r0,r0]

	pass
EOF

cat <<EOF > ldrdp.cgs
# epiphany testcase for ldrd \$rd6,[\$rn6],\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrdp
ldrdp:
	ldrd r0,[r0],r0

	pass
EOF

cat <<EOF > ldrdd16.cgs
# epiphany testcase for ldrd \$rd,[\$rn,\$disp3] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrdd16
ldrdd16:
	ldrd r0,[r0,0]

	pass
EOF

cat <<EOF > ldrdd.cgs
# epiphany testcase for ldrd \$rd6,[\$rn6,\$disp11] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global ldrdd
ldrdd:
	ldrd r0,[r0,0]

	pass
EOF

cat <<EOF > strbx16.cgs
# epiphany testcase for strb \$rd,[\$rn,\$rm] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strbx16
strbx16:
	strb r0,[r0,r0]

	pass
EOF

cat <<EOF > strbx.cgs
# epiphany testcase for strb \$rd6,[\$rn6,\$rm6] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strbx
strbx:
	strb r0,[r0,r0]

	pass
EOF

cat <<EOF > strbp16.cgs
# epiphany testcase for strb \$rd,[\$rn],\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strbp16
strbp16:
	strb r0,[r0],r0

	pass
EOF

cat <<EOF > strbp.cgs
# epiphany testcase for strb \$rd6,[\$rn6],\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strbp
strbp:
	strb r0,[r0],r0

	pass
EOF

cat <<EOF > strbd16.cgs
# epiphany testcase for strb \$rd,[\$rn,\$disp3] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strbd16
strbd16:
	strb r0,[r0,0]

	pass
EOF

cat <<EOF > strbd.cgs
# epiphany testcase for strb \$rd6,[\$rn6,\$disp11] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strbd
strbd:
	strb r0,[r0,0]

	pass
EOF

cat <<EOF > strwx16.cgs
# epiphany testcase for strw \$rd,[\$rn,\$rm] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strwx16
strwx16:
	strw r0,[r0,r0]

	pass
EOF

cat <<EOF > strwx.cgs
# epiphany testcase for strw \$rd6,[\$rn6,\$rm6] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strwx
strwx:
	strw r0,[r0,r0]

	pass
EOF

cat <<EOF > strwp16.cgs
# epiphany testcase for strw \$rd,[\$rn],\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strwp16
strwp16:
	strw r0,[r0],r0

	pass
EOF

cat <<EOF > strwp.cgs
# epiphany testcase for strw \$rd6,[\$rn6],\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strwp
strwp:
	strw r0,[r0],r0

	pass
EOF

cat <<EOF > strwd16.cgs
# epiphany testcase for strw \$rd,[\$rn,\$disp3] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strwd16
strwd16:
	strw r0,[r0,0]

	pass
EOF

cat <<EOF > strwd.cgs
# epiphany testcase for strw \$rd6,[\$rn6,\$disp11] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strwd
strwd:
	strw r0,[r0,0]

	pass
EOF

cat <<EOF > strx16.cgs
# epiphany testcase for str \$rd,[\$rn,\$rm] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strx16
strx16:
	str r0,[r0,r0]

	pass
EOF

cat <<EOF > strx.cgs
# epiphany testcase for str \$rd6,[\$rn6,\$rm6] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strx
strx:
	str r0,[r0,r0]

	pass
EOF

cat <<EOF > strp16.cgs
# epiphany testcase for str \$rd,[\$rn],\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strp16
strp16:
	str r0,[r0],r0

	pass
EOF

cat <<EOF > strp.cgs
# epiphany testcase for str \$rd6,[\$rn6],\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strp
strp:
	str r0,[r0],r0

	pass
EOF

cat <<EOF > strd16.cgs
# epiphany testcase for str \$rd,[\$rn,\$disp3] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strd16
strd16:
	str r0,[r0,0]

	pass
EOF

cat <<EOF > strd.cgs
# epiphany testcase for str \$rd6,[\$rn6,\$disp11] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strd
strd:
	str r0,[r0,0]

	pass
EOF

cat <<EOF > strdx16.cgs
# epiphany testcase for strd \$rd,[\$rn,\$rm] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strdx16
strdx16:
	strd r0,[r0,r0]

	pass
EOF

cat <<EOF > strdx.cgs
# epiphany testcase for strd \$rd6,[\$rn6,\$rm6] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strdx
strdx:
	strd r0,[r0,r0]

	pass
EOF

cat <<EOF > strdp16.cgs
# epiphany testcase for strd \$rd,[\$rn],\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strdp16
strdp16:
	strd r0,[r0],r0

	pass
EOF

cat <<EOF > strdp.cgs
# epiphany testcase for strd \$rd6,[\$rn6],\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strdp
strdp:
	strd r0,[r0],r0

	pass
EOF

cat <<EOF > strdd16.cgs
# epiphany testcase for strd \$rd,[\$rn,\$disp3] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strdd16
strdd16:
	strd r0,[r0,0]

	pass
EOF

cat <<EOF > strdd.cgs
# epiphany testcase for strd \$rd6,[\$rn6,\$disp11] -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global strdd
strdd:
	strd r0,[r0,0]

	pass
EOF

cat <<EOF > mov16EQ.cgs
# epiphany testcase for moveq \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16EQ
mov16EQ:
	moveq r0,r0

	pass
EOF

cat <<EOF > movEQ.cgs
# epiphany testcase for moveq \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movEQ
movEQ:
	moveq r0,r0

	pass
EOF

cat <<EOF > mov16NE.cgs
# epiphany testcase for movne \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16NE
mov16NE:
	movne r0,r0

	pass
EOF

cat <<EOF > movNE.cgs
# epiphany testcase for movne \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movNE
movNE:
	movne r0,r0

	pass
EOF

cat <<EOF > mov16GT.cgs
# epiphany testcase for movgt \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16GT
mov16GT:
	movgt r0,r0

	pass
EOF

cat <<EOF > movGT.cgs
# epiphany testcase for movgt \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movGT
movGT:
	movgt r0,r0

	pass
EOF

cat <<EOF > mov16GTU.cgs
# epiphany testcase for movgtu \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16GTU
mov16GTU:
	movgtu r0,r0

	pass
EOF

cat <<EOF > movGTU.cgs
# epiphany testcase for movgtu \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movGTU
movGTU:
	movgtu r0,r0

	pass
EOF

cat <<EOF > mov16GTE.cgs
# epiphany testcase for movgte \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16GTE
mov16GTE:
	movgte r0,r0

	pass
EOF

cat <<EOF > movGTE.cgs
# epiphany testcase for movgte \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movGTE
movGTE:
	movgte r0,r0

	pass
EOF

cat <<EOF > mov16GTEU.cgs
# epiphany testcase for movgteu \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16GTEU
mov16GTEU:
	movgteu r0,r0

	pass
EOF

cat <<EOF > movGTEU.cgs
# epiphany testcase for movgteu \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movGTEU
movGTEU:
	movgteu r0,r0

	pass
EOF

cat <<EOF > mov16LT.cgs
# epiphany testcase for movlt \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16LT
mov16LT:
	movlt r0,r0

	pass
EOF

cat <<EOF > movLT.cgs
# epiphany testcase for movlt \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movLT
movLT:
	movlt r0,r0

	pass
EOF

cat <<EOF > mov16LTU.cgs
# epiphany testcase for movltu \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16LTU
mov16LTU:
	movltu r0,r0

	pass
EOF

cat <<EOF > movLTU.cgs
# epiphany testcase for movltu \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movLTU
movLTU:
	movltu r0,r0

	pass
EOF

cat <<EOF > mov16LTE.cgs
# epiphany testcase for movlte \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16LTE
mov16LTE:
	movlte r0,r0

	pass
EOF

cat <<EOF > movLTE.cgs
# epiphany testcase for movlte \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movLTE
movLTE:
	movlte r0,r0

	pass
EOF

cat <<EOF > mov16LTEU.cgs
# epiphany testcase for movlteu \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16LTEU
mov16LTEU:
	movlteu r0,r0

	pass
EOF

cat <<EOF > movLTEU.cgs
# epiphany testcase for movlteu \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movLTEU
movLTEU:
	movlteu r0,r0

	pass
EOF

cat <<EOF > mov16B.cgs
# epiphany testcase for mov \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16B
mov16B:
	mov r0,r0

	pass
EOF

cat <<EOF > movB.cgs
# epiphany testcase for mov \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movB
movB:
	mov r0,r0

	pass
EOF

cat <<EOF > mov16BEQ.cgs
# epiphany testcase for movbeq \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16BEQ
mov16BEQ:
	movbeq r0,r0

	pass
EOF

cat <<EOF > movBEQ.cgs
# epiphany testcase for movbeq \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movBEQ
movBEQ:
	movbeq r0,r0

	pass
EOF

cat <<EOF > mov16BNE.cgs
# epiphany testcase for movbne \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16BNE
mov16BNE:
	movbne r0,r0

	pass
EOF

cat <<EOF > movBNE.cgs
# epiphany testcase for movbne \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movBNE
movBNE:
	movbne r0,r0

	pass
EOF

cat <<EOF > mov16BLT.cgs
# epiphany testcase for movblt \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16BLT
mov16BLT:
	movblt r0,r0

	pass
EOF

cat <<EOF > movBLT.cgs
# epiphany testcase for movblt \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movBLT
movBLT:
	movblt r0,r0

	pass
EOF

cat <<EOF > mov16BLTE.cgs
# epiphany testcase for movblte \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16BLTE
mov16BLTE:
	movblte r0,r0

	pass
EOF

cat <<EOF > movBLTE.cgs
# epiphany testcase for movblte \$rd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movBLTE
movBLTE:
	movblte r0,r0

	pass
EOF

cat <<EOF > movts16.cgs
# epiphany testcase for movts \$rd,\$rn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movts16
movts16:
	movts r0,r0

	pass
EOF

cat <<EOF > movts.cgs
# epiphany testcase for movts \$sd6,\$rn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movts
movts:
	movts config,r0

	pass
EOF

cat <<EOF > movfs16.cgs
# epiphany testcase for movfs \$rd,\$sn -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movfs16
movfs16:
	movfs r0,config

	pass
EOF

cat <<EOF > movfs.cgs
# epiphany testcase for movfs \$rd6,\$sn6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global movfs
movfs:
	movfs r0,config

	pass
EOF

cat <<EOF > nop.cgs
# epiphany testcase for nop -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global nop
nop:
	nop

	pass
EOF

cat <<EOF > idle.cgs
# epiphany testcase for idle -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global idle
idle:
	idle

	pass
EOF

cat <<EOF > bkpt.cgs
# epiphany testcase for bkpt -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global bkpt
bkpt:
	bkpt

	pass
EOF

cat <<EOF > rti.cgs
# epiphany testcase for rti -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global rti
rti:
	rti

	pass
EOF

cat <<EOF > trap16.cgs
# epiphany testcase for trap \$disp3 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global trap16
trap16:
	trap 0

	pass
EOF

cat <<EOF > add16.cgs
# epiphany testcase for add \$rd,\$rn,\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global add16
add16:
	add r0,r0,r0

	pass
EOF

cat <<EOF > add.cgs
# epiphany testcase for add \$rd6,\$rn6,\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global add
add:
	add r0,r0,r0

	pass
EOF

cat <<EOF > sub16.cgs
# epiphany testcase for sub \$rd,\$rn,\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global sub16
sub16:
	sub r0,r0,r0

	pass
EOF

cat <<EOF > sub.cgs
# epiphany testcase for sub \$rd6,\$rn6,\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global sub
sub:
	sub r0,r0,r0

	pass
EOF

cat <<EOF > and16.cgs
# epiphany testcase for and \$rd,\$rn,\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global and16
and16:
	and r0,r0,r0

	pass
EOF

cat <<EOF > and.cgs
# epiphany testcase for and \$rd6,\$rn6,\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global and
and:
	and r0,r0,r0

	pass
EOF

cat <<EOF > or16.cgs
# epiphany testcase for or \$rd,\$rn,\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global or16
or16:
	or r0,r0,r0

	pass
EOF

cat <<EOF > or.cgs
# epiphany testcase for or \$rd6,\$rn6,\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global or
or:
	or r0,r0,r0

	pass
EOF

cat <<EOF > xor16.cgs
# epiphany testcase for xor \$rd,\$rn,\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global xor16
xor16:
	xor r0,r0,r0

	pass
EOF

cat <<EOF > xor.cgs
# epiphany testcase for xor \$rd6,\$rn6,\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global xor
xor:
	xor r0,r0,r0

	pass
EOF

cat <<EOF > asr16.cgs
# epiphany testcase for asr \$rd,\$rn,\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global asr16
asr16:
	asr r0,r0,r0

	pass
EOF

cat <<EOF > asr.cgs
# epiphany testcase for asr \$rd6,\$rn6,\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global asr
asr:
	asr r0,r0,r0

	pass
EOF

cat <<EOF > lsr16.cgs
# epiphany testcase for lsr \$rd,\$rn,\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global lsr16
lsr16:
	lsr r0,r0,r0

	pass
EOF

cat <<EOF > lsr.cgs
# epiphany testcase for lsr \$rd6,\$rn6,\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global lsr
lsr:
	lsr r0,r0,r0

	pass
EOF

cat <<EOF > lsl16.cgs
# epiphany testcase for lsl \$rd,\$rn,\$rm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global lsl16
lsl16:
	lsl r0,r0,r0

	pass
EOF

cat <<EOF > lsl.cgs
# epiphany testcase for lsl \$rd6,\$rn6,\$rm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global lsl
lsl:
	lsl r0,r0,r0

	pass
EOF

cat <<EOF > addi16.cgs
# epiphany testcase for add \$rd,\$rn,\$simm3 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global addi16
addi16:
	add r0,r0,0

	pass
EOF

cat <<EOF > addi.cgs
# epiphany testcase for add \$rd6,\$rn6,\$simm11 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global addi
addi:
	add r0,r0,0

	pass
EOF

cat <<EOF > subi16.cgs
# epiphany testcase for sub \$rd,\$rn,\$simm3 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global subi16
subi16:
	sub r0,r0,0

	pass
EOF

cat <<EOF > subi.cgs
# epiphany testcase for sub \$rd6,\$rn6,\$simm11 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global subi
subi:
	sub r0,r0,0

	pass
EOF

cat <<EOF > lsri16.cgs
# epiphany testcase for lsr \$rd,\$rn,\$shift -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global lsri16
lsri16:
	lsr r0,r0,0

	pass
EOF

cat <<EOF > lsri32.cgs
# epiphany testcase for lsr \$rd6,\$rn6,\$shift -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global lsri32
lsri32:
	lsr r0,r0,0

	pass
EOF

cat <<EOF > lsli16.cgs
# epiphany testcase for lsl \$rd,\$rn,\$shift -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global lsli16
lsli16:
	lsl r0,r0,0

	pass
EOF

cat <<EOF > lsli32.cgs
# epiphany testcase for lsl \$rd6,\$rn6,\$shift -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global lsli32
lsli32:
	lsl r0,r0,0

	pass
EOF

cat <<EOF > asri16.cgs
# epiphany testcase for asr \$rd,\$rn,\$shift -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global asri16
asri16:
	asr r0,r0,0

	pass
EOF

cat <<EOF > asri32.cgs
# epiphany testcase for asr \$rd6,\$rn6,\$shift -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global asri32
asri32:
	asr r0,r0,0

	pass
EOF

cat <<EOF > mov8.cgs
# epiphany testcase for mov \$rd,\$imm8 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov8
mov8:
	mov r0,0

	pass
EOF

cat <<EOF > mov16.cgs
# epiphany testcase for mov \$rd6,\$imm16 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global mov16
mov16:
	mov r0,0

	pass
EOF

cat <<EOF > faddf16.cgs
# epiphany testcase for fadd \$frd,\$frn,\$frm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global faddf16
faddf16:
	fadd r0,r0,r0

	pass
EOF

cat <<EOF > faddf32.cgs
# epiphany testcase for fadd \$frd6,\$frn6,\$frm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global faddf32
faddf32:
	fadd r0,r0,r0

	pass
EOF

cat <<EOF > fsubf16.cgs
# epiphany testcase for fsub \$frd,\$frn,\$frm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global fsubf16
fsubf16:
	fsub r0,r0,r0

	pass
EOF

cat <<EOF > fsubf32.cgs
# epiphany testcase for fsub \$frd6,\$frn6,\$frm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global fsubf32
fsubf32:
	fsub r0,r0,r0

	pass
EOF

cat <<EOF > fmulf16.cgs
# epiphany testcase for fmul \$frd,\$frn,\$frm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global fmulf16
fmulf16:
	fmul r0,r0,r0

	pass
EOF

cat <<EOF > fmulf32.cgs
# epiphany testcase for fmul \$frd6,\$frn6,\$frm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global fmulf32
fmulf32:
	fmul r0,r0,r0

	pass
EOF

cat <<EOF > fmaddf16.cgs
# epiphany testcase for fmadd \$frd,\$frn,\$frm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global fmaddf16
fmaddf16:
	fmadd r0,r0,r0

	pass
EOF

cat <<EOF > fmaddf32.cgs
# epiphany testcase for fmadd \$frd6,\$frn6,\$frm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global fmaddf32
fmaddf32:
	fmadd r0,r0,r0

	pass
EOF

cat <<EOF > fmsubf16.cgs
# epiphany testcase for fmsub \$frd,\$frn,\$frm -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global fmsubf16
fmsubf16:
	fmsub r0,r0,r0

	pass
EOF

cat <<EOF > fmsubf32.cgs
# epiphany testcase for fmsub \$frd6,\$frn6,\$frm6 -*- Asm -*-
# mach: all

	.include "testutils.inc"

	start

	.global fmsubf32
fmsubf32:
	fmsub r0,r0,r0

	pass
EOF

