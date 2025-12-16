MAIN = main

LATEXMK_FLAGS = -pdf -shell-escape -interaction=nonstopmode

.PHONY: compile watch live clean cleanall

compile:
	latexmk $(LATEXMK_FLAGS) $(MAIN).tex

watch:
	evince main.pdf &
	latexmk $(LATEXMK_FLAGS) -pvc -view=none $(MAIN).tex

clean:
	latexmk -c

cleanall:
	latexmk -C
	rm -rf _minted-$(MAIN) || true

