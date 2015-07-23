#include <cstdlib>

inline int random(int min, int max) { return rand() % (max + 1 - min) + min; }

class MapGenerator {
public:
	MapGenerator(int width, int height);
	~MapGenerator() { delete mMap; }
	
	void setIterations(int i) { mIterations = i; }
	void setDeathThreshold(int t) { mDeathThreshold = t; }
	void setBirthThreshold(int t) { mBirthThreshold = t; }
	void setStartAlive(int s) { mStartAliveChance = s; }
	void setSeed(int s) { srand(s); }

	void print();
	void generate();
protected:
	char* mMap = nullptr;
	int mWidth;
	int mHeight;
	int mIterations = 2;
	int mDeathThreshold = 2;
	int mBirthThreshold = 2;
	int mStartAliveChance = 60;

	void initializeMap();
	int getAliveNeighbours(int x, int y);
};