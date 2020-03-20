#include <iostream>
#include <vector>
#include <stack>

#define MIN(a,b) ({ a < b ? a : b; })
#define MAX(a,b) ({ a > b ? a : b; })

class Node {
    public:
    int id;
    int low;
    int first_grade;
    bool visited = false;
    bool on_stack = false;
    int scc;
    std::vector<Node*> friends;

    Node(int i, int g): id(i), low(i), first_grade(g){}
    void add_friend(Node* f){ friends.push_back(f);}
};

class SCC {
    public:
    int id;
    int max_score;
    bool visited = false;
    bool scc_visited = false;
    std::vector<Node*> nodes;
    std::vector<SCC*> neighbours;

    SCC(int i): id(i){}
};


class Graph {
    public:
    std::vector<Node*> students;
    std::vector<SCC*> sccs;
    std::stack<Node*> stack;
    std::stack<SCC*> scc_stack;

    void dfs(Node* s){
        s->visited = true;
        stack.push(s);
        int max = 0;
        Node* top;
        s->on_stack = true;
        for (Node* student : s->friends){
            if (student->visited == false) { //if not visited
                this->dfs(student);
            }
            if (student->on_stack){
                s->low = MIN(student->low, s->low);
            }
        }
    
        if (s->id == s->low){ //arrived to the first element, new scc
            int scc_id = sccs.size();
            SCC* scc = new SCC(scc_id);
            sccs.push_back(scc);
            while( (top = stack.top())->id != s->id ){
                top->on_stack=false;
                top->low = s->low;
                top->scc = scc_id;
                max = MAX(top->first_grade, max);
                scc->nodes.push_back(top); //add the nodes to scc
                stack.pop();
            }
            max = MAX(top->first_grade, max);
            scc->nodes.push_back(top); // add the last node to scc
            s->on_stack=false;
            top->scc = scc_id;
            stack.pop();
            scc->max_score = max;
        }
    }

    void scc_dfs(SCC* scc){
        //aqui fazer set das notas finais
        int last;
        SCC* top;
        scc_stack.push(scc);
        for (SCC* s : scc->neighbours){
            this->scc_dfs(s); //there are not cycles
        }
        //there is only one pop as there are no cycles
        last = scc_stack.top()->max_score;
        scc_stack.pop();
        top = scc_stack.top();
        if (!scc_stack.empty()){
            scc_stack.top()->max_score = MAX(top->max_score, last);
        }
    }
};



int main(int argc, char const *argv[]){
    int n, m;
    int grade;
    int s1, s2;
    scanf("%d , %d", &n, &m);

    Graph* g = new Graph();


    int i = 1;
    while (i <= n){ //read students
        scanf("%d", &grade);
        g->students.push_back(new Node(i,grade));
        i++;
    }

    while (m){ //read friendships
        m--;
        scanf("%d %d", &s1, &s2);
        g->students.at(s1-1)->add_friend(g->students.at(s2-1));
    }

    //Start DFS
    for (Node* student : g->students){
        if (student->visited == false) { //if not visited
            g->dfs(student);
        }
    }

    //verify which scc are connected
    for(SCC* scc: g->sccs){
        for(Node* s: scc->nodes){
            for(Node* f: s->friends){
                if (g->sccs.at(f->scc)->visited) continue;
                if(s->scc != f->scc){   
                    g->sccs.at(f->scc)->visited = true;
                    scc->neighbours.push_back(g->sccs.at(f->scc));
                }
            }
        }
    }

    printf("SCC: %lu\n", g->sccs.size());

    for(SCC* scc: g->sccs){
        for(SCC* s: scc->neighbours){
             printf("[%d]---->[%d]\n", scc->id, s->id );
        } 
    }

    for(SCC* scc: g->sccs){
        if (scc->scc_visited == false){
            g->scc_dfs(scc);
            scc->scc_visited = true;
        }
    }

    for(SCC* scc: g->sccs){
        printf("[%d]: [%d]\n", scc->id, scc->max_score);
    }



    return 0;
}
