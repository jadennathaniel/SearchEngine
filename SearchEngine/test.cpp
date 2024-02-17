#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "AvlTree.h"
#include <unordered_map>
// add includes

TEST_CASE("Check that AVLTree works", "[AVLTree]")
{
    AvlTree<string, unordered_map<string, int>> tree;
    REQUIRE(tree.isEmpty() == true);

    tree.insert("hello");
    tree.insert("world");
    tree.insert("foo");
    tree.insert("chicken");
    tree.insert("dog");
    tree["dog"]["23243256"] = 2;

    REQUIRE(tree.isEmpty() == false);
    REQUIRE(tree.contains("hello") == true);
    REQUIRE(tree.contains("world") == true);
    REQUIRE(tree.contains("foo") == true);
    REQUIRE(tree.contains("chicken") == true);
    REQUIRE(tree.contains("dog") == true);
    REQUIRE(tree["dog"]["23243256"] == 2);
    REQUIRE(tree.contains("cat") == false);
    tree.remove("chicken");
    REQUIRE(tree.contains("chicken") == false);
    AvlTree<string, unordered_map<string, int>> treeCopy;
    treeCopy = tree;
    REQUIRE(treeCopy.contains("hello") == true);
    REQUIRE(treeCopy.contains("world") == true);
    REQUIRE(treeCopy.contains("foo") == true);
    REQUIRE(treeCopy.contains("dog") == true);
    REQUIRE(treeCopy["dog"]["23243256"] == 2);
    REQUIRE(treeCopy.contains("cat") == false);
    treeCopy.makeEmpty();

    bool errorFound = false;
    try{
        treeCopy.getValues("hello");
    }
    catch(const runtime_error& e){
        errorFound = true;
    }
    REQUIRE(errorFound);
}
