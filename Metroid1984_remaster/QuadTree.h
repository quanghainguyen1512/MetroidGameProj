#ifndef QUADTREE_H
#define QUADTREE_H

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

class QuadTree
{
public:
	QuadTree(int x, int y, int width, int height, int level, int index);
	~ QuadTree();

	void Initialize(string filepath);
	void Import(string source);
	void Load(vector<int> &listOut, int CamX, int CamY, int CamWidth, int CamHeight);
	void addToNode(int index, string value);

	int getValue();
	void getList(vector<int> &v);

private:
	QuadTree* node0;
	QuadTree* node1;
	QuadTree* node2;
	QuadTree* node3;
	int _x;
	int _y;
	int _width;
	int _height;
	int _level;
	int _index;
	int value;
	vector<int> list;
	bool Is_parent;

};
#endif // QUADTREE_H
