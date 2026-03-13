CC=gcc
SRC=src
BIN=bin

build:
	$(CC) $(SRC)/main.c -o $(BIN)/main

run: build
	$(BIN)/main