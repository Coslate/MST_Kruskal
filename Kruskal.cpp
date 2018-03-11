#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <Kruskal.h>

void Kruskal_Algorithm::InitialSet(Fibonacci_Heap &fib_heap_q, const std::vector<LinkedListNode*> &all_node, std::unordered_map<FTNode*, MST_Edge*> &map_node_ft2edge, std::unordered_map<std::string, LinkedListNode*> &map_node_st2ll, AdjList &adj_list){
    std::unordered_map<LinkedListNode*, std::unordered_map<LinkedListNode*, bool>> map_edge_added;

    for(size_t i=0;i<all_node.size();++i){
        LinkedList* the_linked_list = adj_list.ReadAdjList(all_node[i]);
        LinkedListNode* current_node = the_linked_list->GetFristNode();
        while(current_node != NULL){
            LinkedListNode* node_to_add_ll = map_node_st2ll[current_node->GetName()];

            //Check if the edge has not been added to heap
            if(map_edge_added[all_node[i]].find(node_to_add_ll) == map_edge_added[all_node[i]].end()){
                std::string ft_name = "";
                ft_name.append(all_node[i]->GetName());
                ft_name.append("->");//Undirected edge
                ft_name.append(node_to_add_ll->GetName());
                FTNode*   ft_edge_add = new FTNode(current_node->GetData(), ft_name);
                MST_Edge* ft_edge     = new MST_Edge(all_node[i], node_to_add_ll, current_node->GetData());
                fib_heap_q.InsertArbitrary(ft_edge_add);

                map_node_ft2edge[ft_edge_add] = ft_edge;
                map_edge_added[all_node[i]][node_to_add_ll] = true;
                map_edge_added[node_to_add_ll][all_node[i]] = true;
            }
            current_node = current_node->GetNext();
        }
    }
}
void Kruskal_Algorithm::FindMST(Fibonacci_Heap &fib_heap_q, std::vector<MST_Edge*> &final_mst, AdjList &adj_list, const int all_node_size, std::unordered_map<FTNode*, MST_Edge*> map_node_ft2edge){
    UnionFind uf_forest;

    while(uf_forest.GetMaxWeight() < all_node_size){
        FTNode* ex_edge_node = fib_heap_q.ExtractMin();
        MST_Edge* ex_edge = map_node_ft2edge[ex_edge_node];
        LinkedListNode* u_node = ex_edge->RetEdgeA();
        LinkedListNode* v_node = ex_edge->RetEdgeB();

        if(uf_forest.Union(u_node, v_node)){

            //Inserted the MST edge to final_mst
            final_mst.push_back(ex_edge);
        }
    }
}
void Kruskal_Algorithm::PrintMST(const std::vector<MST_Edge*> &final_mst, const int print_width){
    int min_edge = 0;
    std::cout<<"MST : "<<std::endl;
    for(size_t i=0;i<final_mst.size();++i){
        LinkedListNode* start_node = final_mst[i]->RetEdgeA();
        LinkedListNode* end_node = final_mst[i]->RetEdgeB();
        int edge_weight = final_mst[i]->RetWeight();

        if(start_node == NULL){
            printf("(%*s --> %*s, weight = %*d)\n", print_width,  "NULL", print_width, end_node->GetName().c_str(), print_width, edge_weight);
        }else{
            printf("(%*s --> %*s, weight = %*d)\n", print_width, start_node->GetName().c_str(), print_width, end_node->GetName().c_str(), print_width, edge_weight);
        }
        min_edge += edge_weight;
    }
    printf("minimum total edge weight = %d\n", min_edge);
}
void Kruskal_Algorithm::Release(std::vector<MST_Edge*> &final_mst){
    while (!final_mst.empty()){
        MST_Edge* edge_to_delete = final_mst.back();
        final_mst.pop_back();
        delete edge_to_delete;
    }
}
