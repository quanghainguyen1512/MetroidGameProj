#include"QuadTree.h"

using namespace std;

QuadTree::QuadTree(int x, int y, int width, int height, int level, int index)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_level = level;
	_index = index;
	Is_parent = true;
	node0 = NULL;
	node1 = NULL;
	node2 = NULL;
	node3 = NULL;
	value = -1;
}

void QuadTree::Initialize(string filepath)
{
	ifstream file_txt(filepath);
	string str;
	string fileContent;
	while (getline(file_txt, str))
	{
		string result = str.erase(0, 2);
		Import(result);
	}
}

void QuadTree::Import(string str)
{
	char a[1024];
	strncpy(a, str.c_str(), sizeof(a));
	a[sizeof(a) - 1] = 0;
	int level = _level;
	int node = int(a[0]) - 48;
	if (a[1] == '-')
	{
		string result = str.erase(0, 2);
		
		addToNode(int(a[0]) - 48, result);
	}
	else if (a[1] == ']')
	{
		list.push_back(int(a[0]) - 48);
	}
	else if (a[1] == '}')
	{
		value = int(a[0]) - 48;
		Is_parent = false;
	}
	else if (a[1] != '}'&&a[1] != ']')
	{
		int i = 0;
		int number = 0;
		while (48<=int(a[i])&&int(a[i])<=57)
		{
			number = number * 10 + (int(a[i]) - 48);
			i++;
		}
		if (a[i] == ']')
		{
			list.push_back(number);
		}
		else if (a[i] == '}')
		{
			value = number;
			Is_parent = false;
		}
	}
}

void QuadTree::addToNode(int index, string value)
{
	switch (index)
	{
	case 0:
	{
		if (node0 == NULL)
		{
			node0 = new QuadTree(_x, _y, _width / 2, _height / 2, _level + 1, 0);
			if (node0 == NULL)
				return;
			else
			{
				Is_parent = true;
				node0->Import(value);
			}
		}
		else
		{
			node0->Import(value);
		}
		break;
	}
	case 1:
	{
		if (node1 == NULL)
		{
			node1 = new QuadTree(_x + _width / 2, _y, _width / 2, _height / 2, _level + 1, 1);
			if (node1 == NULL)
				return;
			else
			{
				Is_parent = true;
				node1->Import(value);
			}
		}
		else
		{
			node1->Import(value);
		}
		break;
	}
	case 2:
	{
		if (node2 == NULL)
		{
			node2 = new QuadTree(_x + _width / 2, _y + _height / 2, _width / 2, _height / 2, _level + 1, 2);
			if (node2 == NULL)
				return;
			else
			{
				Is_parent = true;
				node2->Import(value);
			}
		}
		else
		{
			node2->Import(value);
		}
		break;
	}
	case 3:
	{
		if (node3 == NULL)
		{
			node3 = new QuadTree(_x, _y + _height / 2, _width / 2, _height / 2, _level + 1, 3);
			if (node3 == NULL)
				return;
			else
			{	
				Is_parent = true;
				node3->Import(value);
			}
		}
		else
		{
			node3->Import(value);
		}
		break;
	}
	default:
		break;
	}
}

