########## PROJECT SPECIFIC

SOURCE := matrix.hpp problem.cpp solution.hpp
OBJECT := problem.o# algorithm.o
ALGORITHMS := nosolve greedy hungarian hungarian_sp munkres

########## DEFAULT

# folder where to put debugging files
DEBUG_DIR := ./debug
DEBUG_FLAGS := -D_GLIBCXX_DEBUG -Wpedantic -Wconversion -Wextra -Wall -DDEBUGMODE -std=c++17
BINARY := lsap_solver
COMPILE_FLAGS := -DNDEBUG -O3 -Wopenmp-simd -std=c++17
COMPILE_FLAGS_CUDA := -02 -std=c++17

CXXSRC := $(filter %.cpp, $(SOURCE))

########## MAIN

#execute this to compile all algorithms in their directories
lsaps: $(ALGORITHMS) min_cost

#%.o: %.cpp matrix.hpp abstractsolver.hpp solution.hpp
#	$(CXX) $(COMPILE_FLAGS) -c $<

problem.o: problem.cpp matrix.hpp
	$(CXX) $(COMPILE_FLAGS) -c $<

ALGALG := $(foreach wrd,$(ALGORITHMS),$(wrd)/algorithm.o)
ALGMAIN := $(foreach wrd,$(ALGORITHMS),$(wrd)/main.o)

.PHONY: lsaps $(ALGORITHMS) min_cost lsaps_cuda hungarian_gpu greedy_cuda clean doc test benchmark

.SECONDEXPANSION:
$(ALGORITHMS): $(OBJECT) $$(addsuffix /algorithm.o,$$@) $$(addsuffix /main.o,$$@)
	@echo "Running build step for $@."
	$(CXX) $(COMPILE_FLAGS) -o $(addprefix $(addsuffix /,$@),$(BINARY)) $(addprefix -DCOMPILE_,$@) $^

.SECONDEXPANSION:
$(ALGALG): $$(subst .o,.cpp,$$@) $(OBJECT)
	$(CXX) $(COMPILE_FLAGS) -c $< -o $@

.SECONDEXPANSION:
$(ALGMAIN): main.cpp $$(subst /main.o,/algorithm.o,$$@) $(OBJECT)
	$(CXX) $(COMPILE_FLAGS) -c main.cpp -o $@

#hungarian: $(OBJECT) hungarian/algorithm.o
#	$(CXX) $(COMPILE_FLAGS) -o $(addprefix hungarian/,$(BINARY)) $^

#hungarian/algorithm.o: hungarian/algorithm.cpp
#	$(CXX) $(COMPILE_FLAGS) -c $< -o $@

min_cost:
	@echo "Running build step for $@."
	$(CXX) $(COMPILE_FLAGS) min_cost/main.cpp -o min_cost/$(BINARY)

########## CUDA GPU

lsaps_cuda: greedy_cuda hungarian_gpu

hungarian_gpu: $(OBJECT) hungarian_gpu/algorithm.o hungarian_gpu/main.o
	@echo "Running build step for $@."
	nvcc $(COMPILE_FLAGS) -o hungarian_gpu/$(BINARY) -DCOMPILE_hungarian_gpu

hungarian_gpu/algorithm.o: hungarian_gpu/algorithm.cu $(OBJECT)
	nvcc $(COMPILE_FLAGS_CUDA) -c $< -o $@

hungarian_gpu/main.o: main.cpp hungarian_gpu/algorithm.o $(OBJECT)
	nvcc $(COMPILE_FLAGS) -c main.cpp -o $@

greedy_cuda:
	@echo "Running build step for $@."
	nvcc $(COMPILE_FLAGS_CUDA) greedy_cuda/algorithm.cu -o greedy_cuda/$(BINARY)

########## TEST

test: lsaps
	bash ./test_each_each.sh

########## BENCHMARKS

benchmark: lsaps
	bash ./benchmark_each_each.sh

########## DEBUGGING

DEBUG_OBJECT := $(foreach wrd,$(OBJECT),$(DEBUG_DIR)/$(wrd))

debug: $(DEBUG_OBJECT)
	$(CXX) $(DEBUG_FLAGS) -o $(DEBUG_DIR)/$(BINARY) $^

$(DEBUG_DIR)/%.o: %.cpp %.hpp
	mkdir -p $(dir $@)
	$(CXX) $(DEBUG_FLAGS) -c $< -o $(DEBUG_DIR)/$(subst .cpp,.o,$<)

$(DEBUG_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(DEBUG_FLAGS) -c $< -o $(DEBUG_DIR)/$(subst .cpp,.o,$<)

########## EXTRA

# command to only generate the documentation
docs: $(SOURCE) ./Doxyfile
	@doxygen
	@open docs/html/index.html

clean:
	rm **/*.o
