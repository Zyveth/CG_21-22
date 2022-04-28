#include <stdio.h>
#include <string.h>

#include "headers/Sphere.h"
#include "headers/Box.h"
#include "headers/Cone.h"
#include "headers/Plane.h"
#include "headers/Bezier.h"

using namespace std;

int main(int argc, char **argv) 
{
	if(argc > 7 || argc < 5)
	{
		printf("Invalid number of arguments: %d.\n", argc);
		exit(0);
	}

	if(strcmp(argv[1], "sphere") == 0)
	{
		if(argc - 2 != 4)
		{
			printf("Invalid number of arguments for sphere: %d.\n", argc - 2);
			exit(0);
		}

		float radius = strtof(argv[2], NULL);
		int slices = strtol(argv[3], NULL, 10);
		int stacks = strtol(argv[4], NULL, 10);

		if(radius < 0)
		{
			printf("Invalid argument for radius: %f.\n", radius);
			exit(0);
		}

		if(slices < 0)
		{
			printf("Invalid argument for slices: %d.\n", slices);
			exit(0);
		}

		if(stacks < 0)
		{
			printf("Invalid argument for stacks: %d.\n", stacks);
			exit(0);
		}

		char* init_path = "generated/";
		char* path = (char*) malloc(sizeof(char) * (strlen(argv[5]) + strlen(init_path)));
		strcpy(path, init_path);
		strncat(path, argv[5], strlen(argv[5]));

		Sphere s;

		printf("Generating vertices...\n");

		s.generatevertices(radius, slices, stacks);

		printf("Vertices generated.\n\nSaving vertices in \'%s\'...\n", path);

		s.serialize(path);

		printf("Vertices saved in \'%s\'.\n", path);

		free(path);
	}
	else if(strcmp(argv[1], "box") == 0)
	{
		if(argc - 2 != 3)
		{
			printf("Invalid number of arguments for box: %d.\n", argc - 2);
			exit(0);
		}

		float units = strtof(argv[2], NULL);
		int divisions = strtol(argv[3], NULL, 10);

		if(units < 0)
		{
			printf("Invalid argument for units: %f.\n", units);
			exit(0);
		}

		if(divisions < 0)
		{
			printf("Invalid argument for divisions: %d.\n", divisions);
			exit(0);
		}

		char* init_path = "generated/";
		char* path = (char*) malloc(sizeof(char) * (strlen(argv[4]) + strlen(init_path)));
		strcpy(path, init_path);
		strncat(path, argv[4], strlen(argv[4]));

		Box b;

		printf("Generating vertices...\n");

		b.generateVertices(units, divisions);

		printf("Vertices generated.\n\nSaving vertices in \'%s\'...\n", path);

		b.serialize(path);

		printf("Vertices saved in \'%s\'.\n", path);

		free(path);
	}
	else if(strcmp(argv[1], "cone") == 0)
	{
		if(argc - 2 != 5)
		{
			printf("Invalid number of arguments for cone: %d.\n", argc - 2);
			exit(0);
		}

		float radius = strtof(argv[2], NULL);
		float height = strtof(argv[3], NULL);
		int slices = strtol(argv[4], NULL, 10);
		int stacks = strtol(argv[5], NULL, 10);

		if(radius < 0)
		{
			printf("Invalid argument for radius: %f.\n", radius);
			exit(0);
		}

		if(height < 0)
		{
			printf("Invalid argument for height: %f.\n", height);
			exit(0);
		}

		if(slices < 0)
		{
			printf("Invalid argument for slices: %d.\n", slices);
			exit(0);
		}

		if(stacks < 0)
		{
			printf("Invalid argument for stacks: %d.\n", stacks);
			exit(0);
		}

		char* init_path = "generated/";
		char* path = (char*) malloc(sizeof(char) * (strlen(argv[6]) + strlen(init_path)));
		strcpy(path, init_path);
		strncat(path, argv[6], strlen(argv[6]));

		Cone c;

		printf("Generating vertices...\n");

		c.generateVertices(radius, height, slices, stacks);

		printf("Vertices generated.\n\nSaving vertices in \'%s\'...\n", path);

		c.serialize(path);

		printf("Vertices saved in \'%s\'.\n", path);

		free(path);
	}
	else if(strcmp(argv[1], "plane") == 0)
	{
		if(argc - 2 != 3)
		{
			printf("Invalid number of arguments for plane: %d.\n", argc - 2);
			exit(0);
		}

		float units = strtof(argv[2], NULL);
		int divisions = strtol(argv[3], NULL, 10);

		if(units < 0)
		{
			printf("Invalid argument for units: %f.\n", units);
			exit(0);
		}

		if(divisions < 0)
		{
			printf("Invalid argument for divisions: %d.\n", divisions);
			exit(0);
		}

		char* init_path = "generated/";
		char* path = (char*) malloc(sizeof(char) * (strlen(argv[4]) + strlen(init_path)));
		strcpy(path, init_path);
		strncat(path, argv[4], strlen(argv[4]));

		Plane p;

		printf("Generating vertices...\n");

		p.generateVertices(units, divisions);

		printf("Vertices generated.\n\nSaving vertices in \'%s\'...\n", path);

		p.serialize(path);

		printf("Vertices saved in \'%s\'.\n", path);

		free(path);
	}
	else if(strcmp(argv[1], "bezier") == 0)
	{
		if(argc - 2 != 3)
		{
			printf("Invalid number of arguments for bezier: %d.\n", argc - 2);
			exit(0);
		}

		char* input_file = (char*) malloc(sizeof(char) * (strlen(argv[2])));
		strcpy(input_file, argv[2]);

		int tessellation = strtol(argv[3], NULL, 10);

		if(tessellation < 0)
		{
			printf("Invalid argument for tessellation: %d.\n", tessellation);
			exit(0);
		}

		char* init_path = "generated/";
		char* path = (char*) malloc(sizeof(char) * (strlen(argv[4]) + strlen(init_path)));
		strcpy(path, init_path);
		strncat(path, argv[4], strlen(argv[4]));

		Bezier b;

		printf("Generating vertices...\n");

		b.parseBezier(input_file);
		b.bezierPoints(tessellation);

		printf("Vertices generated.\n\nSaving vertices in \'%s\'...\n", path);

		b.serialize(path);

		printf("Vertices saved in \'%s\'.\n", path);

		free(path);
	}
	else
	{
		printf("\n\nInvalid argument for shape: %s.", argv[1]);
		exit(0);
	}
	
	return 1;
}