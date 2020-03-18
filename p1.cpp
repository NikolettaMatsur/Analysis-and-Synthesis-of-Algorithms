#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

class Node{
    int id;
    int first_test_grade;
    int final_grade;
    int next = -1;
    int low = -1;
    int disc = -1;
    std::vector<Node*> friends;

    public:
    Node(int i,int g): id(i), first_test_grade(g) {}
    void set_final_grade(int g) { final_grade = g;}
    int get_final_grade() { return final_grade;}
    void set_next(int n) { next = n;}
    void add_friend(Node* f) { friends.push_back(f);}
    int get_first_test_grade() { return first_test_grade;}
    int get_id() { return id;}
    int get_disc() { return disc;}
    int get_friend() {
        if(++next > friends.size()) return -1;
        return friends.at(next)->get_id();
    }
    void visit(int d, int l) {
        disc = d;
        low = l;
    }
    
    //TEST 
    void print_friends() {
        std::cout << "FRIENDS OF: " << id << std::endl;
        for (std::vector<Node*>::iterator it = friends.begin() ; it != friends.end(); ++it)
            std::cout  << (*it)->get_id();
        std::cout << '\n';
    }
};

int main(int argc, char const *argv[]){
    int n, m;
    int grade;
    int s1, s2;
    std::vector<Node*> students;

    std::scanf("%d , %d", &n, &m);

    //TEST:
    // std::cout << "N:" << n << std::endl; //TODO remove
    // std::cout << "M:" << m << std::endl; //TODO remove

    if (n < 2) {
        std::cerr << "Têm de existir pelo menos 2 alunos." << std::endl;
        return 1;
    }

    if (m < 0) {
        std::cerr << "O número de amizades não pode ser negativo." << std::endl;
        return 1;
    }

    int i = 1;
    while (i <= n){ //read students
        std::scanf("%d", &grade);
        students.push_back(new Node(i,grade));
        i++;
    }

    //TEST:
    // for (std::vector<Node*>::iterator it = students.begin() ; it != students.end(); ++it)
    //     std::cout  << (*it)->get_first_test_grade() << std::endl;
    // std::cout << '\n';

    while (m){
        m--;
        std::scanf("%d %d", &s1, &s2);
        students.at(s1-1)->add_friend(students.at(s2-1));
    }

    //TEST:
    // for (std::vector<Node*>::iterator it = students.begin() ; it != students.end(); ++it)
    //     (*it)->print_friends();
    // std::cout << '\n';


    //Start DFS
    int time = 0;
    int low = 0;
    int next = 0;
    for (std::vector<Node*>::iterator it = students.begin() ; it != students.end(); ++it){
        if ((*it)->get_disc() < 0) { //if not visited
            (*it)->visit(time, low);
            //insert in stack
            while (next > -1){

            }
            low++;
        }
    }
    

    /* print results */
    // for (std::vector<Node*>::iterator it = students.begin() ; it != students.end(); ++it)
    //     std::cout << (*it)->get_final_grade() << std::endl;
    // std::cout << '\n';
    
    return 0;
}