void QuadTree::Load(vector<int> &listOut, int CamX, int CamY, int CamWidth, int CamHeight)
{
	if (Is_parent == true || value == -1)
	{
		bool left_right = (CamX < (_x + _width / 2) && (_x + _width / 2) < CamX + CamWidth);
		bool up_down = (CamY < (_y + _height / 2) && (_y + _height / 2) < CamY + CamHeight);
		bool node0_node1 = (_y <= CamY && (CamY + CamHeight) <= (_y + _height / 2));
		bool node1_node2 = ((_x + _width / 2) <= CamX && (CamX + CamWidth) <= (_x + _width));
		bool node2_node3 = ((_y + _height / 2) <= CamY && (CamY + CamHeight) <= (_y + _height));
		bool node3_node0 = (_x <= CamX && (CamX + CamWidth) <= (_x + _width / 2));

		if (left_right == true && up_down == true)
		{
			if (node0)
				node0->Load(listOut, CamX, CamY, (_x + _width / 2 - CamX), (_y + (_height / 2) - CamHeight));
			if (node1)
				node1->Load(listOut, _x + _width / 2, CamY, (CamX + CamWidth) - (_x + _width / 2), _y + _height / 2 - CamY);
			if (node2)
				node2->Load(listOut, _x + _width / 2, _y + _height / 2, (CamX + CamWidth) - (_x + _width / 2), (CamY + CamHeight) - (_y + _height / 2));
			if (node3)
				node3->Load(listOut, CamX, _y + _height / 2, (_x + _width / 2) - CamX, (CamY + CamHeight) - (_y + _height / 2));
		}
		else if (left_right == true)
		{
			if (node0_node1 == true)
			{
				if (node0)
					node0->Load(listOut, CamX, CamY, (_x + _width / 2) - CamX, CamHeight);
				if (node1)
					node1->Load(listOut, (_x + _width / 2), CamY, (CamX + CamWidth) - (_x + _width / 2), CamHeight);
			}
			else if (node2_node3 == true)
			{
				if (node2)
					node2->Load(listOut, CamX, CamY, (_x + _width / 2) - CamX, CamHeight);
				if (node3)
					node3->Load(listOut, (_x + _width / 2), CamY, (CamX + CamWidth) - (_x + _width / 2), CamHeight);
			}
		}
		else if (up_down == true)
		{
			if (node1_node2 == true)
			{
				if (node1)
					node1->Load(listOut, CamX, CamY, CamWidth, (_y + _height / 2) - CamY);
				if (node2)
					node2->Load(listOut, CamX, _y + _height / 2, CamWidth, (CamY + CamHeight) - (_y + _height / 2));
			}
			else if (node3_node0 == true)
			{
				if (node0)
					node0->Load(listOut, CamX, CamY, CamWidth, (_y + _height / 2) - CamY);
				if (node3)
					node3->Load(listOut, CamX, _y + _height / 2, CamWidth, (CamY + CamHeight) - (_y + _height / 2));
			}
		}
		else if (node0_node1 == true && node3_node0 == true)
		{
			if (node0)
				node0->Load(listOut, CamX, CamY, CamWidth, CamHeight);
		}
		else if (node1_node2 == true && node2_node3 == true)
		{
			if (node2)
				node2->Load(listOut, CamX, CamY, CamWidth, CamHeight);
		}
		else if (node2_node3 == true && node3_node0 == true)
		{
			if (node3)
				node3->Load(listOut, CamX, CamY, CamWidth, CamHeight);
		}
		else if (node0_node1 == true && node1_node2 == true)
		{
			if (node1)
				node1->Load(listOut, CamX, CamY, CamWidth, CamHeight);
		}

		if ((_x < CamX && (_x + _width) < (CamX + CamWidth)) &&
			(_y < CamY && (_y + _height) < (CamY + CamHeight)))
			getList(listOut);

		for (int i = 0; i < list.size(); i++)
		{
			listOut.push_back(list[i]);
		}
	}
	else
	{
		listOut.push_back(value);
	}
}

int QuadTree::getValue()
{
	return value;
}
void QuadTree::getList(vector<int> &v)
{
	if (Is_parent == true || value == -1)
	{
		for (int i = 0; i < list.size(); i++)
		{
			v.push_back(list[i]);
		}

		if (node0)
			node0->getList(v);
		if (node1)
			node1->getList(v);
		if (node2)
			node2->getList(v);
		if (node3)
			node3->getList(v);
	}
	else
	{
		v.push_back(value);
	}
}

QuadTree::~QuadTree()
{
	if (node0)
	{
		delete node0;
		node0 = nullptr;
	}
	if (node1)
	{
		delete node0;
		node0 = nullptr;
	}
	if (node2)
	{
		delete node0;
		node0 = nullptr;
	}
	if (node3)
	{
		delete node0;
		node0 = nullptr;
	}
}