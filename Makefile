# BUILD SETTINGS ###########################################

TARGET := ConeVoronoi

# FLAGS ####################################################

ifneq ($(MAKECMDGOALS), release)
    CONFIG := debug
    EXTRA_CXXFLAGS += -g3 -O0
else
    CONFIG := release
    EXTRA_CXXFLAGS += -g0 -O2 -DNDEBUG
endif

EXTRA_CXXFLAGS += -pedantic -Wall -Wextra -Wno-unused
ALL_CXXFLAGS += -std=c++0x -MMD -Iinclude $(EXTRA_CXXFLAGS) $(CXXFLAGS)
ALL_LDFLAGS += -Llib $(LDFLAGS)
LDLIBS += -lGL -lGLU -lglut -lm
############################################################

TARGET := bin/$(TARGET)
JUNK := bin/obj-$(CONFIG)

STRIP := strip

OBJS := $(shell find src -name *.cpp | sed "s/^src\///")
OBJS := $(foreach obj, $(OBJS:.cpp=.o), $(JUNK)$(obj))

# RULES ####################################################

.PHONY : all release clean

all : $(TARGET)

release : all
	@$(STRIP) $(TARGET)

clean :
	@rm -rf bin/*

ifneq ($(MAKECMDGOALS), clean)
    -include $(OBJS:.o=.d)
endif

$(TARGET) : $(OBJS)
	@$(CXX) -o $@ $(ALL_LDFLAGS) $^ $(LDLIBS)

$(JUNK)%.o : src/%.cpp
	@mkdir -p "$(dir $@)"
	@$(CXX) -c -o $@ $(ALL_CXXFLAGS) $<
