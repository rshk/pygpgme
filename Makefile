PYTHON = python

build:
	$(PYTHON) setup.py build_ext -i

check: build
	GPG_AGENT_INFO= $(PYTHON) test_all.py -v

clean:
	$(PYTHON) setup.py clean

dist: build
	$(PYTHON) setup.py sdist --force-manifest

.PHONY: build check clean dist
