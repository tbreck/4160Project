
CXX = g++

DEPDIR := .deps
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(basename $*).Td

CXXFLAGS = `sdl2-config --cflags` -g -std=c++11 -O0 -I `sdl2-config --prefix`/include/

LDFLAGS = `sdl2-config --libs` -lm -lSDL2_image -lexpat -lSDL2_ttf -lSDL2_mixer

SRCPTH = $(shell find . -regex ".*\.cpp" | tr '\n' ' ')
SRCFLS = $(notdir $(SRCPTH))
SRCDIR = $(dir $(SRCPTH))

OBJDIR  = build
$(shell mkdir -p $(OBJDIR) >/dev/null)
OBJFLS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRCFLS))

EXEC = run

VPATH = $(SRCDIR)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

$(OBJDIR)/%.o: %.cpp
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.d
	@echo "Creating Object $(notdir $@)"
	@$(CXX) $(DEPFLAGS) $(CXXFLAGS) -c $< -o $@
	@mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

$(EXEC): $(OBJFLS)
	@echo "Creating Executable $@"
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJFLS) $(LDFLAGS)

clean:
	@echo "Deleting Objects"
	@rm -rf $(OBJDIR)
	@echo "Deleting Executable"
	@rm -rf $(EXEC)
	@echo "Deleting Dependecy List"
	@rm -rf $(DEPDIR)
	@echo "Deleting Images"
	@rm -rf frames/*.bmp

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(notdir $(basename $(OBJFLS)))))
