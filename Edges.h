#pragma once
#include <unordered_set>
#include <functional>

class Edge {
	private: 
		int EdgeNumber;
		int firstPoint;
		int secondPoint;

	public:	

		Edge(const int first, const int second);
		void SetFirst(const int first);
		int GetFirst();
		void SetSecond(const int second);
		int GetSecond();
		void SetEdgeNumber(const int number);
		int GetEdgeNumber();

		bool operator==(const Edge& otherEdge) const;

		struct EdgesHasher {
			size_t operator()(const Edge& edge) const;
		};

};

