#include "MapGenerator.h"
#include <iostream>


MapGenerator::MapGenerator(int width, int height) {
	mWidth = width;
	mHeight = height;
	mMap = new char[width*height];
}

void MapGenerator::generate() {
	initializeMap();
	for (int i = 0; i < mIterations; i++) {
		char* auxMap = new char[mWidth*mHeight];
		for (int y = 0; y < mHeight; y++) {
			for (int x = 0; x < mWidth; x++) {
				int aliveNeighbours = getAliveNeighbours(x, y);
				if (mMap[y*mWidth + x]) {
					if (aliveNeighbours < mDeathThreshold)
						auxMap[y*mWidth + x] = 0;
					else
						auxMap[y*mWidth + x] = 1;
				}
				else {
					if (aliveNeighbours > mBirthThreshold)
						auxMap[y*mWidth + x] = 1;
					else
						auxMap[y*mWidth + x] = 0;
				}
			}
		}
		delete mMap;
		mMap = auxMap;
		auxMap = nullptr;
	}
}

void MapGenerator::print() {
	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++)
			if (mMap[y*mWidth + x])
				std::cout << ".";
			else
				std::cout << "#";
		std::cout << std::endl;
	}
}

void MapGenerator::initializeMap() {
	int n = mWidth * mHeight;
	for (int i = 0; i < n; i++)
		if (random(1, 100) < mStartAliveChance)
			mMap[i] = 1;
		else
			mMap[i] = 0;
}

int MapGenerator::getAliveNeighbours(int x, int y) {
	int count = 0;
	for (int i = y - 1; i < y + 2; i++) {
		for (int j = x - 1; j < x + 2; j++) {
			if (j < 0 || j > mWidth || i < 0 || i > mHeight || (i == y && j == x)) continue;
			count += mMap[i*mWidth + j];
		}
	}
	return count;
}