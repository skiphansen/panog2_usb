###############################################################################
## Makefile
###############################################################################
include ../project.mk

SRC_DIR       = .
SRC_DIR      += $(CORES_DIR)/core_soc/src_v
SRC_DIR      += $(CORES_DIR)/dbg_bridge/src_v
SRC_DIR      += $(CORES_DIR)/cpu/riscv/core/riscv
SRC_DIR      += $(CORES_DIR)/cpu/riscv/top_tcm_wrapper
#SRC_DIR      += $(CORES_DIR)/core_ulpi_wrapper/src_v
SRC_DIR      += $(CORES_DIR)/core_usb_host/src_v

BSCAN_SPI_DIR = $(PANO_CORES_DIR)/xc3sprog

ifeq ($(PLATFORM),pano-g2-c)
   EXTRA_VFLAGS += CPU_CLK_48MHZ=1
else ifeq ($(PLATFORM),pano-g2)
   EXTRA_VFLAGS += CPU_CLK_36MHZ=1
else
   $(error Unknown PLATFORM $(PLATFORM))
endif

COMPRESS_BITFILE = yes
INIT_IMAGE = ./firmware.mem

#MAP_CMDS = -w -intstyle ise -detail -ir off -ignore_keep_hierarchy -ol high

# NB: the -pr b option was removed from the default options, otherwise there 
# are timing errors
MAP_CMDS = -w -intstyle ise -detail -ir off -ignore_keep_hierarchy -timing -ol high -mt 2

# use 4 cores
PAR_CMDS = -w -intstyle ise -ol high  -mt 4

PATCHED_CPU = $(CORES_DIR)/cpu/riscv/.patched

.PHONY: init_and_build
init_and_build: $(PATCHED_CPU) all

TOPDIR = ..
include $(TOPDIR)/pano/make/ise.mk

CPU_PATCH_DIR := $(PATCHES_DIR)/cores/cpu/riscv
CPU_PATCHES   := $(wildcard $(CPU_PATCH_DIR)/*.patch)

$(PATCHED_CPU): $(CPU_PATCHES)
	(cd $(CORES_DIR)/cpu/riscv; git reset HEAD --hard; \
	$(foreach _patch,$(CPU_PATCHES), patch -p1 < $(_patch);))
	touch $@

firmware.mem:
	make -C $(TOPDIR)/fw/blinky init_image

debug:
	echo "SRC_DIR: $(SRC_DIR)"
