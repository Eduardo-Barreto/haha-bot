# Name: config.mk
# Author: Daniel Nery Silva de Oliveira
# ThundeRatz Robotics Team
# 06/2019

# Cube file name without .ioc extension
PROJECT_NAME = cube
VERSION := v1

PROJECT_RELEASE := $(PROJECT_NAME)_$(VERSION)

TARGET_BOARD := target_$(PROJECT_RELEASE)

DEVICE_FAMILY  := STM32F4xx
DEVICE_TYPE    := STM32F401xx
DEVICE_DEF     := STM32F401xC
DEVICE         := STM32F401CCUx

# Linker script file without .ld extension
# Find it on cube folder after code generation
DEVICE_LD_FILE := STM32F401CCUx_FLASH

# Lib dir
LIB_DIR  := lib

# Cube Directory
CUBE_DIR := cube

# Config Files Directory
CFG_DIR :=

# Tests Directory
TEST_DIR := tests

# Default values, can be set on the command line or here
DEBUG   ?= 1
VERBOSE ?= 0

TEST_NAME ?=
