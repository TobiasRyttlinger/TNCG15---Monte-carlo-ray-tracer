#pragma once
#include "Ray.h"
#include "Scene.h"
struct Node {

	Node(Node* parentIn, Ray rayIn, Scene* scene){
		parent = parentIn;
		ray = rayIn;
		//scene->(ray);
	}

	Node createNewNodes(Node* currentNode, int depth) {



	}

	Node createRayTree(Ray& ray) {
		Node root = Node(nullptr, ray, scene);
		Node* next = &root;

		createNewNodes(&root, 0);

		return root;
	}
	Scene* scene;
	Node* parent;
	Ray ray;


};