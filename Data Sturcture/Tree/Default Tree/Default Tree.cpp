#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;
// smart pointer를 사용하여 생명주기 관리
using NodeRef = shared_ptr<struct Node>;

NodeRef CreateTree();
void PrintTree(NodeRef root, int depth);
int Getheight(NodeRef root);

struct Node 
{
    Node() { }
    Node(const string& data) : _data(data) { }

    string              _data;
    vector<NodeRef>   _children;
};

int main()
{
    NodeRef GameTeam = CreateTree();

    PrintTree(GameTeam, 0);

    int height = Getheight(GameTeam);

    cout << "GameTeam Tree Height is " << height << endl;

    return 0;
}

NodeRef CreateTree()
{
    NodeRef root = make_shared<Node>("R1 개발실");
    // 디자인 팀
    {
        NodeRef node = make_shared<Node>("디자인 팀");
        root->_children.push_back(node);
        {
            NodeRef leaf = make_shared<Node>("전투");
            node->_children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("경제");
            node->_children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("스토리");
            node->_children.push_back(leaf);
            {
                NodeRef leaf2 = make_shared<Node>("스토리 보드");
                leaf->_children.push_back(leaf2);
            }
        }
    }
    // 프로그래밍 팀
    {
        NodeRef node = make_shared<Node>("프로그래밍 팀");
        root->_children.push_back(node);
        {
            NodeRef leaf = make_shared<Node>("서버");
            node->_children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("클라");
            node->_children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("엔진");
            node->_children.push_back(leaf);
        }
    }
    // 아트 팀
    {
        NodeRef node = make_shared<Node>("아트 팀");
        root->_children.push_back(node);
        {
            NodeRef leaf = make_shared<Node>("배경");
            node->_children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("캐릭터");
            node->_children.push_back(leaf);
        }
    }

    return root;
}

// 재귀 함수를 이용해 접근
void PrintTree(NodeRef root, int depth)
{
    // 들여쓰기로 계층구조 보기 쉽게 만듦
    for (int i = 0; i < depth; i++)
        cout << "  ";

    cout << root->_data << endl;

    for (NodeRef& child : root->_children)
        PrintTree(child, depth + 1);
}

// 깊이 (Depth) : 루트에서 어떤 노드에 도달하기 위해 거쳐야 하는 간선의 수 (root = 0)
// 높이 (height) : 가장 깊숙히 있는 노드의 깊이 (max depth, root = 1)

// 재귀 함수를 통해 분할트리의 순회하면서 height를 구함.
int Getheight(NodeRef root)
{
    int height = 1;

    for (NodeRef& child : root->_children)
    {
        height = max(height, Getheight(child) + 1);
    }

    return height;
}
