/*
 * maze.h
 *
 *  Created on: 24 avr. 2019
 *      Author: bdosd
 */

#ifndef MAZE_H_
#define MAZE_H_

#include "stdint.h"

struct Info
{
	// The distance of the cell from the source (no units)
	uint16_t distance;
	// bit 0 is whether or not the cell has been visited
	uint8_t misc;
};

class maze
{
public:
	maze();
	virtual ~maze();

	static const uint8_t WIDTH = 16;
	static const uint8_t HEIGHT = 16;

	// The x and y positions of the lower left and upper right center cells
	static const uint8_t CLLX = (WIDTH - 1) / 2;
	static const uint8_t CLLY = (HEIGHT - 1) / 2;
	static const uint8_t CURX = (WIDTH) / 2;
	static const uint8_t CURY = (HEIGHT) / 2;

	// For each cell, we store only eight bits of information: four bits for
	// whether we know the value of a wall, and four bits for the actual value
	//
	//    info |  known  |  walls  |
	//         |---------|---------|
	//     dir | e s w n | e s w n |
	//         |---------|---------|
	//    bits | 7 6 5 4 | 3 2 1 0 |
	//
	// Furthermore, each cell can be indexed by just eight bits: at most
	// four bits for the x position, and at most four bits for the y position
	//
	uint8_t m_data[WIDTH * HEIGHT];
	Info m_dataDijkstra[WIDTH * HEIGHT];

	uint8_t	mousePos;
	uint8_t	mouseDir;

	void initDijkstra();

	void findPath(uint8_t mousePos);

	uint8_t getCell(uint8_t x, uint8_t y);

	bool isKnown(uint8_t cell, uint8_t direction);
	bool isWall(uint8_t cell, uint8_t direction);

	bool isCenter(uint8_t cell);

	bool scanWall();
};

#endif /* MAZE_H_ */
