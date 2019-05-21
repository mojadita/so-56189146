# Makefile -- makefile for Stack Overflow question 56189146.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Tue May 21 13:48:55 EEST 2019

targets = pru_56189146
toclean = $(targets)

RM ?= rm -f

pru_56189146_objs = pru_56189146.o
toclean += $(pru_56189146_objs)

all: $(targets)
clean:
	$(RM) $(toclean)

pru_56189146: $(pru_56189146_deps) $(pru_56189146_objs)
	$(CC) $(LDFLAGS) $(pru_56189146_objs) \
		$(pru_56189146_ldflags) $(pru_56189146_libs) -o $@
