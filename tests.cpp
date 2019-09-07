//
// Created by byunits on 2/27/19.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "CTree.h"


TEST_CASE( "Basic test" ) {
    auto tree = new CTree("Yo world");
    REQUIRE( tree->toString() == "Yo world" );

    REQUIRE( tree->isRoot() );
    REQUIRE( tree->getNode("Yo")->getLine() == "Yo world" );
}

TEST_CASE( "Blank test" ) {
    CTree *blank = new CTree();
    REQUIRE(blank->toString() == "");
    REQUIRE(blank->get("foo") == "");
}

TEST_CASE( "Children" ) {
    auto text = "hello\n World";
    CTree *tree = new CTree(text);
    REQUIRE(tree->toString() == text);

    REQUIRE(tree->getLength() == 1);
}

TEST_CASE( "Children2" ) {
    auto text = "hello a\n World\nyo fish";
    CTree *tree = new CTree(text);
    REQUIRE(tree->toString() == text);
    REQUIRE(tree->getLength() == 2);

    auto child = tree->nodeAt(1);
    REQUIRE(child->toString() == "yo fish");
    REQUIRE(child->getLength() == 0);
    REQUIRE(child->getParent() == tree);
    REQUIRE(child->getKeyword() == "yo");
    REQUIRE(child->getContent() == "fish");
    REQUIRE(tree->get("hello") == "a");
}


TEST_CASE( "setLine" ) {
    auto text = "hello\n World\nyo";
    CTree *tree = new CTree(text);

    //tree->nodeAt(1)->setLine("foo");
    //REQUIRE(tree->toString() == "hello\n World\nfoo");
}