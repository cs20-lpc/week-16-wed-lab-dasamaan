#include "GraphMatrix.hpp"
#include <string>

using namespace std;

GraphMatrix::GraphMatrix(int numV, GType type)
: Graph(numV, 0, type) {

    cout << "Constructor called with v = " << numV << endl;
    cout << "Stored v = " << v << endl;

    // Allocate rows
    adjMatrix = new bool*[v];

    // Allocate columns
    for (int i = 0; i < v; i++) {
        adjMatrix[i] = new bool[v];
    }

    // Initialize matrix to false
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            adjMatrix[i][j] = false;
        }
    }
}

GraphMatrix::~GraphMatrix() {
    for (int i = 0; i < v; i++) {
        delete[] adjMatrix[i];
    }

    delete[] adjMatrix;

}

bool GraphMatrix::isEdge(int i, int j) const {
    if (i < 0 || i >= v || j < 0 || j >= v) {
        throw std::out_of_range("toggleEdge: invalid vertex");
    }

    return adjMatrix[i][j];

}

ostream& GraphMatrix::print(ostream& os) const {
    os << "    ";
    for (int i = 0; i < v; i++) {
        os << i << ' ';
    }
    os << endl;

    os << "---";
    for (int i = 0; i < v; i++) {
        os << "--";
    }
    os << endl;

    for (int i = 0; i < v; i++) {
        os << i << " | ";
        for (int j = 0; j < v; j++) {
            os << adjMatrix[i][j] << ' ';
        }
        os << endl;
    }

    return os;
}

void GraphMatrix::toggleEdge(int i, int j) {
    if (i < 0 || i >= v || j < 0 || j >= v) {
        throw std::out_of_range("toggleEdge: invalid vertex");
    }

    // Toggle edge
    adjMatrix[i][j] = !adjMatrix[i][j];

    // Update edge count
    if (adjMatrix[i][j]) {
        e++;
    }
    else {
        e--;
    }

    // If undirected, mirror edge
    if (graphType == UNDIRECTED && i != j) {
        adjMatrix[j][i] = adjMatrix[i][j];
    }
}
