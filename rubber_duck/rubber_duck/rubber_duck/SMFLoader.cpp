#include "SMFLoader.h"
#include <iostream>
#include <fstream>

using namespace std;

SMFLoader::SMFLoader()
{
	vertex = NULL;
	face = NULL;
	color = NULL;
	normal = NULL;

	vertexSize = 0;
	faceSize = 0;
	colorSize = 0;
	normalSize = 0;
}

void SMFLoader::load(char* filename)
{
	ifstream fin;
	int vertexCnt = 0;
	int faceCnt = 0;
	int colorCnt = 0;
	int normalCnt = 0;
	char temp[256];
	char choice;

	clear();

	fin.open(filename, ios::in);

	if (!fin)
	{
		cout << "can't open file" << endl;
		return;
	}

	vertexSize = 1024;
	faceSize = 1024;
	colorSize = 1024;

	vertex = new float[vertexSize * 3];
	face = new int[faceSize * 3];
	color = new float[colorSize * 3];
	normal = new float[normalSize * 3];

	while (!fin.eof())
	{
		//fin >> temp;
		//cout << temp << endl;
		//choice = fin.get();
		//cout << choice <<endl;
		//while()
		choice = fin.get();
		while (choice == '\n' || choice == '\t' || choice == ' ')
			choice = fin.get();
		switch (choice)
		{
		case 'v':
			fin >> vertex[vertexCnt * 3];
			fin >> vertex[vertexCnt * 3 + 1];
			fin >> vertex[vertexCnt * 3 + 2];
			vertexCnt++;

			if (vertexCnt >= vertexSize)
			{
				float* tmp = vertex;
				vertex = new float[vertexSize * 3 * 4];
				memcpy(vertex, tmp, sizeof(float) * vertexCnt * 3);
				vertexSize = vertexSize * 4;
				delete tmp;
			}
			break;

		case 'f':
			fin >> face[faceCnt * 3];
			fin >> face[faceCnt * 3 + 1];
			fin >> face[faceCnt * 3 + 2];

			faceCnt++;
			if (faceCnt >= faceSize)
			{
				int* tmp = face;
				face = new int[faceSize * 3 * 4];
				memcpy(face, tmp, sizeof(int) * faceCnt * 3);
				faceSize = faceSize * 4;
				delete tmp;
			}
			break;

		case 'c':
			fin >> color[colorCnt * 3];
			fin >> color[colorCnt * 3 + 1];
			fin >> color[colorCnt * 3 + 2];

			colorCnt++;
			if (colorCnt >= colorSize)
			{
				float* tmp = color;
				color = new float[colorSize * 3 * 4];
				memcpy(color, tmp, sizeof(float) * colorCnt * 3);
				colorSize = colorSize * 4;
				delete tmp;
			}
			break;
			/*
			case 'n':
				fin >> normal[normalCnt * 3];
				fin >> normal[normalCnt * 3 + 1];
				fin >> normal[normalCnt * 3 + 2];

				normalCnt++;
				if (normalCnt >= normalSize)
				{
					float* tmp = normal;
					normal = new float[normalSize * 3 * 4];
					memcpy(normal, tmp, sizeof(float) * normalCnt * 3);
					normalSize = normalSize * 4;
					delete tmp;
				}
				break;
			*/
		default:
			fin.getline(temp, 256);
			cout << temp << endl;
		}
	}

	float* tmpf = vertex;
	vertex = new float[vertexCnt * 3];
	memcpy(vertex, tmpf, sizeof(float) * vertexCnt * 3);
	vertexSize = vertexCnt;
	delete tmpf;

	int* tmpi = face;
	face = new int[faceCnt * 3];
	memcpy(face, tmpi, sizeof(int) * faceCnt * 3);
	faceSize = faceCnt;
	delete tmpi;

	float* tmpc = color;
	color = new float[colorCnt * 3];
	memcpy(color, tmpc, sizeof(float) * colorCnt * 3);
	colorSize = colorCnt;
	delete tmpc;

	float* tmpn = normal;
	normal = new float[normalCnt * 3];
	memcpy(normal, tmpn, sizeof(float) * normalCnt * 3);
	normalSize = normalCnt;
	delete tmpn;

	fin.close();
}

void SMFLoader::clear()
{
	if (vertex)
	{
		delete vertex;
		vertex = NULL;
	}
	if (face)
	{
		delete face;
		face = NULL;
	}
	if (color)
	{
		delete color;
		color = NULL;
	}
	if (normal)
	{
		delete normal;
		normal = NULL;
	}
}

float* SMFLoader::getVertices()
{
	return vertex;
}

int* SMFLoader::getFaces()
{
	return face;
}

float* SMFLoader::getColors()
{
	return color;
}

float* SMFLoader::getNormals()
{
	return normal;
}

float* SMFLoader::getFace(int index)
{
	float* tmp;

	if (index >= faceSize)
		return NULL;

	tmp = new float[9];

	int v = face[index * 3] - 1;

	tmp[0] = vertex[v * 3];
	tmp[1] = vertex[v * 3 + 1];
	tmp[2] = vertex[v * 3 + 2];

	v = face[index * 3 + 1] - 1;
	tmp[3] = vertex[v * 3];
	tmp[4] = vertex[v * 3 + 1];
	tmp[5] = vertex[v * 3 + 2];

	v = face[index * 3 + 2] - 1;
	tmp[6] = vertex[v * 3];
	tmp[7] = vertex[v * 3 + 1];
	tmp[8] = vertex[v * 3 + 2];

	return tmp;
}

float* SMFLoader::getFaceColor(int index)
{
	float* tmp;

	if (colorSize != vertexSize)
	{
		cout << "color size != vertex size." << endl;
		return NULL;
	}

	if (index >= faceSize)
		return NULL;

	tmp = new float[9];

	int v = face[index * 3] - 1;

	tmp[0] = color[v * 3];
	tmp[1] = color[v * 3 + 1];
	tmp[2] = color[v * 3 + 2];

	v = face[index * 3 + 1] - 1;
	tmp[3] = color[v * 3];
	tmp[4] = color[v * 3 + 1];
	tmp[5] = color[v * 3 + 2];

	v = face[index * 3 + 2] - 1;
	tmp[6] = color[v * 3];
	tmp[7] = color[v * 3 + 1];
	tmp[8] = color[v * 3 + 2];

	return tmp;
}

float* SMFLoader::getFaceNormal(int index)
{
	float* tmp;

	if (normalSize != vertexSize)
	{
		cout << "normal size != vertex size." << endl;
		return NULL;
	}

	if (index >= faceSize)
		return NULL;

	tmp = new float[9];

	int v = face[index * 3] - 1;

	tmp[0] = normal[v * 3];
	tmp[1] = normal[v * 3 + 1];
	tmp[2] = normal[v * 3 + 2];

	v = face[index * 3 + 1] - 1;
	tmp[3] = normal[v * 3];
	tmp[4] = normal[v * 3 + 1];
	tmp[5] = normal[v * 3 + 2];

	v = face[index * 3 + 2] - 1;
	tmp[6] = normal[v * 3];
	tmp[7] = normal[v * 3 + 1];
	tmp[8] = normal[v * 3 + 2];

	return tmp;
}

int SMFLoader::getVertexSize()
{
	return vertexSize;
}

int SMFLoader::getFaceSize()
{
	return faceSize;
}

int SMFLoader::getColorSize()
{
	return colorSize;
}

int SMFLoader::getNormalSize()
{
	return normalSize;
}