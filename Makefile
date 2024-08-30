.PHONY: all help link build flash copy_firmware
MAKEFLAGS += --no-print-directory

default_keyboard=feb42
default_keymap=default

DIR := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(DIR),)
    DIR := $(shell pwd)
endif

QMK := $(shell realpath $(shell qmk env QMK_HOME))

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: help


link: ## [kb=my_keyboard]
	@$(eval kb ?= $(if $(kb),$(kb), $(default_keyboard)))
	@if [ ! -d "$(DIR)/keyboards/$(kb)" ]; then \
		echo "Error: Keyboard '$(kb)' does not exist."; \
		exit 1; \
	fi
	@if [ -e "$(QMK)/keyboards/$(kb)" ]; then rm -rf $(QMK)/keyboards/$(kb); fi
	@ln -s $(DIR)/keyboards/$(kb) $(QMK)/keyboards/$(kb)

build: ## ## [kb=my_keyboard] [km=my_keymap]
	@$(eval kb ?= $(if $(kb),$(kb), $(default_keyboard)))
	@if [ ! -d "$(DIR)/keyboards/$(kb)" ]; then \
		echo "Error: Keyboard '$(kb)' does not exist."; \
		exit 1; \
	fi
	@$(eval km ?= $(if $(km),$(km), $(default_keymap)))
	@make link -B kb=$(kb)
	@qmk compile -kb $(kb) -km $(km)
	@make copy_firmware -B kb=$(kb) km=$(km)

flash: ## [kb=my_keyboard] [km=my_keymap] [console=true|false]
	@$(eval kb ?= $(if $(kb),$(kb), $(default_keyboard)))
	@if [ ! -d "$(DIR)/keyboards/$(kb)" ]; then \
		echo "Error: Keyboard '$(kb)' does not exist."; \
		exit 1; \
	fi
	@$(eval km ?= $(if $(km),$(km), $(default_keymap)))
	@make build -B kb=$(kb) km=$(km)
	@qmk flash -kb $(kb) -km $(km)
ifeq ($(console),true)
	@qmk console
endif


copy_firmware: ## [kb=my_keyboard] [km=my_keymap]
	@$(eval kb ?= $(if $(kb),$(kb), $(default_keyboard)))
	@if [ ! -d "$(DIR)/keyboards/$(kb)" ]; then \
		echo "Error: Keyboard '$(kb)' does not exist."; \
		exit 1; \
	fi
	@$(eval km ?= $(if $(km),$(km), $(default_keymap)))
	@echo Copying firmware..
	@if [ ! -d "$(DIR)/build" ]; then mkdir -p $(DIR)/build; fi
	@if [ -e "$(QMK)/.build/${kb}_$(km).bin" ]; then cp "$(QMK)/.build/${kb}_$(km).bin" "$(DIR)/build/${kb}_$(km).bin"; fi
	@if [ -e "$(QMK)/.build/${kb}_$(km).hex" ]; then cp "$(QMK)/.build/${kb}_$(km).hex" "$(DIR)/build/${kb}_$(km).hex"; fi
	@if [ -e "$(QMK)/.build/${kb}_$(km).elf" ]; then cp "$(QMK)/.build/${kb}_$(km).elf" "$(DIR)/build/${kb}_$(km).elf"; fi
	@if [ -e "$(DIR)/${kb}_$(km).hex" ]; then rm -f $(DIR)/${kb}_$(km).hex; fi
	@echo done
