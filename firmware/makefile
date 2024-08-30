.PHONY: all help push copy build flash
MAKEFLAGS += --no-print-directory

kb=feb40
km=default

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: help

push: ## [m="my message"]
	$(eval m ?= $(if $(m),$(m),"update"))
	@git add --all
	@git commit -m "$(m)"
	@git push

build: ## [km=my_keymap]
	@qmk compile -kb $(kb) -km $(km)
	@make copy -B km=$(km)

flash: ## [console=true|false] [km=my_keymap]
	@qmk flash -kb $(kb) -km $(km)
	@make copy -B km=$(km)
ifeq ($(console),true)
	@make console
endif

console: ## opens console
	@qmk console

# private

copy:
	@echo Copying firmware to ./build
	@if [ -e "../../.build/${kb}_$(km).bin" ]; then cp "../../.build/${kb}_$(km).bin" "./build/${kb}_$(km).bin"; fi
	@if [ -e "../../.build/${kb}_$(km).hex" ]; then cp "../../.build/${kb}_$(km).hex" "./build/${kb}_$(km).hex"; fi
