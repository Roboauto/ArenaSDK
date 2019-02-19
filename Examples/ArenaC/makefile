SUBDIRS =   C_Acquisition                        \
            C_Enumeration                        \
            C_Streamables                        \
            C_Save

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)
DEPS = $(OBJS:%.o=%.d)

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	@echo '\n'[$@]
	$(MAKE) -C $@

SUBCLEAN = $(addsuffix .clean,$(SUBDIRS))

.PHONY: clean $(SUBCLEAN)
clean: $(SUBCLEAN)

$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean
