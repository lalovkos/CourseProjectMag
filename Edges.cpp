#include "Edges.h"


Edge::Edge(const int first, const int second) {
	firstPoint = first;
	secondPoint = second;
}

void Edge::SetFirst(const int first) {
	firstPoint = first;
}
int Edge::GetFirst() {
	return firstPoint;
}

void Edge::SetSecond(const int second) {
	secondPoint = second;
}

int Edge::GetSecond() {
	return secondPoint;
}

void Edge::SetEdgeNumber(const int number) {
	EdgeNumber = number;
}

int Edge::GetEdgeNumber() {
	return EdgeNumber;
}


size_t Edge::EdgesHasher::operator()(const Edge& edge) const
{
	size_t xHash = std::hash<int>()(edge.firstPoint);
	size_t yHash = std::hash<int>()(edge.secondPoint);
	return xHash ^ yHash;
}
