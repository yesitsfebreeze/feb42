.PHONY: all help link build flash copy_firmware push
MAKEFLAGS += --no-print-directory

DIR := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(DIR),)
    DIR := $(shell pwd)
endif

QMK := $(shell realpath $(shell qmk env QMK_HOME))

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: help

link: ## links the keyboard into the qmk firmware folder
	@if [ -e "$(QMK)/keyboards/feb42" ]; then rm -rf $(QMK)/keyboards/feb42; fi
	@ln -s $(DIR)/firmware $(QMK)/keyboards/feb42

build: ## [km=my_keymap]
	@$(eval km ?= $(if $(km),$(km), "default"))
	@make link -B
	@qmk compile -kb feb42 -km $(km)
	@make copy_firmware -B kb=feb42 km=$(km)

flash: ## [km=my_keymap] [console=true|false]
	@$(eval km ?= $(if $(km),$(km), "default"))
	@make build -B km=$(km)
	@qmk flash -kb feb42 -km $(km)
ifeq ($(console),true)
	@qmk console
endif

push: ## [m="my message"]
	$(eval m ?= $(if $(m),$(m),"update"))
	@git add --all
	@git commit -m "$(m)"
	@git push


copy_firmware: ## [km=my_keymap]
	@$(eval km ?= $(if $(km),$(km), $(default_keymap)))
	@echo Copying firmware..
	@if [ ! -d "$(DIR)/build" ]; then mkdir -p $(DIR)/build; fi
	@if [ -e "$(QMK)/.build/feb42_$(km).bin" ]; then cp "$(QMK)/.build/feb42_$(km).bin" "$(DIR)/build/firmware.bin"; fi
	@if [ -e "$(QMK)/.build/feb42_$(km).hex" ]; then cp "$(QMK)/.build/feb42_$(km).hex" "$(DIR)/build/firmware.hex"; fi
	@if [ -e "$(QMK)/.build/feb42_$(km).elf" ]; then cp "$(QMK)/.build/feb42_$(km).elf" "$(DIR)/build/firmware.elf"; fi
	@if [ -e "$(DIR)/feb42_$(km).hex" ]; then rm -f $(DIR)/feb42_$(km).hex; fi
	@echo done
