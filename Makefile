# Copyright (c) 2020 Mertcan Davulcu
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# VARIABLES
G++ = g++
G++H = $(G++) -c
OUT = -o

DIR_INCLUDE = ./include
DIR_SOURCE = ./src
DIR_PARSER = $(DIR_SOURCE)/parser
DIR_UTILS = $(DIR_SOURCE)/utils

define GENERIC
processor.o
endef

define PARSER
grammar.o \
lexer.o \
tokens.o
endef

define UTILS
io.o \
string.o
endef

# WORKFLOW
workflow: include compile
include: $(GENERIC) $(PARSER) $(UTILS)

# INCLUDE
processor.o: $(DIR_SOURCE)/processor.cc
	$(G++H) $< $(OUT) processor.o

# PARSER
grammar.o: $(DIR_PARSER)/grammar.cc
	$(G++H) $< $(OUT) grammar.o

lexer.o: $(DIR_PARSER)/lexer.cc
	$(G++H) $< $(OUT) lexer.o

tokens.o: $(DIR_PARSER)/tokens.cc
	$(G++H) $< $(OUT) tokens.o

# UTILS
io.o: $(DIR_UTILS)/io.cc
	$(G++H) $< $(OUT) io.o

string.o: $(DIR_UTILS)/string.cc
	$(G++H) $< $(OUT) string.o

compile: $(DIR_SOURCE)/main.cc
	$(G++) $< $(GENERIC) $(PARSER) $(UTILS) $(OUT) reli
