#include <iostream>
#include "assert.h"
#include "Weighted_graph.h"
#include "Exception.h"
#include "ece250.h"

int main() {
    
    ece250::allocation_table.start_recording();
    
    Weighted_graph *g1 = new Weighted_graph(4);
    std::pair< double , int > min_tree;
    
    std::cout << "Harder's test file" << std::endl;
    
    try {
        g1->insert_edge( -1, 0, 0.3);
    } catch (illegal_argument) {}
    
    try {
        g1->insert_edge( 0, -2, 0.3);
    } catch (illegal_argument) {}
    
    try {
        g1->insert_edge( 0, 4, 0.3);
    } catch (illegal_argument) {}
    
    try {
        g1->insert_edge( 0, 3, -0.3);
    } catch (illegal_argument) {}
    
    assert(g1->insert_edge(0, 0, 0.3) == false);
    
    assert(g1->insert_edge(0, 1, 0.3) == true);
    min_tree = std::make_pair<double, int>(0.3, 1);
    assert(g1->minimum_spanning_tree() == min_tree);
    
    assert(g1->insert_edge(2, 3, 0.4) == true);
    min_tree = std::make_pair<double, int>(0.7, 2);
    assert(g1->minimum_spanning_tree() == min_tree);
    
    assert(g1->insert_edge(0, 2, 0.5) == true);
    min_tree = std::make_pair<double, int>(1.2, 3);
    assert(g1->minimum_spanning_tree() == min_tree);
    
    assert(g1->insert_edge(1, 3, 0.1) == true);
    min_tree = std::make_pair<double, int>(0.8, 3);
    assert(g1->minimum_spanning_tree() == min_tree);
    
    assert(g1->insert_edge(1, 3, 0.9) == true);
    min_tree = std::make_pair<double, int>(1.2, 3);
    assert(g1->minimum_spanning_tree() == min_tree);
    
    assert(g1->insert_edge(1, 3, 0.9) == true);
    min_tree = std::make_pair<double, int>(1.2, 3);
    assert(g1->minimum_spanning_tree() == min_tree);
    
    delete g1;
    
    std::cout << "First test complete" << std::endl;
    ece250::allocation_table.stop_recording();
    ece250::allocation_table.summary();
    
    
    
    // Second Test
    ece250::allocation_table.start_recording();
    g1 = new Weighted_graph(5);
    
    assert(g1->insert_edge(0, 1, 0.1) == true);
    assert(g1->insert_edge(1, 2, 0.1) == true);
    assert(g1->insert_edge(2, 3, 0.1) == true);
    assert(g1->insert_edge(0, 4, 3.1) == true);
    assert(g1->insert_edge(1, 4, 2.1) == true);
    assert(g1->insert_edge(2, 4, 1.1) == true);
    assert(g1->insert_edge(3, 4, 0.9) == true);
    
    assert(g1->insert_edge(0, 2, 0.4) == true);
    assert(g1->insert_edge(0, 3, 0.5) == true);
    assert(g1->insert_edge(1, 3, 0.6) == true);
    
    min_tree = std::make_pair<double, int>(1.2, 7);
    assert(g1->minimum_spanning_tree() == min_tree);
    
    assert(g1->insert_edge(0, 4, 0.45) == true);
    
    min_tree = std::make_pair<double, int>(0.75, 5);
    assert(g1->minimum_spanning_tree() == min_tree);
    
    assert(g1->erase_edge(0, 4) == true);
    
    min_tree = std::make_pair<double, int>(1.2, 7);
    assert(g1->minimum_spanning_tree() == min_tree);
    
    std::cout << "Harder's test file passed!" << std::endl;
    
    delete g1;
    
    ece250::allocation_table.stop_recording();
    ece250::allocation_table.summary();

    
    return 0;
}
/*
 summary*/