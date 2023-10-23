#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <sstream> 
#include <algorithm>
#include <set>
#include <queue> 
#include <stack>
    using namespace std;

    //Kiểu dữ liệu đỉnh
    struct Edge {
        int source;
        int target;
    };
    //Có trọng số
    struct EdgeWeight
    {
        int source;
        int target;
        int weight;
    };
    //Đọc đồ thị không có trọng số từ file txt
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

        int source = 0;
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

    //Đọc đồ thị có trọng số từ file txt
    vector<EdgeWeight> readGraphWeightFromFile(const string& filename, int& numVertices) {
        vector<EdgeWeight> edges;
        ifstream inputFile(filename);

        if (!inputFile.is_open()) {
            cout << "Cannot open file." << endl;
            return edges;
        }

        // Đọc số lượng đỉnh từ dòng đầu tiên
        string line;
        getline(inputFile, line);
        numVertices = stoi(line);

        int source = 0;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            int target, weight;
            while (ss >> target >> weight) {
                EdgeWeight edge = { source, target, weight };
                edges.push_back(edge);
            }
            source++;
        }

        inputFile.close();
        return edges;
    }

    //Kiểm tra vô hướng
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

    //In đồ thị dưới dạng ma trận
    void printAdjacencyMatrix(const vector<Edge>& edges, int numVertices) {
        vector<vector<int>> adjacencyMatrix(numVertices, vector<int>(numVertices, 0));

        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
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

                adjacencyMatrix[i][j] = hasEdge ? check : 0;
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    //Cặp đỉnh có cạnh bội
    int countDuplicateEdges(const vector<Edge>& edges) {
        const int MAX_VERTICES = 100; // Số lượng đỉnh tối đa
        vector<vector<int>> edgeCount(MAX_VERTICES, vector<int>(MAX_VERTICES, 0));

        int count = 0;

        for (const auto& edge : edges) {
            edgeCount[edge.source][edge.target]++;
        }

        for (const auto& edge : edges) {
            if (edgeCount[edge.source][edge.target] > 1 && edge.source < edge.target) {
                count++;
            }
        }
        return count/2;
    }

    //Tổng cạnh của đồ thị
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

    //Bậc của đỉnh đồ thị vô hướng
    vector<int> calculateDegreesUndirected(const vector<Edge>& edges, int numVertices) {
        vector<int> degrees(numVertices, 0); // Bậc của đỉnh bắt đầu từ 1

        for(int i = 0; i < edges.size(); ++i) {
            int source = edges[i].source;
            int target = edges[i].target;

            if (source == target) {            
                degrees[source]++;
                degrees[target]++;
            }
            else {         
                degrees[source]++;       
            }
        }
        return degrees;
    }

    //Bậc của đỉnh đồ thị có hướng
    void calculateInAndOutDegrees(const vector<Edge>& edges, int numVertices,vector<int>& inDegrees, vector<int>& outDegrees) {

        inDegrees.resize(numVertices, 0); 
        outDegrees.resize(numVertices, 0);

        for (const Edge& edge : edges) {
            outDegrees[edge.source]++;
            inDegrees[edge.target]++;
        }
    }

    //Đếm cạnh khuyên
    int countEdgePiercings(const vector<Edge>& edges) {
        int check = 0;
        for (const Edge& edge : edges) {
            if (edge.source == edge.target) {
                check++;
            }
        }
        return check;
    }

    //Đến đỉnh treo đồ thị vô hướng
    int countHangingVerticesUndirected(const vector <int> degree, int numVertices) {
        int check = 0;
        for (int i = 0; i <numVertices; ++i) {
            if (degree[i] == 1) {
                check++;
            }
        }
        return check;
    }

    //Đếm đỉnh cô lặp đồ thị vô hướng
    int countIsolatedVerticesUndirected(const vector <int> degree, int numVertices) {
        int check = 0;
        for (int i = 0; i < numVertices; ++i) {
            if (degree[i] == 0) {
                check++;
            }
        }
        return check;
    }

    //Đếm đỉnh treo đồ thị có hướng
    int countHangingVerticesDirected(const vector<int> inDegrees, vector <int> outDegrees, int numVertices) {
        int check = 0;
        for (int i = 0; i < numVertices; ++i) {
            if ((outDegrees[i] + inDegrees[i]) == 1) {
                check++;
            }
        }
        return check;
    }

    //Đếm đỉnh cô lặp đồ thị có hướng 
    int countIsolatedVerticesDirected(const vector<int> inDegrees, vector <int> outDegrees, int numVertices) {
        int check = 0;
        for (int i = 0; i < numVertices; ++i) {
            if ((outDegrees[i] + inDegrees[i]) == 0) {
                check++;
            }
        }
        return check;
    }

    //DFS
    void DFS(const vector<vector<int>>& adjacencyList, int source, unordered_set<int>& visited) {
        cout << source << " ";
        visited.insert(source);

        for (int neighbor : adjacencyList[source]) {
            if (visited.find(neighbor) == visited.end()) {
                DFS(adjacencyList, neighbor, visited);
            }
        }
    }

    void printDFS(const vector<Edge>& edges, int numVertices, int source) {
        vector<vector<int>> adjacencyList(numVertices);

        for (const auto& edge : edges) {
            adjacencyList[edge.source].push_back(edge.target);
            // adjacencyList[edge.target].push_back(edge.source);
        }

        unordered_set<int> visited;
        cout << "DFS traversal starting from vertex " << source << ": ";
        DFS(adjacencyList, source, visited);
        cout << endl;
    }

    //BFS
    vector<int> BFS(const vector<vector<int>>& adjacencyList, int source, unordered_set<int>& visited) {
        vector<int> result;
        queue<int> q;
        q.push(source);
        visited.insert(source);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            result.push_back(current);
            for (int neighbor : adjacencyList[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }

        return result;
    }

    void printBFS(const vector<Edge>& edges, int numVertices, int source) {
        vector<vector<int>> adjacencyList(numVertices);

        for (const auto& edge : edges) {
            adjacencyList[edge.source].push_back(edge.target);
            // adjacencyList[edge.target].push_back(edge.source);
        }

        unordered_set<int> visited;
        vector<int> bfsResult = BFS(adjacencyList, source, visited);

        cout << "BFS traversal starting from vertex " << source << ": ";
        for (int vertex : bfsResult) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    //In ra các thành phần liên thông
    void printConnectedComponents(const vector<Edge>& edges, int numVertices) {
        vector<vector<int>> adjacencyList(numVertices);
        for (const auto& edge : edges) {
            adjacencyList[edge.source].push_back(edge.target);
            adjacencyList[edge.target].push_back(edge.source);
        }

        vector<bool> visited(numVertices, false);
        int componentCount = 0;

        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                queue<int> q;
                q.push(i);
                visited[i] = true;
                componentCount++;

                cout << "Interconnection components  " << componentCount << ": ";
                while (!q.empty()) {
                    int current = q.front();
                    q.pop();
                    cout << current << " ";
                    for (int neighbor : adjacencyList[current]) {
                        if (!visited[neighbor]) {
                            q.push(neighbor);
                            visited[neighbor] = true;
                        }
                    }
                }
                cout << endl;
            }
        }
        cout << "Number of interconnected components: " << componentCount << endl;
    }

    //Kiểm tra liên thông bằng BFS
    bool isConnectedGraph(const vector<Edge>& edges, int numVertices) {
        vector<vector<int>> adjacencyList(numVertices);

        for (const auto& edge : edges) {
            adjacencyList[edge.source].push_back(edge.target);
            adjacencyList[edge.target].push_back(edge.source);
        }

        unordered_set<int> visited;
        BFS(adjacencyList, edges[0].source, visited);

        return (visited.size() == numVertices);
    }

    //Prim
    void prim(const vector<EdgeWeight>& edges, int source, int numVertices) {
        int sumWeight = 0;
        bool used[1000];
        memset(used, false, sizeof(used));
        vector<pair<int, int>> adj[1000];
        vector<EdgeWeight> SpanningTree;  
        for (const EdgeWeight& edge : edges) {
            adj[edge.source].emplace_back(edge.target, edge.weight);
            adj[edge.target].emplace_back(edge.source, edge.weight); 
        }

        used[source] = true;

        while (SpanningTree.size() < numVertices - 1) {
            int minW = INT_MAX;
            int x, y;
            for (int i = 0; i < numVertices; i++) { 
                if (used[i]) {
                    for (const pair<int, int>& it : adj[i]) {
                        int j = it.first, weight = it.second;
                        if (!used[j] && weight < minW) {
                            minW = weight;
                            x = i; y = j;
                        }
                    }
                }
            }
            SpanningTree.push_back({ x, y, minW });
            sumWeight += minW;
            used[y] = true; 
        }
        cout << "Minimum Spanning Tree (Prim Algorithm):" << endl;
        for (const EdgeWeight& edge : SpanningTree) {
            cout << edge.source << "-" << edge.target << ": " << edge.weight << endl;
        }
        cout << "Weights of the Spanning tree: " << sumWeight << endl << endl;
    }

    //Kruskal. 
    bool compareEdges(const EdgeWeight& edge1, const EdgeWeight& edge2) {
        return edge1.weight < edge2.weight;
    }
    int findParent(vector<int>& parent, int node) {
        if (parent[node] == node) {
            return node;
        }
        return parent[node] = findParent(parent, parent[node]);
    }
    void kruskal(const vector<EdgeWeight>& edges, int numVertices) {
        vector<EdgeWeight> sortedEdges = edges;
        sort(sortedEdges.begin(), sortedEdges.end(), compareEdges);

        vector<int> parent(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            parent[i] = i;
        }

        vector<EdgeWeight> minSpanningTree;
        int totalWeight = 0;

        for (const EdgeWeight& edge : sortedEdges) {
            int parentSource = findParent(parent, edge.source);
            int parentTarget = findParent(parent, edge.target);
            if (parentSource != parentTarget) {
                minSpanningTree.push_back(edge);
                totalWeight += edge.weight;
                parent[parentSource] = parentTarget;
            }
        }

        cout << "Minimum Spanning Tree (Kruskal Algorithm):" << endl;
        for (const EdgeWeight& edge : minSpanningTree) {
            cout << edge.source << "-" << edge.target << ": " << edge.weight << endl;
        }

        cout << "Weights of the Spanning tree: " << totalWeight << endl;
    }

    //Kiểm tra đồ thị có trọng số dương
    bool isGraphWithPositiveWeights(const vector<EdgeWeight>& edges) {
        for (const EdgeWeight& edge : edges) {
            if (edge.weight <= 0) {
                return false; 
            }
        }
        return true; 
    }
    //Dijkstra
    void dijkstra(const vector<EdgeWeight>& edges, int numVertices, int source) {
        vector<int> distance(numVertices, INT_MAX);
        vector<int> parent(numVertices, -1);

        distance[source] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, source));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const EdgeWeight& edge : edges) {
                if (edge.source == u) {
                    int v = edge.target;
                    int weight = edge.weight;
                    if (distance[v] > distance[u] + weight) {
                        distance[v] = distance[u] + weight;
                        parent[v] = u;
                        pq.push(make_pair(distance[v], v));
                    }
                }
            }
        }

        for (int i = 0; i < numVertices; ++i) {
            if (i != source && distance[i] != INT_MAX) {
                cout << "Cost from " << source << " to " << i << ": " << distance[i] << endl;
                cout << "Path: ";
                int current = i;
                vector<int> path;
                while (current != -1) {
                    path.push_back(current);
                    current = parent[current];
                }
                for (int j = path.size() - 1; j >= 0; --j) {
                    cout << path[j];
                    if (j != 0) cout << " -> ";
                }
                cout << endl;
            }
            else if (i != source) {
                cout << "No path from " << source << " to " << i << endl;
            }
        }
    }

    //Forrd-Bellman
    void fordBellman(const vector<EdgeWeight>& edges, int numVertices, int source) {
        vector<int> distance(numVertices, INT_MAX);
        vector<int> parent(numVertices, -1);

        distance[source] = 0;

        for (int i = 0; i < numVertices - 1; ++i) {
            for (const EdgeWeight& edge : edges) {
                if (distance[edge.source] != INT_MAX && distance[edge.source] + edge.weight < distance[edge.target]) {
                    distance[edge.target] = distance[edge.source] + edge.weight;
                    parent[edge.target] = edge.source;
                }
            }
        }

        // Kiểm tra chu trình âm
        for (const EdgeWeight& edge : edges) {
            if (distance[edge.source] != INT_MAX && distance[edge.source] + edge.weight < distance[edge.target]) {
                cout << "Do thi co mach am" << endl;
                return;
            }
        }

        for (int i = 0; i < numVertices; ++i) {
            if (i != source && distance[i] != INT_MAX) {
                cout << "Cost from " << source << " to " << i << ": " << distance[i] << endl;
                cout << "Path: ";
                int current = i;
                vector<int> path;
                while (current != -1) {
                    path.push_back(current);
                    current = parent[current];
                }
                for (int j = path.size() - 1; j >= 0; --j) {
                    cout << path[j];
                    if (j != 0) cout << " -> ";
                }
                cout << endl;
            }
            else if (i != source) {
                cout << "No path from " << source << " to " << i << endl;
            }
        }
    }

    //Kiểm tra đơn đồ thị
    bool isSimpleGraph(const vector<Edge>& edges) {
        if (isUndirectedGraph(edges) == false && countDuplicateEdges(edges)>1 && countEdgePiercings(edges) > 0) {
            return false;
        }
        return true;
    }

    //Tim chu trình euler
    void Euler(const vector<Edge>& edges, int source, int numVertices) {
        vector<set<int>> adj(numVertices);
        for (const Edge& edge : edges) {
            adj[edge.source].insert(edge.target);
            adj[edge.target].insert(edge.source);
        }

        stack<int> st;
        vector<int> EulerCycle;

        st.push(source);
        while (!st.empty()) {
            int x = st.top();
            if (!adj[x].empty()) {
                int y = *adj[x].begin();
                st.push(y);

                adj[x].erase(y);
                adj[y].erase(x);
            }
            else {
                st.pop();
                EulerCycle.push_back(x);
            }
        }

        if (EulerCycle.empty()) {
            cout << "No solution" << endl;
        }
        else {
            reverse(begin(EulerCycle), end(EulerCycle));

            
            if (!EulerCycle.empty() && EulerCycle.front() == EulerCycle.back()) {
                cout << "Euler Cycle: ";
                for (int vertex : EulerCycle) {
                    cout << vertex << " ";
                }
                cout << endl;
            }
            else {
                cout << "Euler Path: ";
                for (int vertex : EulerCycle) {
                    cout << vertex << " ";
                }
                cout << endl;
            }
        }
    }
    //Xử lý yêu cầu 1
    void Requirement1 (const vector<Edge>& edges, int numVertices) {
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
            int coutIsolated = countIsolatedVerticesDirected(inDegrees, outDegrees, numVertices);

            cout << "Sum of isolated vertices of graph: " << coutIsolated << endl;
        }
        //bậc cuả đỉnh
        if (isUndirectedGraph(edges)) {
            cout << "Degrees of vertices:" << endl;
            for (int i = 0; i < numVertices; ++i) {
                cout << "Vertex " << i << ": " << degrees[i] << endl;
            }
        }
        else {
            vector<int> inDegrees, outDegrees;
            calculateInAndOutDegrees(edges, numVertices, inDegrees, outDegrees);
            for (int i = 0; i < numVertices; ++i) {
                cout << "Vertex " << i << ": In-Degree = " << inDegrees[i] << ", Out-Degree = " << outDegrees[i] << std::endl;
            }
        }
    }

    //Xử lý yêu cầu 2
    void Requirement2(const vector<Edge>& edges, int numVertices) {
        int source;
        cout << "Enter source ";
        cin >> source;

        printDFS(edges, numVertices, source);
        printBFS(edges, numVertices, source);

        if (isUndirectedGraph) {
            cout << "This is an undirected graph." << endl;
        }
        printConnectedComponents(edges, numVertices);
    }

    //Xử lý yêu cầu 3
    void Requirement3(const vector<EdgeWeight>& edges, int numVertices) {
        vector<Edge> adjacencyList(edges.size());
        for (int i = 0; i < edges.size() ; i++) {
            adjacencyList[i].source = edges[i].source;
            adjacencyList[i].target = edges[i].target;
            }
        if (isUndirectedGraph(adjacencyList) && isConnectedGraph(adjacencyList, numVertices)) {
            int source = 0;
            prim(edges, source, numVertices);
            kruskal(edges, numVertices);
        }
        else {
            cout << "Đồ thị không phải là đồ thị vô hướng liên thông." << endl;
        }
        
        
    }

    //Xử lý yêu cầu 4
    void Requirement4(const vector<EdgeWeight>& edges, int numVertices) {
        int source;
        cout << "Enter source ";
        cin >> source;
        if (isGraphWithPositiveWeights(edges)) {
            cout << "The shortest path according to the Dijkstra algorithm" << endl;
            dijkstra(edges, numVertices, source);
        }
        else {
            cout << "A graph is not a connected scalar graph." << endl;
        }
        cout << "The shortest path according to the Forrd-Bellman algorithm" << endl;
        fordBellman(edges, numVertices, source);
    }

    //Xử lý yêu cầu 5
    void Requirement5(const vector<Edge>& edges, int numVertices) {
        int source = 0;
        if (isSimpleGraph(edges)) {
            if (!isConnectedGraph(edges, numVertices)) {
                cout << "Non - Euler Graph" << endl;
            }
            else {
                vector<int> degree(numVertices, 0);
                degree = calculateDegreesUndirected(edges, numVertices);

                int oddDegreeCount = 0;
                vector<int> oddDegreeVertices;

                for (int i = 0; i < numVertices; ++i) {
                    if (degree[i] % 2 != 0) {
                        oddDegreeCount++;
                        oddDegreeVertices.push_back(i);
                    }
                }
                if (oddDegreeCount == 0) {
                    cout << "Euler Graph" << endl;
                    int source;
                    cout << "Enter source ";
                    cin >> source;
                    Euler(edges, source, numVertices);
                }
                else if (oddDegreeCount == 2) {
                    cout << "Semi - Euler Graph" << endl;
                    cout << "The euler path can start from vertices : ";
                    for (int vertex : oddDegreeVertices) {
                        cout << vertex << " " << endl;
                    }
                    int source;
                    cin >> source;

                    while (find(oddDegreeVertices.begin(), oddDegreeVertices.end(), source) == oddDegreeVertices.end()) {
                        cout << "Invalid vertex. Retype: ";
                        cin >> source;
                    }
                    Euler(edges, source, numVertices);
                    cout << endl;
                }
                else {
                    cout << "Non - Euler Graph" << endl;
                }
            }
        }
        else {
            cout << "Not single graphs" << endl;}
    }
    //main
    int main() {       
 
        int choice;
        while (true) {
            cout << "Menu:" << endl;
            cout << "1. Requirement 1 " << endl;
            cout << "2. Requirement 2" << endl;
            cout << "3. Requirement 3" << endl;
            cout << "4. Requirement 4" << endl;
            cout << "5. Requirement 5" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your selection: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "1. Requirement 1: " << endl; {
                    int numVertices = 0;
                    vector<Edge> edges = readGraphFromFile("graph1.txt", numVertices);
                    Requirement1(edges, numVertices);
                }
                break;
            case 2:
                cout << "2. Requirement 2" << endl; {
                    int numVertices = 0;
                    vector<Edge> edges = readGraphFromFile("graph2.txt", numVertices);
                    Requirement2(edges, numVertices);
                }
                break;
            case 3:
                cout << "3. Requirement 3" << endl;
                {
                    int numVertices;
                    vector<EdgeWeight> edges = readGraphWeightFromFile("graph3.txt", numVertices);               
                    Requirement3(edges, numVertices);
                }
                
                break;
            case 4:
                cout << "4. Requirement 4" << endl; {
                    int numVertices;
                    vector<EdgeWeight> edges = readGraphWeightFromFile("graph4.txt", numVertices);   
                    Requirement4(edges, numVertices);                
                }

                break;
            case 5:
                cout << "5. Requirement 5" << endl; {
                    int numVertices;
                    vector<Edge> edges = readGraphFromFile("graph5.txt", numVertices);
                    Requirement5(edges, numVertices);
                }
                break;

            case 6:
                cout << "Goodbye! The show ended." << endl;
                return 0;
            default:
                cout << "Invalid selection. Please select again." << endl;
            }
        }
        return 0;
    }        
    
