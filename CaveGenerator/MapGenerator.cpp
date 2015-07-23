#include "MapGenerator.h"
#include <iostream>

void MapGenerator::print() {
	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++) {
			if (mMap[y*mWidth + x])
				std::cout << ".";
			else
				std::cout << "#";
		}
		std::cout << std::endl;
	}
}

char* MapGenerator::generate() {
	initializeMap();
	for (int i = 0; i < mIterations; i++)
		doIteration();
	return mMap;
}

void MapGenerator::initializeMap() {
	int n = mWidth * mHeight;
	mMap = new char[n];
	memset(mMap, 0, n*sizeof(char));
	for (int y = 1; y < mHeight - 1; y++)
		for (int x = 1; x < mWidth - 1; x++)
			mMap[y*mWidth + x] = random(1, 100) < mStartAliveChance ? 1 : 0;
}

void MapGenerator::doIteration() {
	int n = mWidth*mHeight;
	char* newMap = new char[n];
	for (int i = 0; i < n; i++) {
		if (i%mWidth == 0 || i / mWidth == 0 || i / mWidth == mHeight - 1) {
			newMap[i] = 0;
			continue;
		}
		int aliveNeighbours = getAliveNeighbours(i % mWidth, i / mWidth);
		if (mMap[i])
			newMap[i] = aliveNeighbours < mDeathThreshold ? 0 : 1;
		else
			newMap[i] = aliveNeighbours > mBirthThreshold ? 1 : 0;
	}
	delete mMap;
	mMap = newMap;
}

int MapGenerator::getAliveNeighbours(int x, int y) {
	int count = 0;
	for (int i = y - 1; i < y + 2; i++)
		for (int j = x - 1; j < x + 2; j++) {
			if (j < 0 || j > mWidth || i < 0 || i > mHeight || (i == y && j == x))
				continue;
			count += mMap[i*mWidth + j];
		}
	return count;
}