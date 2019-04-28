/*
 * maze.cpp
 *
 *  Created on: 24 avr. 2019
 *      Author: bdosd
 */

#include "API.h"

#include "maze.h"

maze::maze()
{
	for (int ii = 0; ii < WIDTH * HEIGHT; ii++)
	{
		m_data[ii] = 0;
	}

	for (int ii = 0; ii < WIDTH; ii++)
	{
		m_data[ii] = 0xF4;
		m_data[ii + (HEIGHT - 1) * WIDTH] = 0xF1;
	}

	for (int ii = 0; ii < HEIGHT; ii++)
	{
		m_data[ii * WIDTH] = 0xF2;
		m_data[(ii * WIDTH) + HEIGHT - 1] = 0xF8;
	}

	m_data[0] = 0xF6;
	m_data[WIDTH - 1] = 0xFC;
	 m_data[(HEIGHT - 1) * WIDTH] = 0xF3;
	 m_data[(HEIGHT * WIDTH) - 1] = 0xF9;

	mousePos = 0;
	mouseDir = 0;
}

maze::~maze()
{
	// TODO Auto-generated destructor stub
}

void maze::initDijkstra()
{
	for (int ii = 0; ii < WIDTH * HEIGHT; ii++)
	{
		m_dataDijkstra[ii].distance = -1; // Here -1 is used to get the maximum unsigned value
		m_dataDijkstra[ii].misc = 0;
	}

}

void maze::findPath(uint8_t mousePos)
{
	uint8_t currentPos;
	uint8_t nextPos;

	initDijkstra();
	nextPos = mousePos;
	m_dataDijkstra[mousePos].distance = 0;

	while (!isCenter(currentPos))
	{
		currentPos = nextPos;
		m_dataDijkstra[currentPos].misc |= 0x1; //set as visited

		if (!isKnown(currentPos, 0) || !isWall(currentPos, 0))
		{
			if (!(m_dataDijkstra[currentPos + WIDTH].misc & 0x01)) // if not visited
				m_dataDijkstra[currentPos + WIDTH].distance = m_dataDijkstra[currentPos].distance + 1;
		}
		if (!isKnown(currentPos, 1) || !isWall(currentPos, 1))
		{
			if (!(m_dataDijkstra[currentPos - WIDTH].misc & 0x01)) // if not visited
				m_dataDijkstra[currentPos - WIDTH].distance = m_dataDijkstra[currentPos].distance + 1;
		}
		if (!isKnown(currentPos, 2) || !isWall(currentPos, 2))
		{
			if (!(m_dataDijkstra[currentPos + 1].misc & 0x01)) // if not visited
				m_dataDijkstra[currentPos + 1].distance = m_dataDijkstra[currentPos].distance + 1;
		}
		if (!isKnown(currentPos, 3) || !isWall(currentPos, 3))
		{
			if (!(m_dataDijkstra[currentPos - 1].misc & 0x01)) // if not visited
				m_dataDijkstra[currentPos - 1].distance = m_dataDijkstra[currentPos].distance + 1;
		}

		//look for the next cell
		uint16_t minDist = -1;
		for (int ii = 0; ii < WIDTH * HEIGHT; ii++)
		{
			if (!(m_dataDijkstra[ii].misc & 0x01)) // if not visited
			{
				if (m_dataDijkstra[ii].distance < minDist)
				{
					minDist = m_dataDijkstra[ii].distance;
					nextPos = ii;
				}
			}
		}
	}
}

uint8_t maze::getCell(uint8_t x, uint8_t y)
{
	return x * HEIGHT + y;
}

bool maze::isKnown(uint8_t cell, uint8_t direction)
{
	return (m_data[cell] >> (direction + 4)) & 1;
}

bool maze::isWall(uint8_t cell, uint8_t direction)
{
	return (m_data[cell] >> direction) & 1;
}

bool maze::isCenter(uint8_t cell)
{
	if (cell == CLLX * WIDTH + CLLY)
		return 1;
	if (cell == CLLX * WIDTH + CURY)
		return 1;
	if (cell == CURX * WIDTH + CLLY)
		return 1;
	if (cell == CURX * WIDTH + CURY)
		return 1;
	return 0;
}

bool maze::scanWall()
{
	int tmp;

	if (API::wallFront())
	{
		m_data[mousePos] |= 0x11 << mouseDir;
	}

	if (API::wallLeft())
	{
		tmp = 0x2222 << mouseDir;
		m_data[mousePos] |=(tmp>>8)&0xFF;
	}

	if (API::wallRight())
	{
		tmp = 0x8888 << mouseDir;
		m_data[mousePos] |=(tmp>>8)&0xFF;

	}
	return 0;
}

