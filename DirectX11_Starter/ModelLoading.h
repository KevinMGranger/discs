#pragma once

#include <tuple>
#include <vector>
#include <d3d11.h>
#include "Vertex.h"

std::pair<std::vector<Vertex>, std::vector<UINT>> LoadModel(char *filename);