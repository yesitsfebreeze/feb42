# Copyright 2018-2024 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later

# avoid 'Entering|Leaving directory' messages
MAKEFLAGS += --no-print-directory

QMK_USERSPACE := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(QMK_USERSPACE),)
    QMK_USERSPACE := $(shell pwd)
endif

# Add extra binaries to path
export PATH := $(QMK_USERSPACE)/bin:$(PATH)

# Deal with macOS
ifeq ($(shell uname -s),Darwin)
SED = gsed
ECHO = gecho
else
SED = sed
ECHO = echo
endif

#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Repositories

$(QMK_USERSPACE)/qmk_firmware:
	git clone --depth=1 https://github.com/tzarc/qmk_firmware.git $(QMK_USERSPACE)/qmk_firmware \
		&& cd $(QMK_USERSPACE)/qmk_firmware \
		&& git sshsign

$(QMK_USERSPACE)/qmk_userspace:
	git clone --depth=1 https://github.com/qmk/qmk_userspace.git $(QMK_USERSPACE)/qmk_userspace \
		&& cd $(QMK_USERSPACE)/qmk_userspace \
		&& git pull --ff-only \
		&& git sshsign

$(QMK_USERSPACE)/qmk-dot-github:
	git clone --depth=1 https://github.com/qmk/.github.git $(QMK_USERSPACE)/qmk-dot-github \
		&& cd $(QMK_USERSPACE)/qmk-dot-github \
		&& git pull --ff-only \
		&& git sshsign

qmk_firmware: $(QMK_USERSPACE)/qmk_firmware
qmk_userspace: $(QMK_USERSPACE)/qmk_userspace
qmk-dot-github: $(QMK_USERSPACE)/qmk-dot-github

.PHONY: shrink
shrink: repositories
	@git -C $(QMK_USERSPACE) shrink
	@git -C $(QMK_USERSPACE)/qmk_firmware shrink
	@git -C $(QMK_USERSPACE)/qmk_userspace shrink
	@git -C $(QMK_USERSPACE)/qmk-dot-github shrink


.PHONY: repositories
repositories: qmk_firmware qmk_userspace qmk-dot-github

#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Cleaning

.PHONY: clean distclean userspace_clean

