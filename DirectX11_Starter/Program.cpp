#include "Program.h"


Program::Program(Mesh *mesh, Material *mat)
	: GameObject(mesh, mat), colliderComp(this, )
{

}


Program::~Program()
{
}
