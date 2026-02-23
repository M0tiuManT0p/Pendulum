CC_LINUX = gcc
CC_WIN = x86_64-w64-mingw32-gcc

INC_DIR = include
EXT_DIR = include/external
LOGIC_DIR = logic
VISUAL_DIR = visual

SRCS = main.c gui_impl.c logic/data.c logic/logic.c visual/settings.c visual/visuals.c

TARGET_LINUX = pendulum
TARGET_WIN = pendulum.exe

CFLAGS = -Wall -Wextra -std=c99 -Wno-unused-parameter -I$(INC_DIR) -I$(EXT_DIR)

LIBS_LINUX = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

LIBS_WIN = -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows

all: linux windows

linux: $(SRCS)
	$(CC_LINUX) $(CFLAGS) $(SRCS) -o $(TARGET_LINUX) $(LIBS_LINUX)
	
windows: $(SRCS)
	$(CC_WIN) $(CFLAGS) $(SRCS) -o $(TARGET_WIN) -Linclude/external $(LIBS_WIN) -static

clean:
	rm -f $(TARGET_LINUX) $(TARGET_WIN)