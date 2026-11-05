# Space Shooter - build system
#
# Usage:
#   make            build the game (downloads and compiles raylib on first run)
#   make run        build and start the game
#   make debug      build with debug symbols and sanitizers (BUILD=debug)
#   make clean      remove game build artifacts
#   make distclean  remove build artifacts and the downloaded raylib sources
#
# Requirements: a C++17 compiler, GNU make, git and (on Linux) the X11/OpenGL
# development packages required by raylib - see README.md.

# ---------------------------------------------------------------------------
# Configuration
# ---------------------------------------------------------------------------
APP            := space_shooter
BUILD          ?= release
RAYLIB_VERSION ?= 5.5
RAYLIB_REPO    ?= https://github.com/raysan5/raylib.git

CXX      ?= g++
CXXSTD   := -std=c++17
WARNINGS := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion

SRC_DIR      := src
ASSETS_DIR   := assets
EXTERNAL_DIR := external
RAYLIB_DIR   := $(EXTERNAL_DIR)/raylib
RAYLIB_SRC   := $(RAYLIB_DIR)/src
BUILD_DIR    := build/$(BUILD)
OBJ_DIR      := $(BUILD_DIR)/obj
RAYLIB_OUT   := build/raylib
RAYLIB_LIB   := $(RAYLIB_OUT)/libraylib.a

# ---------------------------------------------------------------------------
# Platform detection
# ---------------------------------------------------------------------------
ifeq ($(OS),Windows_NT)
    PLATFORM_OS := WINDOWS
    EXE_EXT     := .exe
    PLATFORM_LIBS := -lopengl32 -lgdi32 -lwinmm
    APP_LDFLAGS := -static -static-libgcc -static-libstdc++
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        PLATFORM_OS := OSX
        PLATFORM_LIBS := -framework OpenGL -framework Cocoa -framework IOKit \
                         -framework CoreAudio -framework CoreVideo
    else
        PLATFORM_OS := LINUX
        PLATFORM_LIBS := -lGL -lm -lpthread -ldl -lrt -lX11
    endif
endif

TARGET := $(BUILD_DIR)/$(APP)$(EXE_EXT)

ifeq ($(BUILD),debug)
    OPT_FLAGS := -O0 -g3
    ifneq ($(PLATFORM_OS),WINDOWS)
        OPT_FLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
    endif
    RAYLIB_BUILD_MODE := DEBUG
else
    OPT_FLAGS := -O2 -DNDEBUG
    RAYLIB_BUILD_MODE := RELEASE
endif

CPPFLAGS += -isystem $(RAYLIB_SRC) -MMD -MP
CXXFLAGS += $(CXXSTD) $(WARNINGS) $(OPT_FLAGS)
LDFLAGS  += $(OPT_FLAGS) $(APP_LDFLAGS)
LDLIBS   += $(RAYLIB_LIB) $(PLATFORM_LIBS)

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS    := $(OBJECTS:.o=.d)
ASSETS  := $(wildcard $(ASSETS_DIR)/*)
ASSETS_OUT := $(patsubst $(ASSETS_DIR)/%,$(BUILD_DIR)/assets/%,$(ASSETS))

# ---------------------------------------------------------------------------
# Targets
# ---------------------------------------------------------------------------
.PHONY: all release debug run raylib clean distclean help

all: $(TARGET) $(ASSETS_OUT)

release:
	@$(MAKE) --no-print-directory BUILD=release

debug:
	@$(MAKE) --no-print-directory BUILD=debug

run: all
	./$(TARGET)

help:
	@sed -n '3,9p' Makefile

# --- raylib (fetched from GitHub and built as a static library) -----------
raylib: $(RAYLIB_LIB)

$(RAYLIB_SRC)/raylib.h:
	@echo "Fetching raylib $(RAYLIB_VERSION)..."
	@mkdir -p $(EXTERNAL_DIR)
	git clone --depth 1 --branch $(RAYLIB_VERSION) $(RAYLIB_REPO) $(RAYLIB_DIR)

$(RAYLIB_LIB): $(RAYLIB_SRC)/raylib.h
	@echo "Building raylib $(RAYLIB_VERSION)..."
	@mkdir -p $(RAYLIB_OUT)
	$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=STATIC \
		RAYLIB_BUILD_MODE=RELEASE RAYLIB_RELEASE_PATH=$(abspath $(RAYLIB_OUT)) \
		CC=$(if $(filter default,$(origin CC)),cc,$(CC))

# --- game -----------------------------------------------------------------
$(TARGET): $(OBJECTS) $(RAYLIB_LIB)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(RAYLIB_SRC)/raylib.h
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/assets/%: $(ASSETS_DIR)/%
	@mkdir -p $(@D)
	cp $< $@

clean:
	rm -rf build/release build/debug

distclean:
	rm -rf build $(EXTERNAL_DIR)

-include $(DEPS)
