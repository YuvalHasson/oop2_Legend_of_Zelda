
#include "Map.h"

Map::Map()
{
	setDict(m_dict);
}

std::vector<std::string> Map::getDict() const
{
	return m_dict;
}

void Map::setDict(std::vector<std::string>& dict)
{
	dict.resize(1000);
	dict[264] = { "wall" };
	dict[265] = { "wall" };
	dict[267] = { "wall" };
	dict[268] = { "wall" };
	dict[269] = { "wall" };
	dict[270] = { "wall" };
	dict[274] = { "wall" };
	dict[275] = { "wall" };
	dict[288] = { "wall" };
	dict[290] = { "wall" };
	dict[291] = { "wall" };
	dict[292] = { "wall" };
	dict[293] = { "wall" };
	dict[312] = { "wall" };
	dict[313] = { "wall" };
	dict[339] = { "wall" };
	dict[340] = { "wall" };
	dict[253] = { "flowers" };
	dict[229] = { "flowers" };
	dict[152] = { "tree" };
	dict[153] = { "tree" };
	dict[154] = { "tree" };
	dict[176] = { "tree" };
	dict[177] = { "tree" };
	dict[200] = { "tree" };
	dict[201] = { "tree" };
	dict[130] = { "tree" };
	dict[131] = { "tree" };
	dict[155] = { "tree" };
	dict[225] = { "tree" };
	dict[249] = { "tree" };
	dict[49] = { "house" };
	dict[60] = { "house" };
	dict[61] = { "house" };
	dict[62] = { "house" };
	dict[9] = { "house" };
	dict[10] = { "house" };
	dict[11] = { "house" };
	dict[33] = { "house" };
	dict[34] = { "house" };
	dict[35] = { "house" };
	dict[48] = { "house" };
	dict[476] = { "sea" };
	dict[477] = { "sea" };
	dict[479] = { "sea" };
}
