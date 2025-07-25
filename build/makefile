# GNU make (gmake) & nmake shared makefile.
# Conditional logic implemented with differing end-of-line comment syntax.
# To enable multithreaded compilation, nmake compiles all files together with
# /MP, while gmake compiles separately with -jN.

# Variables:
# PROJECT: name of project; path to files from repository root.
# SOURCES: * (default), or a list of filenames in the project directory.
# BIN: name of output executable (default = PROJECT).
# BUILD: 0 (default), 1, or 2, specifying the type of build.
# ARGUMENTS: command-line arguments to pass to the executable to be run.

# Targets:
# build (default): compile & link.
# run: compile, link, and run.
# clean: remove intermediates and output directory.

# Default target defined before any "fake" targets.
__default: _default

# ------------------------------------------------------------------------------
ifdef MAKEDIR: # gmake: false; nmake: unused target
!ifdef MAKEDIR # gmake: not seen; nmake: true
# ------------------------------------------------------------------------------

# nmake specific commands.
# The directory structure here must be consistent with macro substitution
# structure utilized later.
ROOT_DIR = ..^\
OBJ_DIR = $(ROOT_DIR)obj^\
BIN_DIR = $(ROOT_DIR)bin^\
PROJECT_OBJ_DIR = $(OBJ_DIR)$(PROJECT)^\
PROJECT_SRC_DIR = $(ROOT_DIR)$(PROJECT)^\
!IFNDEF SOURCES
SOURCES = *.cpp
!ENDIF
!IFNDEF BIN
# For the repository, executable filename is not the project name. This is
# always set by the caller in altair.
BIN = $(PROJECT)
!ENDIF
PROJECT_BIN = $(BIN_DIR)$(PROJECT)\$(BIN).exe
PROJECT_BIN_DIR = $(BIN_DIR)$(PROJECT)^\

# PCH requires that PDB is shared during compile, but separate during link.
PCH_SRC = pch.cpp
PCH_OBJ = $(OBJ_DIR)pch.obj
PCH_PDB = $(OBJ_DIR)pch.pdb
PCH_FILE = $(OBJ_DIR)pch.pch

COMPILER = cl /c
COMPILER_FLAGS_INCLUDES = /I $(ROOT_DIR)include^\
# Does not include the /Fo obj output option, as that is set later depending on
# whether or not we build the pch.
COMPILER_FLAGS_COMMON = $(COMPILER_FLAGS_INCLUDES) /std:c++20\
	/D _CONSOLE /D _CRT_SECURE_NO_WARNINGS\
	/D _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS\
	/Fd$(PCH_PDB) /Fp$(PCH_FILE) /fp:fast /MP /permissive- \
	/Zc:__cplusplus /Zc:wchar_t /Zc:forScope /Zc:inline /Zf\
	/GS /W3 /WX- /wd4250 /wd4068 /sdl /diagnostics:column /EHsc /Gm- /nologo
COMPILER_FLAGS_DEBUG = /D _DEBUG /MDd /Od /RTC1 /JMC /ZI
COMPILER_FLAGS_RELEASE = /D NDEBUG /MT /O2 /Oi /GL /Gy /Zi
COMPILER_FLAGS_INSTRUMENT = $(COMPILER_FLAGS_DEBUG) /Fa$(PROJECT_OBJ_DIR)

LINKER = link
LINKER_FLAGS_LIBRARIES =
LINKER_FLAGS_COMMON = $(LINKER_FLAGS_LIBRARIES) /OUT:$(PROJECT_BIN)\
	/PDB:$(PROJECT_OBJ_DIR)$(BIN).pdb /ILK:$(PROJECT_OBJ_DIR)$(BIN).ilk\
	/MACHINE:x64 /MANIFESTUAC:"level='asInvoker' uiAccess='false'"\
	/MANIFESTFILE:$(PROJECT_OBJ_DIR)$(BIN).exe.intermediate.manifest\
	/LTCGOUT:$(PROJECT_OBJ_DIR)$(BIN).iobj /SUBSYSTEM:CONSOLE /NOLOGO
