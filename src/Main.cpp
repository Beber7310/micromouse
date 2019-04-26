#include "API.h"

#include "maze.h"

int main(int argc, char* argv[])
{
	maze m;

	for (int ii = 0; ii < m.WIDTH * m.HEIGHT; ii++)
	{

		if (m.m_data[ii] & 0x01)
			API::setWall(ii % m.WIDTH, ii / m.HEIGHT, 'n');
		if (m.m_data[ii] & 0x02)
			API::setWall(ii % m.WIDTH, ii / m.HEIGHT, 's');
		if (m.m_data[ii] & 0x04)
			API::setWall(ii % m.WIDTH, ii / m.HEIGHT, 'e');
		if (m.m_data[ii] & 0x08)
			API::setWall(ii % m.WIDTH, ii / m.HEIGHT, 'w');
	}

	m.findPath(0);

	for (int ii = 0; ii < m.WIDTH * m.HEIGHT; ii++)
	{
		char str[10];
		sprintf(str, "%i", m.m_dataDijkstra[ii].distance);

		API::setText(ii % m.WIDTH, ii / m.HEIGHT, str);

	}

	while (true)
	{

		if (API::wallLeft())
		{

		}
		if (!API::wallLeft())
		{
			API::turnLeft();
		}
		while (API::wallFront())
		{
			API::turnRight();
		}
		API::moveForward();
	}
}
