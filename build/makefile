# GNU make (gmake) & nmake shared makefile.
# Conditional logic implemented with differing end-of-line comment syntax.
# To enable multithreaded compilation, nmake compiles all files together with
# /MP, while gmake compiles separately with -jN.
# Makefile assumptions are slightly deviated from `utulek` as our pch.cpp is
# 	shared amongst all projects.

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
ROOT_DIR = ..^\
REPO_NAME = altair
!IFNDEF PROJ
PROJ_NAME = experiment
!ELSE
PROJ_NAME = $(PROJ)
!ENDIF
!IFNDEF BIN
BIN_NAME = $(PROJ_NAME)
!ELSE
BIN_NAME = $(BIN)
!ENDIF
!IFNDEF SRC
SRC_NAME = $(BIN_NAME).cpp
!ELSE
SRC_NAME = $(SRC)
!ENDIF
!IFNDEF BUILD
BUILD_NAME = debug
!ELSE IF $(BUILD) == 2
BUILD_NAME = instrument
!ELSE IF $(BUILD) == 1
BUILD_NAME = release
!ELSE
BUILD_NAME = debug
!ENDIF
!IFNDEF ARCH
ARCH = 64
!ENDIF
!IFNDEF PCH
PCH = 1
!ENDIF
!IFNDEF ARGS
ARGS = < ..\$(ROOT_DIR)build\i.default.txt > ..\$(ROOT_DIR)build\o.default.txt
!ENDIF
# Makefile fails if directory doesn't exist.
!IF [IF EXIST $(ROOT_DIR)experiment\$(BIN_NAME).cpp-assets\ EXIT /B 1] == 1
INCL = $(INCL) $(ROOT_DIR)experiment\$(BIN_NAME).cpp-assets\*
!ENDIF

# The directory structure here must be consistent with macro substitution
# structure utilized later.
BIN_DIR = $(ROOT_DIR)bin^\
PROJ_BIN = $(BIN_DIR)$(PROJ_NAME)\$(BIN_NAME).$(BUILD_NAME).x$(ARCH).exe
PROJ_BIN_DIR = $(BIN_DIR)$(PROJ_NAME)^\
OBJ_DIR = $(ROOT_DIR)obj^\
PROJ_OBJ_DIR = $(OBJ_DIR)$(PROJ_NAME)^\
PROJ_SRC_DIR = $(ROOT_DIR)$(PROJ_NAME)^\
PROJ_SRC = $(patsubsti %,$(PROJ_SRC_DIR)\%,$(SRC_NAME))

