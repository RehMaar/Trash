STDEV = stdev
STDEV_I = stdev_i
STDEV_W = stdev_w

all: report.pdf

report.pdf: report.tex $(STDEV).png $(STDEV_I).png $(STDEV_W).png
	pdflatex $<

$(STDEV).png: $(STDEV).gnu $(STDEV).dat
	gnuplot $<
	
$(STDEV_I).png: $(STDEV_I).gnu $(STDEV_I).dat
	gnuplot $<

$(STDEV_W).png: $(STDEV_W).gnu $(STDEV_W).dat
	gnuplot $<

%.dat:
	cd ../FHTrasnform/ && cargo run && cd - && cp ../FHTrasnform/*.dat .

clean:
	rm *.dat *.aux *.log *.png
.PHONY: clean
