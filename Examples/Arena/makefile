SUBDIRS =   Cpp_Acquisition                        \
            Cpp_Acquisition_RapidAcquisition       \
            Cpp_Callback_OnEvent                   \
            Cpp_Callback_OnNodeChange              \
            Cpp_Callback_Polling                   \
            Cpp_ChunkData                          \
            Cpp_ChunkData_CRCValidation            \
            Cpp_Enumeration                        \
            Cpp_Exposure                           \
            Cpp_Exposure_ForHDR                    \
            Cpp_ForceIp                            \
            Cpp_Save                               \
            Cpp_Save_FileNamePattern               \
            Cpp_SimpleAcquisition                  \
            Cpp_Streamables                        \
            Cpp_Trigger                            \
            Cpp_UserSets                           \
            IpConfigUtility



SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
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


SUBRELEASE = $(addsuffix .release,$(SUBDIRS))

.PHONY: release $(SUBRELEASE)
release: $(SUBRELEASE)

$(SUBRELEASE): %.release:
	$(MAKE) -C $* release


SUBDEBUG = $(addsuffix .debug,$(SUBDIRS))

.PHONY: debug $(SUBDEBUG)
debug: $(SUBDEBUG)

$(SUBDEBUG): %.debug:
	$(MAKE) -C $* debug
