#include"Axis.h"

int __axis__indices[3][5]= 
{
	{1,0,6, 7, 0},
	{3,2,8, 9, 2},
	{5,4,10,11,4},
};

axis::axis()
{
	_part = new globject_part[3];
	_partnum = 3;
	for(int i = 0;i < _partnum; i++)
	{
		_part[i]._indices_num = 5;
		_part[i].assign_index(__axis__indices[i], 5);
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
		_part[i]._indices_num = 5;
		_part[i].assign_index(__axis__indices[i], 5);
	}

	_part[0]._color = glm::vec3(1.0f, 0.0f, 0.0f);
	_part[1]._color = glm::vec3(0.0f, 1.0f, 0.0f);
	_part[2]._color = glm::vec3(0.0f, 0.0f, 1.0f);
}