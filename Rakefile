require "rake/clean"
require 'rake/loaders/makefile'
class String
  def /(other)
    File.join(self, other)
  end
end

HEADER_DIRS = ["Engine2d", "game", "."]
HEADER_INCLUDE = HEADER_DIRS.map { |d| "-I#{d}" }.join(" ")
# DEFAULT_FLAGS = "-w -D_DEBUG -g"
DEFAULT_FLAGS = "-Werror `sdl-config --cflags` `libpng-config --cppflags`"
CFLAGS = "#{ENV['FLAGS'] || DEFAULT_FLAGS} #{HEADER_INCLUDE}"
LINKER_FLAGS = "-lGL -lGLU -ljpeg `sdl-config --libs` -lSDL_mixer -lSDL_ttf -lSDL_image `libpng-config --libs`"

directory "bin"
SRC = FileList["**/*.cpp", "**/*.cc"]
OBJECTS = SRC.pathmap("%X.o")
BIN = "bin/legion"

DEPS = ".depends.mf"
file DEPS => [SRC].flatten do |t|
	sh "gcc -M #{CFLAGS} #{t.prerequisites.join " "} > #{t.name} || rm #{DEPS}" 
end

import ".depends.mf" 

rule '.o' => ['.cc'] do |t|
	sh "c++ #{CFLAGS} -c -o #{t.name} #{t.source}"
end

rule '.o' => ['.cpp'] do |t|
	sh "c++ #{CFLAGS} -c -o #{t.name} #{t.source}"
end

SRC.each do |src|
  file src.ext(".o") => src
end

BIN_GEN = Proc.new do |t|
  Rake::Task["bin"].invoke
  sh "c++ #{LINKER_FLAGS} -o #{t.name} #{t.prerequisites.join(" ")}"
end

def gen_bin(bin, src)
  multitask(bin => src.pathmap("%X.o"), &BIN_GEN)
end
gen_bin BIN, SRC

desc "Creates .o files."
task :objects => OBJECTS

task :default => BIN

CLEAN.include(OBJECTS, BIN, ".depends.mf")

