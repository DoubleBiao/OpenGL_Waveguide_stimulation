#include"Axis.h"

int __axis__indices[3][2]= 
{
	{0,1},
	{2,3},
	{4,5},
};

axis::axis()
{
	_part = new globject_part[3];
	_partnum = 3;
	for(int i = 0;i < _partnum; i++)
	{
		_part[i].assign_index(__axis__indices[i], 3);
	}
	_part[0]._color = glm::vec3(1.0f, 0.0f, 0.0f);
	_part[1]._color = glm::vec3(0.0f, 1.0f, 0.0f);
	_part[2]._color = glm::vec3(0.0f, 0.0f, 1.0f);
}

axis::axis(glm::vec3 ver[], int vertexnum)
{
	_vertices = NULL;
	set_vex(ver, vertexnum);

	_part = new globject_part[3];
	_partnum = 3;
	for(int i = 0;i < _partnum; i++)
	{
		_part[i]._indices_num = 2;
		_part[i].assign_index(__axis__indices[i], 2);
	}

	_part[0]._color = glm::vec3(1.0f, 0.0f, 0.0f);
	_part[1]._color = glm::vec3(0.0f, 1.0f, 0.0f);
	_part[2]._color = glm::vec3(0.0f, 0.0f, 1.0f);
}