LINKER_FLAGS_DEBUG = /DEBUG
LINKER_FLAGS_RELEASE = /INCREMENTAL:NO /OPT:ICF /OPT:REF /LTCG:incremental
LINKER_FLAGS_INSTRUMENT = $(LINKER_FLAGS_DEBUG)

# BUILD_TYPE can be either 0 (default; debug), 1 (release), or 2 (instrument).
!IFNDEF BUILD
BUILD = 0
!ENDIF
!IF $(BUILD) == 1
COMPILER_FLAGS = $(COMPILER_FLAGS_COMMON) $(COMPILER_FLAGS_RELEASE)
LINKER_FLAGS = $(LINKER_FLAGS_COMMON) $(LINKER_FLAGS_RELEASE)
!ELSE IF $(BUILD) == 2
COMPILER_FLAGS = $(COMPILER_FLAGS_COMMON) $(COMPILER_FLAGS_INSTRUMENT)
LINKER_FLAGS = $(LINKER_FLAGS_COMMON) $(LINKER_FLAGS_INSTRUMENT)
!ELSE
COMPILER_FLAGS = $(COMPILER_FLAGS_COMMON) $(COMPILER_FLAGS_DEBUG)
LINKER_FLAGS = $(LINKER_FLAGS_COMMON) $(LINKER_FLAGS_DEBUG)
!ENDIF

# Real targets.
# Default/build target only compiles and links, but does not run.
_default: build
build: $(PROJECT_BIN)
# Build and run.
run: build
	@CD $(BIN_DIR) && $(PROJECT_BIN) $(ARGUMENTS)
# Clean target removes all intermediates, but remakes the in.txt file.
clean:
	@IF EXIST $(BIN_DIR) RD /Q /S $(BIN_DIR)
	@IF EXIST $(OBJ_DIR) RD /Q /S $(OBJ_DIR)
	@DEL i.*.txt o.*.txt
	@TYPE NUL > i.default.txt
	@TYPE NUL > o.default.txt

# Build target.
# Define special macro to enable double-substitution.
DBLSUB_DEP_SRC_DIR_TO_OBJ_DIR = $(**:..\=..\obj\)
# First compile all outdated files (with /MP), then link everything together.
# Splitting out the intermediate obj step makes /MP difficult to use.
$(PROJECT_BIN): $(PROJECT_SRC_DIR)$(SOURCES)
	@$(MAKE) /$(MAKEFLAGS) $(PCH_FILE)
	@IF NOT EXIST $(PROJECT_BIN_DIR) MD $(PROJECT_BIN_DIR)
	@IF NOT EXIST $(PROJECT_OBJ_DIR) MD $(PROJECT_OBJ_DIR)
	@$(COMPILER) $(COMPILER_FLAGS) /Yu"bits/stdc++.h" /Fo$(PROJECT_OBJ_DIR)$(BIN).obj\
		$(PROJECT_SRC_DIR)$(SOURCES)
	@ECHO $(PROJECT_BIN)
# Consider directly using $(PROJECT_OBJ_DIR)$(BIN) here since projects are
# necessarily single-source anyway.
	@$(LINKER) $(LINKER_FLAGS) $(PCH_OBJ)\
		$(DBLSUB_DEP_SRC_DIR_TO_OBJ_DIR:.cpp=.obj)

# Precompiled headers.
$(PCH_FILE): $(PCH_SRC)
	@IF NOT EXIST $(OBJ_DIR) MD $(OBJ_DIR)
	@$(COMPILER) $(COMPILER_FLAGS) /Yc"bits/stdc++.h" /Fo$(PCH_OBJ) $(PCH_SRC)

# ------------------------------------------------------------------------------
!else
else
# ------------------------------------------------------------------------------

# GNU make (gmake) specific commands.
# For usage of bash commands like `read`.
SHELL := /bin/bash
ROOT_DIR := ../
OBJ_DIR := $(ROOT_DIR)obj/
BIN_DIR := $(ROOT_DIR)bin/
PROJECT_OBJ_DIR := $(OBJ_DIR)$(PROJECT)/
PROJECT_SRC_DIR := $(ROOT_DIR)$(PROJECT)/
SOURCES ?= *.cpp
BIN ?= $(PROJECT)
PROJECT_BIN := $(BIN_DIR)$(PROJECT)/$(BIN)
PROJECT_BIN_DIR := $(BIN_DIR)$(PROJECT)/

