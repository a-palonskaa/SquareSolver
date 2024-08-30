CC = g++
CFLAGS = -Wall -std=c++17 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations   \
		 -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy     \
		 -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2     \
		 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith       \
		 -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo           \
		 -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef   \
		 -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-range 			     \
		 -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast 			 \
		 -Wno-varargs -Wstack-protector -Wsuggest-override -Wbounds-attributes-redundant \
		 -Wlong-long -Wopenmp -fcheck-new -fsized-deallocation -fstack-protector 		 \
		 -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-protector  \
		 -fPIE -Werror=vla
LDFLAGS =

INCLUDE_DIR = include
SOURCE_DIR  = src
BUILD_DIR   = build

SOURCES = arg_parser.cpp buffer_clean.cpp compare_double.cpp get_data.cpp logger.cpp main.cpp \
		  show_results.cpp solve_quadr.cpp test_library.cpp test_solve_quadr.cpp
SOURCES := $(addprefix $(SOURCE_DIR)/, $(SOURCES))

OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:%.cpp=%.o))
DEPS 	= $(OBJECTS:.o=.d)

CFLAGS += -I$(INCLUDE_DIR) #-I добавляет пути по которым можно искать headers  и мы довавляем хэдэра туда

EXECUTABLE = $(BUILD_DIR)/square

.PHONY: all debug release

all: release

debug: CFLAGS += -D _DEBUG -D TESTING -ggdb3 -O0
debug: $(EXECUTABLE)

release: CFLAGS += -O2 -DNDEBUG
release: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPS): $(BUILD_DIR)/%.d: %.cpp
	@mkdir -p $(@D)
	$(CC) -E $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@

.PHONY: clean #псевдоцель(не привязана к файлуб таргет который не файл)
clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(DEPS)

NODEPS = clean

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif

