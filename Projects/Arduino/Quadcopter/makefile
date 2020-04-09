# Makefile
ARDMK_DIR 			= 	$(HOME)/.arduino_mk
CTAGS_PATH 			= 	$(ARDUINO_DIR)/tools-builder/ctags/5.8-arduino11/ctags
ARDUINO_DIR 		= 	/usr/share/arduino
AVR_TOOLS_DIR 		= 	/usr
ARDUINO_SKETCHBOOK 	= 	$(shell pwd)/src/quad/
BOARD_TAG 			= 	atmega328
PT= ./src/quad

LOCAL_C_SRCS    ?= $(wildcard ${PT}/*.c)
LOCAL_CPP_SRCS  ?= $(wildcard ${PT}/*.cpp)
LOCAL_CC_SRCS   ?= $(wildcard ${PT}/*.cc)
LOCAL_PDE_SRCS  ?= $(wildcard ${PT}/*.pde)
LOCAL_INO_SRCS  ?= $(wildcard ${PT}/*.ino)
LOCAL_AS_SRCS   ?= $(wildcard ${PT}/*.S)

include $(ARDMK_DIR)/Arduino.mk


flags:
	@echo "$(CFLAGS)" | sed -r "s: :\n:g" >  compile_flags.txt

i.PHONY: ctags
ctags:
	$(CTAGS_PATH) -f tags.cpp $(shell find . -name "*.cpp" -o -name "*.h")
	$(CTAGS_PATH) -f tags.ino --langmap=c++:.ino $(shell find . -name "*.ino")
	cat tags.cpp tags.ino > tags
	sort tags -o tags
	rm -f tags.*
