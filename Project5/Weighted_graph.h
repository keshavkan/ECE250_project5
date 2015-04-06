/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <vector>
#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

class Weighted_graph {
	private:
		static const double INF;


		unsigned int numV;			// |V|
		double **adjMatrix;			// adjacency matrix
		unsigned int adjSize;		// adj size
		unsigned int *degArray;		// vertex degree array; // could also just use for loop everytime
		
		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );
        static bool comp_weight(const struct Edge &lhs, const struct Edge &rhs);


	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();
    

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

struct Edge {
	unsigned int v1;
	unsigned int v2;
	double weight;
};

// Edge struct comparator function
bool Weighted_graph::comp_weight(const struct Edge &lhs, const struct Edge &rhs) {
    return lhs.weight < rhs.weight;
}



/*********************************************************************
 * ***************************************************************** *
 * *                                                               * *
 * *   Constructor, Deconstructor, Operators	                   * *
 * *                                                               * *
 * ***************************************************************** *
 *********************************************************************/

/*
 * Constructor: Creates 2D adjacency matrix and degree array.
 * 				Initializes them to 0 indicating no edges
 *
 */
Weighted_graph::Weighted_graph( int n ) {

	numV = (unsigned int)n;
	degArray = new unsigned int[numV];

	//declare adjacency matrix
	adjMatrix = new double*[numV];
	//contiguous LT temporary array
	adjSize = ((numV - 1) * numV) / 2;
	adjMatrix[0] = nullptr;
	adjMatrix[1] = new double[adjSize];

	//OPT delete dagArray
	degArray[1] = degArray[0] = 0;

	for (unsigned int i = 2; i < numV; i++) {
		adjMatrix[i] = adjMatrix[i - 1] + i - 1;
		degArray[i] = 0;
	}

	for (unsigned int i = 0; i < adjSize; i++) {
		 adjMatrix[1][i] = 0;
	}
}

/*
 * Deconstructor: Deletes adjacency matrices and degree arrays
 *
 *
 */
Weighted_graph::~Weighted_graph() {

	//OPT delete degarray
	delete [] degArray; 
	delete [] adjMatrix[1];
	delete [] adjMatrix;
}


std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	return out;
}



/*********************************************************************
 * ***************************************************************** *
 * *                                                               * *
 * *   Accessors                                                   * *
 * *                                                               * *
 * ***************************************************************** *
 *********************************************************************/

/*
 * Accessor: int degree(int i)
 *
 * Returns: degree of vertex passed
 */
int Weighted_graph::degree(int i) const {

 	if (i < 0 || i >= numV) {
 		throw illegal_argument();
 	}

    return degArray[i];
}


/*
 * Accessor: int edge_count()
 *
 * Returns: the number of edges in the graph by traversign through degArray
 */
int Weighted_graph::edge_count() const {

	unsigned int counter = 0;

	//OPT traversing through degArray will be faster sum(degArray)/2
	// for (unsigned int i = 0; i < adjSize; i++) {
	// 	if (adjMatrix[1][i] != 0) {
	// 		counter++;
	// 	}
	// }

	for (unsigned int i = 0; i < numV; i++) {
		counter += degArray[i];
	}

	return counter / 2;
}


/*
 * Accessor: std::pair<double, int>  minimum_spanning_tree()
 *
 * Uses kruskal's algorith to calculate the minimum spanning tree. 
 * Disjoint_sets data structure is needed
 *
 * Returns: a pair containing the weight of the graph and the number of edges scanned
 */
std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {

	unsigned int eg_count = 0;		//edge traversal count
	double mst_weight = 0;			//tree weight
	std::vector<Edge> eg_vector;	//Edge vector //OPT specify vector size(edge_count())

	// traverse through adjMatrix and insert Edges to 
	for (unsigned int i = 1; i < adjSize; i++) {
		for (unsigned int j = 0; j < i; j++) {
			if (adjMatrix[i][j] != 0) {
				eg_vector.insert(eg_vector.end(), (Edge){i, j, adjMatrix[i][j]});
			}
		}
	}

	// sort Edge vector
    std::sort(eg_vector.begin(), eg_vector.end(), comp_weight);

	//create disjoint set for every vertex
    Data_structures::Disjoint_sets *v_set = new Data_structures::Disjoint_sets(numV);

	//traverse through Edge vector 
	for (unsigned int i = 0; i < eg_vector.size(); i++) {
		Edge e = eg_vector.at(i); // OPT: create instance or nah or at front
		// add vertices to join sets
		v_set->set_union(e.v1, e.v2);
        // increment count and weight
		eg_count++;
		mst_weight += e.weight;
        
		// break if all vertices are in one set. ie. mst created
		if (v_set->disjoint_sets() == 1) {
			break;
		}
	}


	return std::pair<double, int>(mst_weight, eg_count);
}



/*********************************************************************
 * ***************************************************************** *
 * *                                                               * *
 * *   Mutators 								                   * *
 * *                                                               * *
 * ***************************************************************** *
 *********************************************************************/

/*
 * Mutator: bool insert_edge( int i, int j, double d )
 *
 * Returns all 
 */
bool Weighted_graph::insert_edge( int i, int j, double d ) {
	
	if (i >= numV || i < 0 || j >= numV || j < 0 || d <= 0) {
		throw illegal_argument();
	}

	if (i == j) {
		return false;
	}

	// assign larger vertex to i as adjMatrix is lower triangular
	if (i < j) { std::swap(i,j); }

	// insert edge weight to adjMatrix
	adjMatrix[i][j] = d;


	// OPT can remove degArray
	degArray[i]++;
	degArray[j]++;

	return true;
}


/*
 * Mutator: bool erase_edge( int i, int j )
 *
 * Returns true if and existing edge is erased. Else false
 */
bool Weighted_graph::erase_edge( int i, int j ) {

	if (i >= numV || i < 0 || j >= numV || j < 0) {
		throw illegal_argument();
	}

	if (i == j) {
		return false;
	}

	if (i < j) { std::swap(i,j); }

	// delete edge or return false
	if (adjMatrix[i][j] == 0) {
		return false;
	} else {
		adjMatrix[i][j] = 0;


		// OPT can remove degArray
		degArray[i]--;
		degArray[j]--;


		return true;
	}
}


/*
 * Mutator: void clear_edges()
 *
 * Clears all edges from the graph by resetting the adjMatrix.
 */
void Weighted_graph::clear_edges() {

	// set adMatrix to 0, clearing all edges
	for (unsigned int i = 0; i < adjSize; i++) {
		 adjMatrix[1][i] = 0;
	}
}

#endif
