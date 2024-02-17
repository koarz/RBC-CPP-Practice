#include "binary_search_tree.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(BinarySearchTreeTest, TEST1) {

    rbc::Node<int> left{10, nullptr, nullptr};
    rbc::Node<int> right{10, nullptr, nullptr};
    rbc::Node<int> node{10, &left, &right};
    EXPECT_EQ(node.left, &left);
    EXPECT_EQ(node.right, &right);
}

TEST(BinarySearchTreeTest, TEST2) {

    rbc::Node<int> left{10, nullptr, nullptr};
    rbc::Node<int> right{10, nullptr, nullptr};
    rbc::Node<int> node{10, &left, &right};
    rbc::Node<int> copy{node};
    EXPECT_EQ(copy.value, node.value);
    EXPECT_EQ(copy.left, node.left);
    EXPECT_EQ(copy.right, node.right);
}

TEST(BinarySearchTreeTest, TEST3) {

    rbc::Node<int> default_{};
    EXPECT_EQ(default_.value, 0);
    EXPECT_EQ(default_.left, nullptr);
    EXPECT_EQ(default_.right, nullptr);
}

TEST(BinarySearchTreeTest, TEST4) {

    rbc::Node<int> left{10, nullptr, nullptr};
    rbc::Node<int> right{10, nullptr, nullptr};
    rbc::Node<int> node{10, &left, &right};

    std::cout << "adress of node: " << &node << std::endl;
    std::cout << "adress of left: " << &left << std::endl;
    std::cout << "adress of right: " << &right << std::endl;
    std::cout << std::string(80, '*') << std::endl;
    std::cout << "PRINT A NODE" << std::endl;
    std::cout << node << std::endl;
    std::cout << std::string(80, '*') << std::endl;
}

TEST(BinarySearchTreeTest, TEST5) {
    rbc::Node<int> node{5, nullptr, nullptr};

    EXPECT_TRUE(node > 4);
    EXPECT_FALSE(node > 5);
    EXPECT_TRUE(node >= 5);
    EXPECT_FALSE(node >= 6);
    EXPECT_TRUE(node < 6);
    EXPECT_FALSE(node < 2);
    EXPECT_TRUE(node <= 5);
    EXPECT_FALSE(node <= 2);
    EXPECT_TRUE(node == 5);
    EXPECT_FALSE(node == 3);

    EXPECT_TRUE(4 < node);
    EXPECT_FALSE(5 < node);
    EXPECT_TRUE(5 <= node);
    EXPECT_FALSE(6 <= node);
    EXPECT_TRUE(6 > node);
    EXPECT_FALSE(2 > node);
    EXPECT_TRUE(5 >= node);
    EXPECT_FALSE(2 >= node);
    EXPECT_TRUE(5 == node);
    EXPECT_FALSE(3 == node);

}

TEST(BinarySearchTreeTest, TEST6) {
    rbc::BST<int> bst{};
    EXPECT_EQ(bst.get_root(), nullptr);
}

TEST(BinarySearchTreeTest, TEST7) {
    rbc::BST<int> bst{};
    bst.add_node(10);
    bst.add_node(20);
    bst.add_node(5);
    EXPECT_EQ(bst.get_root()->value, 10);
    EXPECT_EQ(bst.get_root()->left->value, 5);
    EXPECT_EQ(bst.get_root()->right->value, 20);
}

TEST(BinarySearchTreeTest, TEST8) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(53);
    bst.add_node(15);
    bst.add_node(7);

    EXPECT_FALSE(bst.add_node(53));
    EXPECT_EQ(bst.get_root()->left->left->value, 7);
    EXPECT_EQ(bst.get_root()->left->right->value, 15);
    EXPECT_EQ(bst.get_root()->right->right->value, 53);
}

TEST(BinarySearchTreeTest, TEST9) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(53);

    EXPECT_FALSE(bst.add_node(50));

    std::vector<int> values;
    bst.bfs([&values](rbc::Node<int>*& node){values.push_back(node->value);});
    EXPECT_EQ(values.size(), 4);
    EXPECT_TRUE(std::find(values.begin(), values.end(), 25) != values.end());
    EXPECT_TRUE(std::find(values.begin(), values.end(), 10) != values.end());
    EXPECT_TRUE(std::find(values.begin(), values.end(), 50) != values.end());
    EXPECT_TRUE(std::find(values.begin(), values.end(), 53) != values.end());
}

TEST(BinarySearchTreeTest, TEST10) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(53);
    bst.add_node(15);
    bst.add_node(7);

    EXPECT_EQ(bst.length(), 6);
}

TEST(BinarySearchTreeTest, TEST11) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(53);
    bst.add_node(15);
    bst.add_node(7);

    std::cout << "PRINT A BINARY SEARCH TREE" << std::endl;
    std::cout << bst << std::endl;
}

TEST(BinarySearchTreeTest, TEST12) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(53);
    bst.add_node(15);
    bst.add_node(7);

    rbc::Node<int>** node{bst.find_node(10)};
    EXPECT_EQ((*node)->value, 10);
    EXPECT_EQ((*node)->left->value, 7);
    EXPECT_EQ((*node)->right->value, 15);
}

