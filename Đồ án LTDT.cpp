#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <sstream> 
#include <algorithm>
#include <set>
    using namespace std;

    struct Edge {
        int source;
        int target;
    };

    vector<Edge> readGraphFromFile(const string& filename, int& numVertices) {
        vector<Edge> edges;
        ifstream inputFile(filename);

        if (!inputFile.is_open()) {
            cout << "Cannot open file." << endl;
            return edges;
        }
        // Đọc số lượng đỉnh từ dòng đầu tiên
        string line;
        getline(inputFile, line); // Đọc dòng chứa số lượng đỉnh
        numVertices = stoi(line); // Chuyển đổi từ string sang int

        int source = 1;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            int target;
            while (ss >> target) {
                Edge edge = {source, target};
                edges.push_back(edge);
            }
            source++;
        }

        inputFile.close();
        return edges;
    }

    bool isUndirectedGraph(const vector<Edge>& edges) {
        unordered_set<int> uniqueEdges;

        for (const auto& edge : edges) {
            int forwardEdgeHash = edge.source * 1000 + edge.target;
            int backwardEdgeHash = edge.target * 1000 + edge.source;

            if (uniqueEdges.find(forwardEdgeHash) != uniqueEdges.end() ||
                uniqueEdges.find(backwardEdgeHash) != uniqueEdges.end()) {
                return true;
            }
            uniqueEdges.insert(forwardEdgeHash);
        }
        return false;
    }

    
    void printAdjacencyMatrix(const vector<Edge>& edges, int numVertices) {
        vector<vector<int>> adjacencyMatrix(numVertices, vector<int>(numVertices, 0));

        cout << "Adjacency Matrix:" << endl;
        for (int i = 1; i <= numVertices; i++) {
            for (int j = 1; j <= numVertices; j++) {
                // Kiểm tra xem có cạnh nào từ đỉnh i đến đỉnh j không
                int check = 0;
                bool hasEdge = false;
                for (const auto& edge : edges) {
                    if (edge.source == i && edge.target == j) {
                        ++check;
                        hasEdge = true;
                    }
                }
                // Gán giá trị 1 nếu có cạnh, ngược lại là 0

                adjacencyMatrix[i - 1][j - 1] = hasEdge ? check : 0;
                cout << adjacencyMatrix[i - 1][j - 1] << " ";
            }
            cout << endl;
        }
    }
    
    int countDuplicateEdges(const vector<Edge>& edges) {
        const int MAX_VERTICES = 100; // Số lượng đỉnh tối đa
        vector<vector<int>> edgeCount(MAX_VERTICES, vector<int>(MAX_VERTICES, 0));

        int count = 0;

        // Đếm số lần xuất hiện của các cặp đỉnh
        for (const auto& edge : edges) {
            edgeCount[edge.source][edge.target]++;
        }

        // Kiểm tra các cặp đỉnh có nhiều cạnh và không trùng ngược lại
        for (const auto& edge : edges) {
            if (edgeCount[edge.source][edge.target] > 1 && edge.source < edge.target) {
                count++;
            }
        }

        return count/2;
    }
    int countEdges(const vector<Edge>& edges, bool isUndirectedGraph) {
        int edgeCount = edges.size();
        for (const auto& edge : edges) {
            if (edge.target == 0) {
                edgeCount--;
            }
        }
        if (isUndirectedGraph) {
            for (const auto& edge : edges) {
                if (edge.target == edge.target) {
                    return edgeCount = (edgeCount + 1) / 2;
                }
                else {
                    return  edgeCount = edgeCount / 2;
                }
            }
        }
        else {
            return edgeCount;
        }
    }

    vector<int> calculateDegreesUndirected(const vector<Edge>& edges, int numVertices) {
        vector<int> degrees(numVertices + 1, 0); // Bậc của đỉnh bắt đầu từ 1

        for(int i = 0; i < edges.size(); ++i) {
            int source = edges[i].source;
            int target = edges[i].target;

            if (source == target) {
                // Cạnh khuyên: tăng bậc của đỉnh một lần
                degrees[source]++;
                degrees[target]++;
            }
            else {
                // Cạnh không phải khuyên: tăng bậc của cả hai đỉnh một lần
                degrees[source]++;       
            }
        }
        return degrees;
    }
    void calculateInAndOutDegrees(const vector<Edge>& edges, int numVertices,vector<int>& inDegrees, vector<int>& outDegrees) {

        inDegrees.resize(numVertices + 1, 0); 
        outDegrees.resize(numVertices + 1, 0);

        for (const Edge& edge : edges) {
            outDegrees[edge.source]++;
            inDegrees[edge.target]++;
        }
    }
    int countEdgePiercings(const vector<Edge>& edges) {
        int check = 0;
        for (const Edge& edge : edges) {
            if (edge.source == edge.target) {
                check++;
            }
        }
        return check;
    }

    int countHangingVerticesUndirected(const vector <int> degree, int numVertices) {
        int check = 0;
        for (int i = 1; i <= numVertices; ++i) {
            if (degree[i] == 1) {
                check++;
            }
        }
        return check;
    }
    int countIsolatedVerticesUndirected(const vector <int> degree, int numVertices) {
        int check = 0;
        for (int i = 1; i <= numVertices; ++i) {
            if (degree[i] == 0) {
                check++;
            }
        }
        return check;
    }
    int countHangingVerticesDirected(const vector<int> inDegrees, vector <int> outDegrees, int numVertices) {
        int check = 0;
        for (int i = 1; i <= numVertices; ++i) {
            if ((outDegrees[i] + inDegrees[i]) == 1) {
                check++;
            }
        }
        return check;
     
    }
    int countIsolatedVerticesDirected(const vector<int> inDegrees, vector <int> outDegrees, int numVertices) {
        int check = 0;
        for (int i = 1; i <= numVertices; ++i) {
            if ((outDegrees[i] + inDegrees[i]) == 0) {
                check++;
            }
        }
        return check;
    }



    int main() {
        int numVertices = 0;
        vector<Edge> edges = readGraphFromFile("graph.txt", numVertices);

        //in ma trận
        printAdjacencyMatrix(edges, numVertices);
        
        //kiểm tra vô hướng, có hướng
        if (isUndirectedGraph(edges)) {
            
            cout << "This is an undirected graph." << endl;
        }
        else {
            cout << "This is a directed graph." << endl;
        }

        int countedges = countEdges(edges, isUndirectedGraph(edges));

        //tổng số đỉnh
        cout << "Sum of vertices of graph: " << numVertices << endl;

        //tông số cạnh
        cout << "Sum of edges of graph: " << countedges << endl;

       //cặp đỉnh xuất hiện canh bội
        int duplicateEdgeCount = countDuplicateEdges(edges);
        cout << "Number of pairs of vertices with multiple edges: " << duplicateEdgeCount << endl;
        

        //cạnh khuyên
        int edgePiercings = countEdgePiercings(edges);
        cout << "Sum of edge piercings: " << edgePiercings << endl;

        // đỉnh treo, đỉnh cô lập 
        vector<int> degrees = calculateDegreesUndirected(edges, numVertices);
        if (isUndirectedGraph(edges)) {
            int countHanging = countHangingVerticesUndirected(degrees, numVertices);
            cout << "Sum of hanging vertices of graph: " << countHanging << endl;
            int coutIsolated = countIsolatedVerticesUndirected(degrees, numVertices);
            cout << "Sum of isolated vertices of graph: " << coutIsolated << endl;
        }
        else {
            vector<int> inDegrees, outDegrees;
            calculateInAndOutDegrees(edges, numVertices, inDegrees, outDegrees);
            int countHanging = countHangingVerticesDirected(inDegrees, outDegrees, numVertices);
            cout << "Sum of hanging vertices of graph: " << countHanging << endl;
            int coutIsolated = countIsolatedVerticesDirected(inDegrees,  outDegrees, numVertices);
            cout << "Sum of isolated vertices of graph: " << coutIsolated << endl;
        }
        //bậc cuả đỉnh
        if (isUndirectedGraph(edges)) {
            cout << "Degrees of vertices:" << endl;
            for (int i = 1; i <= numVertices; ++i) {
                cout << "Vertex " << i << ": " << degrees[i] << endl;
            }
        }
        else {
            vector<int> inDegrees, outDegrees;
            calculateInAndOutDegrees(edges, numVertices, inDegrees, outDegrees);
            for (int i = 1; i <= numVertices; ++i) {
                cout << "Vertex " << i << ": In-Degree = " << inDegrees[i] << ", Out-Degree = " << outDegrees[i] << std::endl;
            }
        }
        
        return 0;
    }
