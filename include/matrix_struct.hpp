#ifndef MATRIX_STRUCT
#define MATRIX_STRUCT
#include <vector>
#include <unordered_map>

typedef std::vector<long> lvec;
typedef std::unordered_map<long, lvec> mapoflvec;
typedef std::vector<lvec> matrixtype;
typedef std::unordered_map<long, mapoflvec> matrixmap;

struct MatrixData
{
     matrixtype matrix;
     matrixmap matrixMap;
};
#endif