TEST(BinarySearchTreeTest, TEST13) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(53);
    bst.add_node(15);
    bst.add_node(7);

    rbc::Node<int>** node{bst.find_node(11)};
    EXPECT_EQ(node, nullptr);
}

TEST(BinarySearchTreeTest, TEST14) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(53);
    bst.add_node(15);
    bst.add_node(7);

    std::cout << "here" << std::endl;
    rbc::Node<int>** node{bst.find_parrent(15)};
    std::cout << "here2" << std::endl;
    EXPECT_EQ((*node)->value, 10);
    EXPECT_EQ((*node)->left->value, 7);
    EXPECT_EQ((*node)->right->value, 15);
}

TEST(BinarySearchTreeTest, TEST15) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(53);
    bst.add_node(15);
    bst.add_node(7);
    bst.add_node(8);
    bst.add_node(9);

    rbc::Node<int>** node{bst.find_successor(10)};
    EXPECT_EQ((*node)->value, 9);
    EXPECT_EQ((*node)->left, nullptr);
    EXPECT_EQ((*node)->right, nullptr);
}

TEST(BinarySearchTreeTest, TEST16) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(53);
    bst.add_node(15);
    bst.add_node(7);
    bst.add_node(8);
    bst.add_node(9);

    EXPECT_FALSE(bst.delete_node(11));
}

TEST(BinarySearchTreeTest, TEST17) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(53);
    bst.add_node(15);
    bst.add_node(7);
    bst.add_node(8);
    bst.add_node(9);

    EXPECT_EQ(bst.length(), 8);
    EXPECT_TRUE(bst.delete_node(53)); // leaf node
    EXPECT_EQ(bst.length(), 7);
    EXPECT_EQ(bst.get_root()->right->right, nullptr);
}

TEST(BinarySearchTreeTest, TEST18) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(65);
    bst.add_node(60);
    bst.add_node(70);
    bst.add_node(5);
    bst.add_node(2);
    bst.add_node(7);
    bst.add_node(75);

    EXPECT_EQ(bst.length(), 10);
    EXPECT_TRUE(bst.delete_node(10)); // only left child
    EXPECT_EQ(bst.length(), 9);
    EXPECT_EQ(bst.get_root()->left->value, 5);
    EXPECT_EQ(bst.get_root()->left->left->value, 2);
    EXPECT_EQ(bst.get_root()->left->right->value, 7);
    EXPECT_EQ(bst.get_root()->left->right->left, nullptr);
    EXPECT_EQ(bst.get_root()->left->right->right, nullptr);
}

TEST(BinarySearchTreeTest, TEST19) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(65);
    bst.add_node(60);
    bst.add_node(70);
    bst.add_node(5);
    bst.add_node(2);
    bst.add_node(7);
    bst.add_node(75);

    rbc::Node<int>* address_of_5{*bst.find_node(5)};
    rbc::Node<int>* address_of_2{*bst.find_node(2)};

    EXPECT_TRUE(bst.delete_node(10)); // only left child

    // the remainig nodes should not be regenerated
    // => address of remaning nodes before and after deletion should be the same
    // when deleting a node: just reconnect the needed parrents and childs
    EXPECT_EQ(*bst.find_node(5), address_of_5);
    EXPECT_EQ(*bst.find_node(2), address_of_2);

}

TEST(BinarySearchTreeTest, TEST20) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(65);
    bst.add_node(60);
    bst.add_node(70);
    bst.add_node(5);
    bst.add_node(2);
    bst.add_node(7);
    bst.add_node(75);

    EXPECT_EQ(bst.length(), 10);
    EXPECT_TRUE(bst.delete_node(50)); // only right child
    EXPECT_EQ(bst.length(), 9);
    EXPECT_EQ(bst.get_root()->right->value, 65);
    EXPECT_EQ(bst.get_root()->right->right->value, 70);
    EXPECT_EQ(bst.get_root()->right->right->right->value, 75);
    EXPECT_EQ(bst.get_root()->right->left->value, 60);
    EXPECT_EQ(bst.get_root()->right->left->left, nullptr);
    EXPECT_EQ(bst.get_root()->right->left->right, nullptr);
}

TEST(BinarySearchTreeTest, TEST21) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(65);
    bst.add_node(60);
    bst.add_node(70);
    bst.add_node(5);
    bst.add_node(2);
    bst.add_node(7);
    bst.add_node(75);

    rbc::Node<int>* address_of_60{*bst.find_node(60)};
    rbc::Node<int>* address_of_75{*bst.find_node(75)};

    EXPECT_TRUE(bst.delete_node(50)); // only left child

    // the remainig nodes should not be regenerated
    // => address of remaning nodes before and after deletion should be the same
    // when deleting a node: just reconnect the needed parrents and childs
    EXPECT_EQ(*bst.find_node(60), address_of_60);
    EXPECT_EQ(*bst.find_node(75), address_of_75);
}

