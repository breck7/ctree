//
// Created by byunits on 2/26/19.
//

#include "CTree.h"
#include <string>
#include <cstring>
#include <iostream>
#include <regex>


ImmutableCTree::ImmutableCTree(std::string children, std::string line, ImmutableCTree* parent)
{
    _setChildren(children);
    _setParent(parent);
    _setLine(line);
}

ImmutableCTree::ImmutableCTree() {}

int ImmutableCTree::_setChildren(std::string children)
{
    if (children == "")
        return 0;


    this->_parseString(children);
    return 0;
}

std::regex ImmutableCTree::getYIRegex() {
    std::regex pat("\n");
    return pat;
}

int ImmutableCTree::_getIndentCount(std::string str) {
    auto level = 0;
    const char edgeChar = ' '; // this.getXI()
    while (str[level] == edgeChar) {
        level++;
    }
    return level;
}

//void ImmutableCTree::getNodeConstructor(std::string line) {
//    return ImmutableCTree;
//}

void ImmutableCTree::_parseString(std::string str) {

    if (str == "") return;
    std::stack<ImmutableCTree *> parentStack;
    int currentIndentCount = -1;
    ImmutableCTree *lastNode = this;

    //const lines = str.split(this.getYIRegex())
    std::istringstream stream(str);
    std::string line;
    while (std::getline(stream, line)) {
        int indentCount = this->_getIndentCount(line);
        if (indentCount > currentIndentCount) {
            currentIndentCount++;
            parentStack.push(lastNode);
        } else if (indentCount < currentIndentCount) {
            // pop things off stack
            while (indentCount < currentIndentCount) {
                parentStack.pop();
                currentIndentCount--;
            }
        }
        auto lineContent = line.substr(currentIndentCount);
        auto parent = parentStack.top();
        lastNode = parent->_createNode(lineContent);
        parent->_children.push_back(lastNode);
    }

    return;

}

ImmutableCTree * ImmutableCTree::_createNode(std::string line) {
    // Todo: should return a variable node type. This is getNodeConstructor in jtree
    return new ImmutableCTree("", line, this);
}

void ImmutableCTree::_setLine(std::string line)
{
    _line = line;
}

void ImmutableCTree::_setParent(ImmutableCTree* parent)
{
    _parent = parent;
}

bool ImmutableCTree::isRoot()
{
    if (_parent)
        return false;
    return true;
}

int ImmutableCTree::getLength()
{
    return _children.size();
}

std::string ImmutableCTree::getLine(){
    return _line;
}

std::string ImmutableCTree::get(std::string query){
    auto node = this->_getNodeByPath(query);
    if (node)
        return node->getContent();
    return ""; // I am differing from the current standard of returning undefined here.
}

std::map<std::string, int> ImmutableCTree::_getIndex() {
    if (!_hasIndex)
        this->_makeIndex();
    return _index;
}

void ImmutableCTree::_makeIndex() {
    for (int index = 0; index < this->getLength(); index++) {
        _index[_children[index]->getKeyword()] = index;
    }
     std::cout << "made index";
    _hasIndex = true;
}

int ImmutableCTree::indexOfLast(std::string keyword) {
    auto index = this->_getIndex();
    auto iter = index.find(keyword);
    if (iter != index.end())
        return iter->second;
     else
        return -1;

}

ImmutableCTree * ImmutableCTree::_getNodeByPath(std::string keywordPath) {
    auto XI = ' ';
    int XI_LENGTH = 1;
    int nextSep = keywordPath.find(XI);

    if (nextSep == -1) {
        int index = this->indexOfLast(keywordPath);
        if (index > -1)
            return _children[index];
        return NULL;
    }

    std::string current = keywordPath.substr(0, nextSep);
    int currentNode = this->indexOfLast(current);
    if (currentNode == -1)
        return  NULL;

    return _children[currentNode]->_getNodeByPath(keywordPath.substr(nextSep + XI_LENGTH));
}

std::string ImmutableCTree::getKeyword(){
    auto ZI = ' ';
    return _line.substr(0, _line.find(ZI));
}

std::string ImmutableCTree::getContent(){
    auto ZI = ' ';
    return _line.substr(_line.find(ZI) + 1);
}

ImmutableCTree * ImmutableCTree::nodeAt(int index){
    return _children[index];
}

ImmutableCTree * ImmutableCTree::getNode(std::string keywordPath){
    return this->_getNodeByPath(keywordPath);
}

ImmutableCTree * ImmutableCTree::getParent(){
    return _parent;
}

std::string ImmutableCTree::toString(int indentCount)
{
    if (this->isRoot())
        return this->_childrenToString(indentCount);
    auto xi = ' ';
    auto YI = '\n';
    auto content = std::string(indentCount, xi) + this->getLine();
    auto value = content + (this->getLength() ? YI + this->_childrenToString(indentCount + 1) : "");
    return value;
}

std::string ImmutableCTree::_childrenToString(int indentCount) {
    std::string value = "";
    std::string YI = "";
    for (int index =0; index < _children.size(); index++) {
        value = value + YI + _children[index]->toString(indentCount);
        YI = "\n";
    }
    return value;
}

CTree::CTree(std::string children, std::string line, ImmutableCTree* parent) : ImmutableCTree(children, line, parent) {}

CTree::CTree() : ImmutableCTree() {}

CTree& CTree::setLine(std::string line) {
    _setLine(line);
return *this;
}
