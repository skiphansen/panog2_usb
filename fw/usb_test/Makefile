include ../../project.mk

TARGET       = usb_test

# source to include
SRC_DIR      = .
SRC_DIR     += $(CORES_DIR)/core_soc/src_c
EXCLUDE_SRC += $(CORES_DIR)/core_soc/src_c/spi_lite.c
SRC_DIR     += $(PANO_FW_DIR)/lib/libstd
SRC_DIR     += $(CORES_DIR)/core_usb_host/sw/core

INCLUDE_PATH += ../include
INCLUDE_PATH += $(PANO_FW_DIR)/common
INCLUDE_PATH += $(CORES_DIR)/core_usb_host/sw/core

EXTRA_CFLAGS += -MD

# build optons
OPT        = 2
ENABLE_LST = yes

include $(TOPDIR)/pano/make/c_prog.mk

run_prebuilt:
	$(RUN_PREFIX) ../../prebuilt/usb_test $(RUN_ARGS)


