#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <Kruskal.h>

void Kruskal_Algorithm::InitialSet(Fibonacci_Heap &fib_heap_q, const std::vector<LinkedListNode*> &all_node, std::unordered_map<FTNode*, MST_Edge*> map_node_ft2edge, std::unordered_map<std::string, LinkedListNode*> &map_node_st2ll, AdjList &adj_list){
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
bool Kruskal_Algorithm::CheckIsTheEdge(std::unordered_map<LinkedListNode*, std::unordered_map<LinkedListNode*, int>> &map_weight, LinkedListNode* const candidate_parent, const int &edge_weight, LinkedListNode* const min_ll_node, std::unordered_map<LinkedListNode*, FTNode*> map_node_ll2ft){
    if((map_weight[candidate_parent].find(min_ll_node) != map_weight[candidate_parent].end()) && (edge_weight == map_node_ll2ft[min_ll_node]->GetKey())){
        return true;
    }else{
        return false;
    }
}
void Kruskal_Algorithm::FindMST(Fibonacci_Heap &fib_heap_q, std::vector<MST_Edge*> &final_mst, std::unordered_map<FTNode*, LinkedListNode*> &map_node_ft2ll, std::unordered_map<std::string, LinkedListNode*> &map_node_st2ll, std::unordered_map<LinkedListNode*, FTNode*> map_node_ll2ft, AdjList &adj_list){
    std::unordered_map<LinkedListNode*, std::unordered_map<LinkedListNode*, int>> map_weight = adj_list.ReadMapWeight();

    while(fib_heap_q.GetTotalNodeNum() != 0){
        //Extractmin from the Fibonacci_Heap
        FTNode* min_ft_node = fib_heap_q.ExtractMin();
        LinkedListNode* min_ll_node = map_node_ft2ll[min_ft_node];

        //Inserted the MST edge to final_mst
        if(final_mst.size() == 0){
            MST_Edge* inserted_edge = new MST_Edge(NULL, min_ll_node, 0);
            final_mst.push_back(inserted_edge);
        }else{
            for(std::vector<MST_Edge*>::reverse_iterator i = final_mst.rbegin(); i!=final_mst.rend(); ++i){
                LinkedListNode* candidate_parent = (*i)->RetEdgeB();
                int edge_weight = map_weight[candidate_parent][min_ll_node];
                if(CheckIsTheEdge(map_weight, candidate_parent, edge_weight, min_ll_node, map_node_ll2ft)){
                    MST_Edge* inserted_edge = new MST_Edge(candidate_parent, min_ll_node, edge_weight);
                    final_mst.push_back(inserted_edge);
                    break;
                }
            }
        }
        
        if(fib_heap_q.GetTotalNodeNum() != 0){
            //Decrease all the adjacent node with the value of edge weight
            LinkedList* the_linked_list = adj_list.ReadAdjList(min_ll_node);
            LinkedListNode* current_node = the_linked_list->GetFristNode();
            while(current_node != NULL){
                LinkedListNode* node_to_decrease_ll = map_node_st2ll[current_node->GetName()];
                FTNode* node_to_decrease = map_node_ll2ft[node_to_decrease_ll];
                fib_heap_q.DecreaseKey(node_to_decrease, map_weight[min_ll_node][node_to_decrease_ll]);
                current_node = current_node->GetNext();
            }
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
