#include "Triangle.h"
#include <glm/glm.hpp>


Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	pos[0] = p1;
	pos[1] = p2;
	pos[2] = p3;

}

class Triangle {
public:
	Triangle();
	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {


	}

private:
	glm::vec3 pos[3];
};