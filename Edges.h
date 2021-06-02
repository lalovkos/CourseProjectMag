#pragma once
#include <unordered_set>
#include <functional>

class Edge {
	private: 
		int EdgeNumber;

	public:
		//TODO: Перенести в private
		int firstPoint;
		int secondPoint;

		Edge(const int first, const int second);
		void SetFirst(const int first);
		int GetFirst();
		void SetSecond(const int second);
		int GetSecond();
		void SetEdgeNumber(const int number);
		int GetEdgeNumber();

		bool operator==(const Edge& otherEdge) const
		{
			if ((this->firstPoint == otherEdge.firstPoint && this->secondPoint == otherEdge.secondPoint) || 
			    (this->firstPoint == otherEdge.secondPoint && this->secondPoint == otherEdge.firstPoint))
				return true;
			else return false;
		}

		struct EdgesHasher {
			size_t operator()(const Edge& edge) const;
		};

};