COMPILER = cl /c
COMPILER_FLAGS_INCLUDES = /I $(ROOT_DIR)include
COMPILER_FLAGS_COMMON = $(COMPILER_FLAGS_INCLUDES) /std:c++20 /D _CONSOLE\
	/Fp$(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\pch.pch\
	/fp:fast /MP /permissive-\
	/Zc:__cplusplus /Zc:wchar_t /Zc:forScope /Zc:inline /Zf\
	/GS /W3 /WX- /wd4250 /wd4068 /sdl /diagnostics:column /EHsc /Gm- /nologo
COMPILER_FLAGS_DEBUG = /D _DEBUG /MDd /Od /RTC1 /JMC /ZI
COMPILER_FLAGS_RELEASE = /D NDEBUG /MT /O2 /Oi /GL /Gy /Zi
COMPILER_FLAGS_INSTRUMENT = $(COMPILER_FLAGS_DEBUG) /Fa$(PROJ_OBJ_DIR)
COMPILER_FLAGS_64 =
COMPILER_FLAGS_86 =

LINKER = link
LINKER_FLAGS_LIBRARIES =
LINKER_FLAGS_COMMON = $(LINKER_FLAGS_LIBRARIES) /OUT:$(PROJ_BIN)\
	/PDB:$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\$(BIN_NAME).pdb\
	/ILK:$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\$(BIN_NAME).ilk\
	/MANIFESTUAC:"level='asInvoker' uiAccess='false'"\
	/MANIFESTFILE:$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\$(BIN_NAME).exe.intermediate.manifest\
	/LTCGOUT:$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\$(BIN_NAME).iobj\
	/SUBSYSTEM:CONSOLE /NOLOGO
LINKER_FLAGS_DEBUG = /DEBUG
LINKER_FLAGS_RELEASE = /INCREMENTAL:NO /OPT:ICF /OPT:REF /LTCG:incremental
LINKER_FLAGS_INSTRUMENT = $(LINKER_FLAGS_DEBUG)
LINKER_FLAGS_64 = /MACHINE:x64
LINKER_FLAGS_86 = /MACHINE:x86

!IF "$(BUILD_NAME)" == "instrument"
COMPILER_FLAGS = $(COMPILER_FLAGS_COMMON) $(COMPILER_FLAGS_INSTRUMENT)
LINKER_FLAGS = $(LINKER_FLAGS_COMMON) $(LINKER_FLAGS_INSTRUMENT)
!ELSE IF "$(BUILD_NAME)" == "release"
COMPILER_FLAGS = $(COMPILER_FLAGS_COMMON) $(COMPILER_FLAGS_RELEASE)
LINKER_FLAGS = $(LINKER_FLAGS_COMMON) $(LINKER_FLAGS_RELEASE)
!ELSE
COMPILER_FLAGS = $(COMPILER_FLAGS_COMMON) $(COMPILER_FLAGS_DEBUG)
LINKER_FLAGS = $(LINKER_FLAGS_COMMON) $(LINKER_FLAGS_DEBUG)
!ENDIF

!IF $(ARCH) == 86
COMPILER_FLAGS = $(COMPILER_FLAGS) $(COMPILER_FLAGS_86)
LINKER_FLAGS = $(LINKER_FLAGS) $(LINKER_FLAGS_86)
!ELSE
COMPILER_FLAGS = $(COMPILER_FLAGS) $(COMPILER_FLAGS_64)
LINKER_FLAGS = $(LINKER_FLAGS) $(LINKER_FLAGS_64)
!ENDIF

# Real targets.
# Default/build target only compiles and links, but does not run.
_default: build
# Ordering is important so that version is updated first.
build: $(PROJ_BIN)
# Build and run.
run: build
	@ECHO Running $(PROJ_BIN)...
	@CD $(BIN_DIR)$(PROJ_NAME) &&\
		$(BIN_NAME).$(BUILD_NAME).x$(ARCH).exe $(ARGS)
# Clean target removes all intermediates, but remakes the in.txt file.
clean:
	@ECHO Cleaning...
	@IF EXIST $(BIN_DIR) RD /Q /S $(BIN_DIR)
	@IF EXIST $(OBJ_DIR) RD /Q /S $(OBJ_DIR)
	@DEL i.*.txt o.*.txt
	@TYPE NUL > i.default.txt
	@TYPE NUL > o.default.txt
# Precompiled headers.
$(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\pch.pch: pch.cpp
	@IF NOT EXIST $(OBJ_DIR) MD $(OBJ_DIR)
	@IF NOT EXIST $(OBJ_DIR)$(BUILD_NAME) MD $(OBJ_DIR)$(BUILD_NAME)
	@IF NOT EXIST $(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\
		MD $(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)
	@$(COMPILER) $(COMPILER_FLAGS) /Yc\
		/Fd$(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\pch.pdb\
		/Fo$(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\pch.obj pch.cpp
pch.cpp: $(INCL)

# Build target.
# First compile all outdated files (with /MP), then link everything together.
# Need additional variable to parse dependencies correctly.
$(PROJ_BIN): $(PROJ_SRC)
	@IF NOT EXIST $(PROJ_BIN_DIR) MD $(PROJ_BIN_DIR)
	@IF NOT EXIST $(PROJ_OBJ_DIR) MD $(PROJ_OBJ_DIR)
	@IF NOT EXIST $(PROJ_OBJ_DIR)$(BUILD_NAME) MD $(PROJ_OBJ_DIR)$(BUILD_NAME)
	@IF NOT EXIST $(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\
		MD $(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)
	@ECHO Building $(PROJ_BIN)...
!IF $(PCH) == 0
	@$(COMPILER) $(COMPILER_FLAGS)\
		/Fd$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\$(BIN_NAME).pdb\
		/Fo$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\ \
		$?
!ELSE
# PDB and IDB should be derived from the PCH versions.
	@IF NOT EXIST $(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\$(BIN_NAME).pdb\
		CP $(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\pch.pdb\
			$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\$(BIN_NAME).pdb
	@IF NOT EXIST $(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\$(BIN_NAME).idb\
		CP $(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\pch.idb\
			$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\$(BIN_NAME).idb
	@$(COMPILER) $(COMPILER_FLAGS)\
		/Fd$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\$(BIN_NAME).pdb\
		/Fo$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\ \
		/Yu"bits/stdc++.h" $?
!ENDIF
	@ECHO Linking $(PROJ_BIN)...
# It's unclear why some of the wildcards need to be escaped, but it works.
	@$(LINKER) $(LINKER_FLAGS) $(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\pch.obj\
		$(patsubsti %.cpp,%.obj,\
		$(patsubsti $(PROJ_SRC_DIR)\%,$(PROJ_OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\\%,$**))

# Mark source files as out of date if any headers have changed.
$(PROJ_SRC): $(INCL) $(OBJ_DIR)$(BUILD_NAME)\x$(ARCH)\pch.pch

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
