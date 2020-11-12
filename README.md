# File Manager

I made this for managing emails stored locally, but is made for basic general file management.
Yes, I know what your thinking, "why would anyone ever do this!?"
Well, I have my reasons. 
Either way, you can use this for what ever you want.

My temporary compiling solution while I figure out how to makefile
clang++ --std=c++17 -g -Wall -IFileManager/include FileManager/examples/main.cpp FileManager/src/emlreader/EMLReader.cpp FileManager/src/search/Search.cpp