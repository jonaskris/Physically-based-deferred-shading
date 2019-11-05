#include <iostream>
#include <vector>
#include <Node.h>

class Scene
{ 
private:
    std::vector<Node*> nodes;

public:
    Scene(std::vector<Node*> nodes) : nodes(nodes) {}

    std::vector<Node*>& getNodes() { return nodes; }
};