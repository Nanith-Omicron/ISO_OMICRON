#pragma once
#include "Primitive.h"
#include "tile.h"
#include <vector>
#include "item.h"

//A singular Cell 
struct Cell {
	std::vector<actor*>peps;
	int x{};
	int y{};
};

//Grid for spatial partioning 
class Grid {

public:
 
	Grid(int w, int h, int cs);
	~Grid();
	
	//
	Cell* getCell(int x, int y);
	Cell* getCell(const glm::vec2& pos);


	void updateCollision();
	void checkCollision(actor* p, std::vector<actor*>& check, int ind);
	void removePrimitiveFromCell(actor* p);
	void refresh(std::vector<actor*>* p);
	void refresh(std::vector<actor*>* p, actor* player);
	void refresh(std::vector<item*>* p, actor* player);
	void addPrimitive(actor* p);
	void addPrimitives(std::vector<actor*>& p);
	void addPrimitive(actor* p, Cell* c);

	std::vector<Cell> cells;
	int cellSize=0, width=0, height=0, numXCells=0, numYCells=0;

};