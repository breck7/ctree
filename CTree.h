//
// Created by byunits on 2/26/19.
//

#include <string>
#include <regex>
#include <cstring>

#ifndef CTREE_CTREE_H
#define CTREE_CTREE_H

class ImmutableCTree {

private:
    void _parseString(std::string content);

protected:
    ImmutableCTree* _parent;
    //std::string _children;
    std::string _line;
    bool _hasIndex = false;
    void _makeIndex();
    std::map<std::string, int> _index;
    std::vector<ImmutableCTree*> _children;
    int _setChildren(std::string children);
    void _setLine(std::string line);
    void _setParent(ImmutableCTree* parent);
    int _getIndentCount(std::string str);
    std::map<std::string, int> _getIndex();
    std::regex getYIRegex();
    std::string _childrenToString(int indentCount = 0);
    ImmutableCTree * _createNode(std::string line);
    ImmutableCTree * _getNodeByPath(std::string keywordPath);

public:
    ImmutableCTree();
    ImmutableCTree(std::string children, std::string line = "", ImmutableCTree* parent = NULL);
    bool isRoot();
    int getLength();
    std::string getLine();
    std::string getContent();
    std::string get(std::string query);
    std::string getKeyword();
    std::string toString(int indentCount = 0);
    ImmutableCTree * nodeAt(int index);
    ImmutableCTree * getNode(std::string keywordPath);
    ImmutableCTree * getParent();
    int indexOfLast(std::string query);
};

class CTree : public ImmutableCTree {

protected:

public:
    CTree(std::string children, std::string line = "", ImmutableCTree* parent = NULL);
    CTree();
    CTree& setLine(std::string line);
};



#endif //CTREE_CTREE_H
