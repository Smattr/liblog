ifneq (${V},)
Q :=
else
Q := @
endif

O ?= build
SRC ?= src
CC ?= gcc
AR ?= ar

.PHONY: default
default: ${O}/liblog.a ${O}/liblog.so

${O}/liblog.a: ${SRC}/log.o | ${O}
	@echo " [AR] $@"
	${Q}${AR} rcs $@ $<

${O}/liblog.so: ${SRC}/log-shared.o | ${O}
	@echo " [LD] $@"
	${Q}${CC} -shared -o $@ $<

${SRC}/log.o: ${SRC}/log.c ${SRC}/log.h
	@echo " [CC] $@"
	${Q}${CC} -Wall -c $< -o $@

${SRC}/log-shared.o: ${SRC}/log.c ${SRC}/log.h
	@echo " [CC] $@"
	${Q}${CC} -fPIC -Wall -c $< -o $@

${O}:
	@mkdir -p $@

.PHONY: clean
clean:
	@echo " [CLEAN]"
	${Q}rm -rf ${O}
	${Q}rm -rf ${SRC}/*.o
