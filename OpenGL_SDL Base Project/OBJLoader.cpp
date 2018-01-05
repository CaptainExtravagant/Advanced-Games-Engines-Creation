#include "OBJLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

OBJLoader::OBJLoader()
{

}

OBJLoader::~OBJLoader()
{

}

long OBJLoader::FileLength(int f)
{
	struct stat buf;

	fstat(f, &buf);

	return(buf.st_size);
}

bool OBJLoader::LoadOBJ(const char* path, obj_type_ptr p_object)
{

	int vertices = 0;
	int normals = 0;
	int uvs = 0;
	int polygons = 0;
	int i = 0;
	FILE *inFile; //File pointer

	inFile = fopen(path, "r");
	if (inFile == NULL)
	{
		printf("Unable to open file");
		return false;
	}

	while (1)
	{
		char lineHeader[128];

		int res = fscanf(inFile, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			Vector3D vertex;
			fscanf(inFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			p_object->vertex[vertices] = vertex;
			vertices++;
		}
		else if(strcmp(lineHeader, "vt") == 0)
		{
			TexCoord uv;
			fscanf(inFile, "%f %f\n", &uv.u, &uv.v);
			p_object->texcoord[uvs] = uv;
			uvs++;
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			Vector3D normal;
			fscanf(inFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			p_object->normal[normals] = normal;
			normals++;
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(inFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
						
			p_object->polygon[polygons].a = vertexIndex[0];
			p_object->polygon[polygons].b = vertexIndex[1];
			p_object->polygon[polygons].c = vertexIndex[2];

			polygons++;
		}
	}

	p_object->vertices_qty = vertices;
	p_object->normals_qty = normals;
	p_object->polygons_qty = polygons;

	fclose(inFile);

	return true;
}