TEST(BinarySearchTreeTest, TEST22) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(65);
    bst.add_node(60);
    bst.add_node(70);
    bst.add_node(5);
    bst.add_node(2);
    bst.add_node(7);
    bst.add_node(75);
    bst.add_node(20);
    bst.add_node(15);

    EXPECT_EQ(bst.length(), 12);
    EXPECT_TRUE(bst.delete_node(10)); // both children exist
    EXPECT_EQ(bst.length(), 11);
    EXPECT_EQ(bst.get_root()->left->value, 7);
    EXPECT_EQ(bst.get_root()->left->left->right, nullptr);
    EXPECT_EQ(bst.get_root()->left->left->value, 5);
}

TEST(BinarySearchTreeTest, TEST23) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(65);
    bst.add_node(60);
    bst.add_node(70);
    bst.add_node(5);
    bst.add_node(2);
    bst.add_node(7);
    bst.add_node(75);
    bst.add_node(20);
    bst.add_node(15);
    bst.add_node(22);

    EXPECT_EQ(bst.length(), 13);
    EXPECT_TRUE(bst.delete_node(25)); // both children exist
    EXPECT_EQ(bst.length(), 12);
    EXPECT_EQ(bst.get_root()->value, 22);
    EXPECT_EQ(bst.get_root()->left->value, 10);
    EXPECT_EQ(bst.get_root()->left->right->right, nullptr);
}

TEST(BinarySearchTreeTest, TEST24) {
    rbc::BST<int> bst{};
    bst.add_node(5);
    bst.add_node(10);
    bst.add_node(50);
    rbc::BST<int> copy{bst};
    EXPECT_EQ(bst.length(), copy.length());
    EXPECT_EQ(bst.get_root()->right->value, copy.get_root()->right->value);
}

TEST(BinarySearchTreeTest, TEST25) {
    rbc::BST<int> bst{};
    bst.add_node(5);
    bst.add_node(10);
    bst.add_node(50);

    rbc::BST<int> equal{};
    bst.add_node(51);
    bst.add_node(66);
    bst.add_node(10);
    equal = bst;
    EXPECT_EQ(bst.length(), equal.length());
    EXPECT_EQ(bst.get_root()->right->right->value,
equal.get_root()->right->right->value);
}

TEST(BinarySearchTreeTest, TEST26) {
    rbc::BST<int> bst{};
    bst.add_node(5);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(1);
    bst.add_node(2);
    bst.add_node(4);
    bst.add_node(60);
    bst.add_node(8);

    bst = bst;
    EXPECT_EQ(bst.get_root()->right->left->value, 8);
}

TEST(BinarySearchTreeTest, TEST27) {
    rbc::BST<int> bst{};
    bst.add_node(5);
    bst.add_node(10);
    bst.add_node(50);

    int test_value{bst.get_root()->right->value};
    rbc::Node<int>* adddress_of_root{*bst.find_node(5)};

    rbc::BST<int> move{std::move(bst)};
    EXPECT_EQ(adddress_of_root, move.get_root());
    EXPECT_EQ(test_value, move.get_root()->right->value);
}

TEST(BinarySearchTreeTest, TEST28) {
    rbc::BST<int> bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(65);
    bst.add_node(5);
    bst.add_node(20);
    bst.add_node(22);

    int test_value{bst.get_root()->left->right->value};
    rbc::Node<int>* adddress_of_root{*bst.find_node(25)};

    rbc::BST<int> move{};
    move = std::move(bst);
    EXPECT_EQ(adddress_of_root, move.get_root());
    EXPECT_EQ(test_value, move.get_root()->left->right->value);
}

TEST(BinarySearchTreeTest, TEST29) {
    rbc::BST<int> bst1{5, 1, 10, 2, 8, 50, 4, 60};
    rbc::BST<int> bst2{3, 2, 100, 20, 8, 50, 4, 60, 44, 23};
    EXPECT_EQ((*bst1.find_successor(5))->value, 4);
    EXPECT_EQ(bst2.length(), 10);
}

TEST(BinarySearchTreeTest, TEST30) {
    rbc::BST<int> bst{5, 1, 10, 2, 8, 50, 4, 60};
    rbc::BST<int> bst2{++bst};

    std::vector<int> values;
    EXPECT_EQ(bst.get_root()->value, 6);
    EXPECT_EQ(bst2.get_root()->value, 6);
    EXPECT_EQ(bst.get_root()->right->right->right->value, 61);
    EXPECT_EQ(bst2.get_root()->right->right->right->value, 61);

}

TEST(BinarySearchTreeTest, TEST31) {
    rbc::BST<int> bst1{5, 1, 10, 2, 8, 50, 4, 60};
    rbc::BST<int> bst2{bst1++};

    std::vector<int> values1;
    bst1.bfs([&values1](rbc::Node<int>*& node){values1.push_back(node->value);});

    std::vector<int> values2;
    bst2.bfs([&values2](rbc::Node<int>*& node){values2.push_back(node->value);});

    for(size_t i{}; i < values1.size(); i++)
        EXPECT_EQ(values2[i], values1[i]-1);
}
