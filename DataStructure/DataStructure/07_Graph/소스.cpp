#include "Graph_MST.h"
using namespace std;

typedef Graph<char> G;

int main()
{
	G graph;

	G::Node* A = G::CreateNode('A');
	G::Node* B = G::CreateNode('B');
	G::Node* C = G::CreateNode('C');
	G::Node* D = G::CreateNode('D');
	G::Node* E = G::CreateNode('E');
	G::Node* F = G::CreateNode('F');
	G::Node* G = G::CreateNode('G');
	G::Node* H = G::CreateNode('H');

	graph.AddNode(A);
	graph.AddNode(B);
	graph.AddNode(C);
	graph.AddNode(D);
	graph.AddNode(E);
	graph.AddNode(F);
	graph.AddNode(G);
	graph.AddNode(H);

	//graph.AddEdge(A, G::CreateEdge(A, C));
	//graph.AddEdge(A, G::CreateEdge(A, D));

	//graph.AddEdge(B, G::CreateEdge(B, C));
	//graph.AddEdge(B, G::CreateEdge(B, E));

	//graph.AddEdge(C, G::CreateEdge(C, F));

	//graph.AddEdge(D, G::CreateEdge(D, F));
	//graph.AddEdge(D, G::CreateEdge(D, G));

	//graph.AddEdge(E, G::CreateEdge(E, G));

	//graph.AddEdge(F, G::CreateEdge(F, H));

	//graph.AddEdge(G, G::CreateEdge(G, H));


	graph.Sort(A);
	graph.PrintResult();


	return 0;
}