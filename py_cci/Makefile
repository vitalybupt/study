# Copyright 2018 6WIND S.A.

DIST = $(CURDIR)/dist
PYTHON = python3
PIP = $(PYTHON) -m pip
VIRTUALENV = $(PYTHON) -m venv
PIP_OPTS += --index  https://pypi.tuna.tsinghua.edu.cn/simple/ --timeout 120
VENV_OPTS += --clear
VENV = .venv
PKG_PYTHON_VERSION ?= 0.0.dev0
in_venv = . $(VENV)/bin/activate &&
empty :=
space := $(empty) $(empty)
join-with = $(subst $(space),$1,$(strip $2))

MODULES = $(wildcard modules/*)
PYTHONPATH = $(CURDIR):$(call join-with,:,$(MODULES))
LC_ALL = C.UTF-8

export PYTHONPATH LC_ALL

TARBALLS = $(addsuffix -$(PKG_PYTHON_VERSION).tar.gz,\
	$(addprefix $(DIST)/pycci-,$(notdir $(MODULES)))) \
	$(DIST)/pycci-$(PKG_PYTHON_VERSION).tar.gz

.PHONY: all
all: $(TARBALLS)

$(DIST)/pycci-$(PKG_PYTHON_VERSION).tar.gz: setup.py
	$(PYTHON) ./setup.py sdist --dist-dir=$(DIST)

$(DIST)/pycci-%-$(PKG_PYTHON_VERSION).tar.gz: modules/%
	cd $<; $(PYTHON) ./setup.py sdist --dist-dir=$(DIST)

SYSTEM_DEPS = \
	/usr/bin/cmake \
	/usr/include/libxml2/libxml/xmlversion.h \
	/usr/include/libxslt/xslt.h \
	/usr/include/pcre.h
pcre.h_PKG = libpcre3-dev
cmake_PKG = cmake
xmlversion.h_PKG = libxml2-dev
xslt.h_PKG = libxslt1-dev

$(SYSTEM_DEPS):
	@echo "error: missing $@"
	@echo "use: 'sudo apt-get install $($(@F)_PKG)' to fix the problem."
	@false

REQUIREMENTS = \
	requirements.txt

$(VENV)/bin/activate: $(SYSTEM_DEPS) $(REQUIREMENTS)
	$(VIRTUALENV) $(VENV_OPTS) $(VENV)
	$(in_venv) $(PIP) install $(PIP_OPTS) --upgrade pip setuptools wheel
	$(in_venv) $(PIP) install $(PIP_OPTS) -r $(REQUIREMENTS)


$(addprefix $(VENV)/bin/,pylint isort): $(VENV)/bin/activate
	$(in_venv) \
	$(PIP) install $(PIP_OPTS) \
		$(addprefix -r,$(REQUIREMENTS))

ORIG_REVISION = $$( \
	rebase_head=`git rev-parse --git-dir`/rebase-merge/head-name && \
	branch=`! [ -f $$rebase_head ] || cut -f3- -d/ $$rebase_head` && \
	git rev-parse --abbrev-ref $$branch@{upstream})
PY_FILES = $(shell git ls-files HEAD -- '*.py')
PY_FILES_CHANGED = $(shell \
	git diff --name-only --diff-filter=ACMR --relative $(ORIG_REVISION) -- '*.py')

GIT_REPO ?= .git
J ?= $(shell nproc)

.PHONY: lint
lint: $(VENV)/bin/pylint
ifneq ($(PY_FILES_CHANGED),)
	@echo "[flake8]"
	@$(in_venv) $(PYTHON) -m flake8 -j$(J) $(PY_FILES_CHANGED) || \
		{ echo "Use 'make format' to fix the problems."; exit 1; }
	@echo "[isort]"
	@$(in_venv) $(PYTHON) -m isort -j$(J) --diff --check-only $(PY_FILES_CHANGED) || \
		{ echo "Use 'make format' to fix the problems."; exit 1; }
	@echo "[pylint]"
	@$(in_venv) $(PYTHON) -m pylint $(PY_FILES_CHANGED)
endif

.PHONY: format
format: $(VENV)/bin/isort
ifneq ($(PY_FILES_CHANGED),)
	@echo "[isort]"
	@$(in_venv) $(PYTHON) -m isort -j$(J) $(PY_FILES_CHANGED)
endif

.PHONY: lint-full
lint-full: $(VENV)/bin/pylint $(py_extension)
	@echo "[flake8]"
	@$(in_venv) $(PYTHON) -m flake8 -j$(J) $(PY_FILES)
	@echo "[isort]"
	@$(in_venv) $(PYTHON) -m isort -j$(J) --diff --check-only $(PY_FILES) || \
		{ echo "Use 'make format' to fix the problems."; exit 1; }
	@echo "[pylint]"
	@$(in_venv) $(PYTHON) -m pylint $(PY_FILES)

tests: TESTS = `find cci -name '*.py'`

.PHONY: tests
tests: $(VENV)/bin/activate $(py_extension)
	$(in_venv) $(PYTHON) -Wd -m pytest -c $(TESTS)