userspace_clean:
	@rm -f $(QMK_USERSPACE)/compile_commands.json $(QMK_USERSPACE)/*.bin $(QMK_USERSPACE)/*.hex $(QMK_USERSPACE)/*.uf2 || true
	@rm -rf $(QMK_USERSPACE)/.cache || true

clean: userspace_clean
	@$(MAKE) -C $(QMK_USERSPACE)/qmk_firmware clean

distclean: userspace_clean
	@$(MAKE) -C $(QMK_USERSPACE)/qmk_firmware distclean

#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Container management

CONTAINER_PREAMBLE := export HOME="/tmp"; export PATH="/tmp/.local/bin:\$$PATH"; python3 -m pip install --upgrade pip; python3 -m pip install -r requirements-dev.txt

.PHONY: format-core pytest format-and-pytest
format-core:
	make -C $(QMK_USERSPACE)/qmk_firmware format-core

pytest:
	make -C $(QMK_USERSPACE)/qmk_firmware pytest

format-and-pytest:
	make -C $(QMK_USERSPACE)/qmk_firmware format-and-pytest

.PHONY: format-keyboards-tzarc
format-keyboards-tzarc:
	cd $(QMK_USERSPACE)/qmk_firmware \
		&& RUNTIME=docker ./util/docker_cmd.sh bash -lic "$(CONTAINER_PREAMBLE); qmk format-c \$$(find keyboards/tzarc \( -name '*.c' -o -name '*.h' \) -and -not -name '*.qgf.*' -and -not -name '*.qff.*' -and -not -name '*conf.h' -and -not -name 'board.h')"

.PHONY: all-vusb all-lufa all-chibios all-riot
all-vusb:
	qmk mass-compile -j$(shell getconf _NPROCESSORS_ONLN 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || $(ECHO) 2) -f protocol=VUSB

all-lufa:
	qmk mass-compile -j$(shell getconf _NPROCESSORS_ONLN 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || $(ECHO) 2) -f protocol=LUFA

all-chibios:
	qmk mass-compile -j$(shell getconf _NPROCESSORS_ONLN 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || $(ECHO) 2) -f protocol=ChibiOS

all-riot:
	qmk mass-compile -j$(shell getconf _NPROCESSORS_ONLN 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || $(ECHO) 2) -f protocol=RIOT

#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Helpers

.PHONY: rgb_effects generated-files format

generated-files: rgb_effects

rgb_effects:
	@"$(QMK_USERSPACE)/bin/generate_rgb_effects.py" > "$(QMK_USERSPACE)/users/tzarc/enable_all_rgb_effects.h"

format:
	@git ls-files | grep -E '\.(c|h|cpp|hpp|cxx|hxx|inc)$$' | grep -vE '\.q[gf]f\.' | grep -vE '(ch|hal|mcu)conf\.h$$' | grep -vE 'board.[ch]$$' | grep -vE '.inl.h$$' | grep -vE 'mini-rv32ima.h$$' | while read file ; do \
		$(ECHO) -e "\e[38;5;14mFormatting: $$file\e[0m" ; \
		clang-format -i "$$file" ; \
	done

format-qmk-keyboards-tzarc:
	@git -C $(QMK_USERSPACE)/qmk_firmware ls-files | grep tzarc | grep -E '\.(c|h|cpp|hpp|cxx|hxx)$$' | grep -vE '\.q[gf]f\.' | grep -vE '(ch|hal|mcu)conf\.h$$' | grep -vE 'board.[ch]$$' | grep -vE 'mini-rv32ima.h$$' | while read file ; do \
		$(ECHO) -e "\e[38;5;14mFormatting: $$file\e[0m" ; \
		clang-format -i "$(QMK_USERSPACE)/qmk_firmware/$$file" ; \
	done

.PHONY: links link-hooks

links: link-hooks

link-hooks:
	@[ -e "$(QMK_USERSPACE)/qmk_firmware/.git/hooks/post-checkout" ] || \
		{ \
			$(ECHO) -e "\e[38;5;14mSymlinking: $(QMK_USERSPACE)/bin/post-checkout.sh -> $(QMK_USERSPACE)/qmk_firmware/.git/hooks/post-checkout\e[0m" ; \
			ln -sf "$(QMK_USERSPACE)/bin/post-checkout.sh" "$(QMK_USERSPACE)/qmk_firmware/.git/hooks/post-checkout" ; \
		}

#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Builds

# short name ! keyboard path ! keymap name
BOARD_DEFS := feb42!feb42!default 

keyboards_folder := keyboards/
empty :=
define handle_board_entry
board_name_$1 := $$(word 1,$$(subst !, ,$1))
board_keyboard_$1 := $$(word 2,$$(subst !, ,$1))
board_keyboard_stripped_$1 := $$(subst $$(keyboards_folder),$$(empty),$$(board_keyboard_$1))
board_keymap_$1 := $$(word 3,$$(subst !, ,$1))

.PHONY: $$(board_name_$1) bin_$$(board_name_$1)

$$(board_name_$1): bin_$$(board_name_$1)

bin_$$(board_name_$1): rgb_effects
	@$(ECHO) -e "\e[38;5;14mBuilding: $$(board_keyboard_stripped_$1):$$(board_keymap_$1)\e[0m"
	+@cd "$(QMK_USERSPACE)/qmk_firmware" \
		&& { \
			[ -z "$$(NO_COMPILEDB)" ] \
				&& qmk compile --compiledb -kb $$(board_keyboard_stripped_$1) -km $$(board_keymap_$1) \
				|| qmk compile -kb $$(board_keyboard_stripped_$1) -km $$(board_keymap_$1); \
		}
	@[ -e "$$(QMK_USERSPACE)/qmk_firmware/compile_commands.json" ] && cp $$(QMK_USERSPACE)/qmk_firmware/compile_commands.json $$(QMK_USERSPACE) \
		|| true
endef
$(foreach board_entry,$(BOARD_DEFS),$(eval $(call handle_board_entry,$(board_entry))))

# define handle_linked_board_entry
# board_name_$1 := $$(word 1,$$(subst !, ,$1))
# board_keyboard_$1 := $$(word 2,$$(subst !, ,$1))
# board_keymap_$1 := $$(word 3,$$(subst !, ,$1))
# link_source_$1 := $$(word 4,$$(subst !, ,$1))
# link_target_$1 := $$(word 5,$$(subst !, ,$1))

# ifeq ($$(link_target_$1),)
# link_target_$1 := $$(board_keyboard_$1)
# endif

# bin_$$(board_name_$1): link_$$(link_target_$1)

# .PHONY: links link_$$(link_target_$1) unlinks unlink_$$(link_target_$1)

# links: link_$$(link_target_$1)
# link_$$(link_target_$1): qmk_firmware
# 	@if [ ! -L "$(QMK_USERSPACE)/qmk_firmware/$$(link_target_$1)" ] ; then \
# 		$(ECHO) -e "\e[38;5;14mSymlinking: $$(link_source_$1) -> $$(link_target_$1)\e[0m" ; \
# 		mkdir -p $$(shell dirname "$(QMK_USERSPACE)/qmk_firmware/$$(link_target_$1)") ; \
# 		ln -sf $(QMK_USERSPACE)/$$(link_source_$1) $(QMK_USERSPACE)/qmk_firmware/$$(link_target_$1) ; \
# 		if [ -z "$$(grep -P '^$$(link_target_$1)$$$$' $(QMK_USERSPACE)/qmk_firmware/.git/info/exclude 2>/dev/null)" ] ; then \
# 			$(ECHO) $$(link_target_$1) >> $(QMK_USERSPACE)/qmk_firmware/.git/info/exclude ; \
# 		fi ; \
# 	fi

# unlinks: unlink_$$(link_target_$1)
# unlink_$$(link_target_$1): qmk_firmware
# 	@if [ -L "$(QMK_USERSPACE)/qmk_firmware/$$(link_target_$1)" ] ; then \
# 		$(ECHO) -e "\e[38;5;14mRemoving symlink: $$(link_source_$1) -> $$(link_target_$1)\e[0m" ; \
# 		rm $(QMK_USERSPACE)/qmk_firmware/$$(link_target_$1) || true; \
# 		$(SED) -i "\@^$$(link_target_$1)@d" $(QMK_USERSPACE)/qmk_firmware/.git/info/exclude; \
# 	fi

# clean: unlink_$$(link_target_$1)
# distclean: unlink_$$(link_target_$1)

# generated-files: links
# endef
# $(foreach board_entry,$(LINKED_BOARD_DEFS),$(eval $(call handle_board_entry,$(board_entry))))
# $(foreach board_entry,$(LINKED_BOARD_DEFS),$(eval $(call handle_linked_board_entry,$(board_entry))))
