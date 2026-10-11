CC = gcc
CFLAGS = -g -Wextra -Wall
INCLUDES = -Iconfigs/ -Isrc/
TARGET = app
BUILD = build

SRCS = $(wildcard src/*/*.c)
CONFIGS_DIR = configs
OBJS = $(addprefix $(BUILD)/, $(SRCS:.c=.o))

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@


$(BUILD)/src/%.o: src/%.c $(CONFIGS_DIR)/configs.h
	@if not exist "$(@D)" mkdir "$(@D)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	@if exist "$(BUILD)" rmdir /s /q "$(BUILD)"
	@if exist "$(TARGET).exe" del /q "$(TARGET).exe"