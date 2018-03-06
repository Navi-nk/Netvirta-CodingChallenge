#ifndef SEARCH_EXE_H
#define SEARCH_EXE_H
#include <vector>
#include <unordered_map>

class SearchExecutor
{
  private:
    std::vector<std::vector<long>> matrix;
    std::unordered_map<long, std::unordered_map<long, std::vector<long>>> matrixMap;
    void preprocessMatrix();

  public:
    bool preprocess(std::vector<std::string>);
};

#endif