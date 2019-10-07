cmake_minimum_required (VERSION 2.6)

project (loyds-puzzle)

set( SOURCES main.c configuration.c loydTree.c )
add_executable(loyds-puzzle ${SOURCES} )