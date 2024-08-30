.PHONY: all help link compile flash copy_firmware push
MAKEFLAGS += --no-print-directory

kb=feb42

DIR := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(DIR),)
    DIR := $(shell pwd)
endif

QMK := $(shell qmk env QMK_HOME | sed -e 's|\\|/|g' -e 's|^\([A-Za-z]\):|/\L\1|')

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: help

link: ## links the keyboard into the qmk firmware folder
	@if [ -d "$(QMK)/keyboards/$(kb)" ]; then rm -rf $(QMK)/keyboards/$(kb); fi
	@echo Linking $(DIR)/firmware to $(QMK)/keyboards/$(kb)
	@ln -s "$(DIR)/firmware" "$(QMK)/keyboards/$(kb)"

compile: ## [km=keymap]
	@$(eval km ?= $(if $(km),$(km), "default"))
	@make link -B
	@qmk compile -kb $(kb) -km $(km)

flash: ## [km=keymap] [console=true|false]
	@$(eval km ?= $(if $(km),$(km), "default"))
	@make link -B
	@qmk flash -kb $(kb) -km $(km)
ifeq ($(console),true)
	@qmk console
endif

push: ## [m="message"]
	$(eval m ?= $(if $(m),$(m),"update"))
	@git add --all
	@git commit -m "$(m)"
	@git push
