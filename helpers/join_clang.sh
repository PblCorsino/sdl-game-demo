#!/bin/sh

# Find and join all .clang complete files
# ag is in "The silver searcher" package
echo Join all clang complete files
find .. | ag clang_complete | xargs cat | sort | uniq > ../.clang_complete