COMPILER ?= clang++
COMPILER_FLAGS_INCLUDES := -I $(ROOT_DIR)include/
COMPILER_FLAGS_COMMON := $(COMPILER_FLAGS_INCLUDES) -std=c++20 -m64 -pthread\
	-Wall -Wextra\
	-D _CONSOLE -D _CRT_SECURE_NO_WARNINGS\
	-D _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
COMPILER_FLAGS_DEBUG := -D _DEBUG -g -O0
COMPILER_FLAGS_RELEASE := -D NDEBUG -Ofast
COMPILER_FLAGS_INSTRUMENT := $(COMPILER_FLAGS_DEBUG) /Fa$(PROJECT_OBJ_DIR)

LINKER := $(COMPILER)
LINKER_FLAGS_LIBRARIES := -pthread -lresolv
LINKER_FLAGS_COMMON := $(LINKER_FLAGS_LIBRARIES)
LINKER_FLAGS_DEBUG :=
LINKER_FLAGS_RELEASE :=
LINKER_FLAGS_INSTRUMENT := $(LINKER_FLAGS_DEBUG)\
	-fsanitize=address,undefined,leak

# -lstdc++fs is neither available nor required on typical MacOS C++ compiler
# implementations.
ifneq ($(shell uname -s), Darwin)
	LINKER_FLAGS_LIBRARIES := $(LINKER_FLAGS_LIBRARIES) -lstdc++fs
endif

BUILD ?= 0
ifeq ($(BUILD), 1)
	COMPILER_FLAGS := $(COMPILER_FLAGS_COMMON) $(COMPILER_FLAGS_RELEASE)
	LINKER_FLAGS := $(LINKER_FLAGS_COMMON) $(LINKER_FLAGS_RELEASE)
else ifeq ($(BUILD), 2)
	COMPILER_FLAGS := $(COMPILER_FLAGS_COMMON) $(COMPILER_FLAGS_INSTRUMENT)
	LINKER_FLAGS := $(LINKER_FLAGS_COMMON) $(LINKER_FLAGS_INSTRUMENT)
else
	COMPILER_FLAGS := $(COMPILER_FLAGS_COMMON) $(COMPILER_FLAGS_DEBUG)
	LINKER_FLAGS := $(LINKER_FLAGS_COMMON) $(LINKER_FLAGS_DEBUG)
endif

# Second expansion for stem matching syntax.
.SECONDEXPANSION:
# Keep intermediate and output files.
# Introduce list of project object intermediates parsed from the source
# directory with SOURCES.
PROJECT_OBJS := $(addprefix $(PROJECT_OBJ_DIR), $(addsuffix .o,\
	$(basename $(notdir $(wildcard $(PROJECT_SRC_DIR)$(SOURCES))))))
.SECONDARY: $(PROJECT_BIN) $(PROJECT_OBJS)

# Ensure files with the same name as fake targets do not trigger.
.PHONY: __default _default build run clean
_default: build
build: $(PROJECT_BIN)
run: build
	@cd $(BIN_DIR) && ./$(PROJECT_BIN) $(ARGUMENTS)
# Clean, but recreate in.txt file.
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR) i.*.txt o.*.txt
	@touch i.default.txt o.default.txt

# Link rule.
$(PROJECT_BIN): $(BIN_DIR)% : $(PROJECT_OBJS)
	@mkdir -p $(@D)
	@echo $@
	@$(LINKER) $(PROJECT_OBJS) $(LINKER_FLAGS) -o $@

# Compile rule. Stem % matchines source file name.
$(PROJECT_OBJS): $(OBJ_DIR)%.o : $(ROOT_DIR)$$*.cpp
	@mkdir -p $(@D)
	@echo $@
	@$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

# ------------------------------------------------------------------------------
endif    # gmake: close condition; nmake: not seen
!endif : # gmake: unused target; nmake close conditional
# ------------------------------------------------------------------------------
