#include "./nthu_bike.h"
#include <iostream>
#include <fstream>
#include <math.h>

#define MAX_INT 999999
#define BIKE_MAX 10000
#define STATION_MAX 1000

using namespace std;


//global variable
float disc_prc;
int rent_cnt_lim;
float* bike_initial_price;


int min_distance(int dist[], bool visited[], int n)
{
    int min = MAX_INT, min_index;
    for (int v = 0; v < n; v++)
    {
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    }

    return min_index;
}

// void print_solution(int dist[], int n)
// {
//     cout <<"Vertex \t Distance from Source" << endl;
//     for (int i = 0; i < n ; i++)
//         cout  << i << " \t\t"<<dist[i]<< endl;
// }

int *dijkstra(int graph[STATION_MAX][STATION_MAX], int src, int n)
{
    int *dist = new int[n];
    bool *visited = new bool[n];
    // initialize all nodes to be unvisited and all distance to MAX_INT
    for (int i = 0; i < n; i++)
        dist[i] = MAX_INT, visited[i] = false;

    dist[src] = 0;

    // find n-1 shortest path for all vertices
    for (int count = 0; count < n - 1; count++)
    {
        // pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = min_distance(dist, visited, n);
        // mark the picked vertex as visited
        visited[u] = true;

        // update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < n; v++)
            // update dist[v] only if is not in visited, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!visited[v] && graph[u][v] && dist[u] != 100000 && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    return dist;
}

template <class T>
class StackNode {
    private:
    public:
        T data;
        StackNode<T>* next;
        
        StackNode(T n) {
            data = n;
            next = NULL;
        }
};

//Stack class
template <class T> 
class Stack {
    // Public access modifier
    public:
        // Empty constructor
        Stack() {
            top = NULL;
        };
    
        // Method 1
        // To add element to stack which can be any type
        // using stack push() operation
        void push(T k) {
            if (isFull()) {
                // Display message when no elements can be pushed
                // into it
                cout << "Stack is full\n";
            }

            StackNode<T>* temp = new StackNode<T>(k);
            // Incrementing the top by unity as element
            // is to be inserted
            temp->next = top;
        
            // Now, adding element to stack
            top = temp;
        };
    
        void pop() {
            StackNode<T>* temp;
            
            // Decreasing the top as
            // element is getting out from the stack
            if(top != NULL) {
                temp = top;
                top = top->next;

                // free(temp);
            }
        
        };

        T topElement() {
            if(isEmpty()) return NULL;
            // Returning the top element
            return top->data;
        };
    
        
        bool isFull() {
            return 0;
        }

        bool isEmpty() {
            return top == NULL;
        };
    
    private:
        // Taking data member top
        StackNode<T>* top;
};

template <class T>
class ListNode {
    private:
    public:
        ListNode<T>* next; 
        T data;
        ListNode(T data) {
            this->data = data;
            next = NULL;
        }
};

template <class T>
class LinkedList {
    private:
    public:
        ListNode<T> *head;
        ListNode<T> *tail;
        int len;
        LinkedList(ListNode<T>* root) {
            head = root;
            tail = root;
            if(root == NULL) {
                len = 0;
            }
            else {
                len = 1;;
            }
        }

        void insert_node(ListNode<T>* newNode) {
            len++;
            if(head == NULL) {
                head = newNode;
                tail = newNode;
                tail->next = NULL;
                return;
            }
            tail->next = newNode;
            tail = newNode;
            tail->next = NULL;
        }

        ListNode<T>* get_head() {
            return head;
        }

        void print_list() {
            ListNode<T>* curr = head;
            while(curr) {
                std::cout << curr->data << " ";
                curr = curr->next;
            }
        }
};

template <class T>
class LinkedListIterator {
    private:
        ListNode<T>* current;
    public:
        LinkedListIterator(ListNode<T>* head) {
            current = head;
        }

        bool hasNext() {
            if(current->next == NULL) return false;
            else return true;
        }

        ListNode<T>* next() {
            if(current == NULL) return NULL;

            ListNode<T>* temp = current;
            current = current->next;

            return temp;     
        }
};


class BikeNode
{
    friend class StationNode;
    friend class BikeInorderIterator;
    // friend StationBST
private:

public:
    BikeNode *left;
    BikeNode *right;
    string bike_type;
    int bike_type_int;
    int bike_id;
    float rental_price; // dollars per minute
    int rental_count;
    int bike_start_time;
    int bike_end_time;

    BikeNode(string b_ty, int b_id, float rent_p, int rent_c)
    {
        bike_type = b_ty;

        string temp;
        for (int i = 1; i < bike_type.length(); i++)
        {
            temp.push_back(bike_type[i]);
        }
        bike_type_int = stoi(temp);

        bike_id = b_id;
        // station_id = st_id;
        rental_price = rent_p;
        rental_count = rent_c;
        bike_start_time = -1;
        bike_end_time = -1;
        left = NULL;
        right = NULL;
    }
};

class BikeInorderIterator {
    private:
        Stack<BikeNode*> traversal;
    
    public:
        BikeInorderIterator(BikeNode* root)
        {
            moveLeft(root);
        }
    
        void moveLeft(BikeNode* current)
        {
            while (current) {
                traversal.push(current);
                current = current->left;
            }
        }
    
        bool hasNext()
        {
            return !traversal.isEmpty();
        }
    
        BikeNode* next()
        {
            if (!hasNext())
                return NULL;
    
            BikeNode* current = traversal.topElement();
            traversal.pop();
    
            if (current->right)
                moveLeft(current->right);
    
            return current;
        }
};

class StationNode {
    friend class StationBST;
    friend class StationInorderIterator;

    private:
        string station_id;  // ex: s11
        int station_id_num; // ex: 11
        StationNode *left;
        StationNode *right;

    public:
        BikeNode *bike_bst_root;
        StationNode(string st_id)
        {
            station_id = st_id;
            string temp;
            for (int i = 1; i < st_id.length(); i++)
            {
                temp.push_back(st_id[i]);
            }
            station_id_num = stoi(temp);
            left = NULL;
            right = NULL;
        }
        // insert bike with the station's bike_bst_root as root
        void insert_bike(BikeNode * const bike)
        {
            if (!bike_bst_root)
            {
                // Insert the first node, if root is NULL.
                bike_bst_root = bike;
                return;
            }
            BikeNode *prev = NULL;
            BikeNode *temp = bike_bst_root;
            while (temp)
            {
                if (temp->bike_id > bike->bike_id)
                {
                    prev = temp;
                    temp = temp->left;
                }
                else if (temp->bike_id < bike->bike_id)
                {
                    prev = temp;
                    temp = temp->right;
                }
                else {
                    return;
                }
            }

            if (prev->bike_id > bike->bike_id)
            {
                prev->left = bike;
            }
            else
            {
                prev->right = bike;
            }
        }

    //search bike by id
    BikeNode* search_bike_byid(int b_id)
    {
        BikeNode *curr = bike_bst_root;
        while (curr != NULL)
        {
            if (b_id < curr->bike_id)
            {
                curr = curr->left;
            }
            else if (b_id > curr->bike_id)
            {
                curr = curr->right;
            }
            else
            {
                return curr;
            }
        }
        return NULL;
    }

    //search bike by type
    BikeNode* search_bike_byty(int b_ty_int) {
        Stack<BikeNode*> s;
        BikeNode *curr = bike_bst_root;
    
        while (curr != NULL || s.isEmpty() == 0)
        {
            /* Reach the left most Node of the
            curr Node */
            while (curr !=  NULL)
            {
                /* place pointer to a tree node on
                the stack before traversing
                the node's left subtree */
                s.push(curr);
                curr = curr->left;
            }
    
            /* Current must be NULL at this point */
            curr = s.topElement();
            s.pop();
    
            if(curr->bike_type_int == b_ty_int) {
                return curr;
            }
    
            /* we have visited the node and its
            left subtree.  Now, it's right
            subtree's turn */
            curr = curr->right;
        }

        //not found
        return NULL;
    }

    // used for rec_remove_bike()
    BikeNode* min_value_node(BikeNode *node)
    {
        BikeNode *current = node;

        // loop down to find the leftmost leaf
        while (current && current->left != NULL) {
            current = current->left;
        }

        return current;
    }
    // called by remove_bike()
    BikeNode* rec_remove_bike(BikeNode *root, int key)
    {
        // base case
        if (root == NULL)
            return root;

        // If the key to be deleted is
        // smaller than the root's
        // key, then it lies in left subtree
        if (key < root->bike_id)
            root->left = rec_remove_bike(root->left, key);

        // If the key to be deleted is
        // greater than the root's
        // key, then it lies in right subtree
        else if (key > root->bike_id)
            root->right = rec_remove_bike(root->right, key);

        // if key is same as root's key, then This is the node
        // to be deleted
        else
        {
            // node has no child
            if (root->left == NULL and root->right == NULL)
                return NULL;

            // node with only one child or no child
            else if (root->left == NULL)
            {
                BikeNode *temp = root->right;
                root->right = NULL;
                // free(root);
                return temp;
            }
            else if (root->right == NULL)
            {
                BikeNode *temp = root->left;
                root->left = NULL;
                // free(root);
                return temp;
            }

            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
            BikeNode *temp = min_value_node(root->right);

            // BikeNode *save = new BikeNode(root->bike_type, root->bike_id, root->rental_price, root->rental_count);
            // save->bike_type_int = root->bike_type_int;
            // save->bike_start_time = root->bike_start_time;
            // save->bike_end_time = root->bike_end_time;

            // Copy the inorder successor's content to this node
            root->bike_id = temp->bike_id;
            root->bike_type = temp->bike_type;
            root->bike_type_int = temp->bike_type_int;
            root->bike_start_time = temp->bike_start_time;
            root->bike_end_time = temp->bike_end_time;
            root->rental_price = temp->rental_price;
            root->rental_count = temp->rental_count;

            // temp->bike_id = save->bike_id;
            // temp->bike_type = save->bike_type;
            // temp->bike_type_int = save->bike_type_int;
            // temp->bike_start_time = save->bike_start_time;
            // temp->bike_end_time = save->bike_end_time;
            // temp->rental_price = save->rental_price;
            // temp->rental_count = save->rental_count;

            // Delete the inorder successor
            root->right = rec_remove_bike(root->right, temp->bike_id);
        }
        return root;
    }
    // called by main function, call rec_remove_bike()
    void remove_bike(int b_id)
    {
        bike_bst_root = rec_remove_bike(bike_bst_root, b_id);
    }

    // call the rec_inorder_print()
    void inorder_print(std::ofstream& dumFile)
    {
        rec_inorder_print(bike_bst_root, dumFile);
    }
    void rec_inorder_print(BikeNode *root, std::ofstream& dumFile)
    {
        if (root != NULL)
        {
            rec_inorder_print(root->left, dumFile);
            dumFile << station_id << " " << root->bike_id << " " << root->bike_type << " " << root->rental_price << " " << root->rental_count<< endl;
            rec_inorder_print(root->right, dumFile);
        }
    }
};

class StationBST
{
friend class StationInorderIterator;
private:
    StationNode *station_bst_root;

public:
    StationBST(StationNode *root)
    {
        station_bst_root = root;
    };

    // insert station with station_bst_root as the root
    void insert_station(StationNode *station)
    {
        if (!station_bst_root)
        {
            // Insert the first node, if root is NULL.
            station_bst_root = station;
            return;
        }
        StationNode *prev = NULL;
        StationNode *temp = station_bst_root;
        while (temp)
        {
            if (temp->station_id_num > station->station_id_num)
            {
                prev = temp;
                temp = temp->left;
            }
            else if (temp->station_id_num < station->station_id_num)
            {
                prev = temp;
                temp = temp->right;
            }
            else {
                return;
            }
        }
        if (prev->station_id_num > station->station_id_num)
        {
            prev->left = station;
        }
        else
        {
            prev->right = station;
        }
    }

    StationNode* search_station(int s_id_num)
    {
        StationNode *curr = station_bst_root;
        while (curr != NULL)
        {
            if (s_id_num < curr->station_id_num)
            {
                curr = curr->left;
            }
            else if (s_id_num > curr->station_id_num)
            {
                curr = curr->right;
            }
            else
            {
                return curr;
            }
        }
        return 0;
    }

    // called by main, call rec_inorder_print()
    void inorder_print(std::ofstream& dumFile)
    {
        rec_inorder_print(station_bst_root, dumFile);
    }
    void rec_inorder_print(StationNode *root, std::ofstream& dumFile)
    {
        if (root != NULL)
        {
            rec_inorder_print(root->left, dumFile);
            root->inorder_print(dumFile);
            rec_inorder_print(root->right, dumFile);
        }
    }
};

class StationInorderIterator {
    private:
        Stack<StationNode*> traversal;

    public:
        StationInorderIterator(StationNode* root)
        {
            moveLeft(root);
        }
    
        void moveLeft(StationNode* current)
        {
            while (current) {
                traversal.push(current);
                current = current->left;
            }
        }
    
        bool hasNext()
        {
            return !traversal.isEmpty();
        }
    
        StationNode* next()
        {
            if (!hasNext())
                return NULL;
    
            StationNode* current = traversal.topElement();
            traversal.pop();
    
            if (current->right)
                moveLeft(current->right);
    
            return current;
        }

};

//to store status of all requests
class UserNode {
    // friend class UserBST;
    // friend class UserInorderIterator;
    // private:
    public:
        string user_id_str;
        int user_id_int;
        int decision;
        ListNode<int>* all_acc_bike;
        int bike_id;
        int acc_start_time;
        int acc_end_time;
        int ride_start_time;
        int ride_end_time;
        int revenue;
        int start_point_int;
        int end_point_int;
        UserNode* left;
        UserNode* right;
        UserNode(string u_id_str, int deci, int b_id, int r_str_t, int r_end_t, int rev) {
            user_id_str = u_id_str;

            string temp;
            for(int i = 1; i < user_id_str.length(); i++) {
                temp.push_back(user_id_str[i]);
            }
            user_id_int = stoi(temp);
            decision = deci;
            bike_id = b_id;
            ride_start_time = r_str_t;
            ride_end_time = r_end_t;
            revenue = rev;
            left = NULL;
            right = NULL;
        }
    
        void print_data() {
            // std::cout << user_id_str << " " << decision << " " << bike_id << " "
            // << ride_start_time << " " << ride_end_time << " " << revenue << endl;
            std::cout << user_id_str << " " << 0 <<  " " << acc_start_time << " " << acc_end_time 
            << " " << start_point_int << " "  << end_point_int << endl;
        }

        void set_all_acc_bike(ListNode<int>* all_acc_b) {
            all_acc_bike = all_acc_b;
        }

        void set_acc_st_time(int acc_st_t) {
            acc_start_time = acc_st_t;
        }

        void set_acc_end_time(int acc_end_t) {
            acc_end_time = acc_end_t;
        }

        void set_st_end_point(int st_p, int end_p) {
            start_point_int = st_p;
            end_point_int = end_p;
        }
};

//UserNode BST
class UserBST {
    private:
        UserNode* user_bst_root;
        
    public:
        UserBST(UserNode* root) {
            user_bst_root = root;
        }

        UserNode* get_root() {
            return user_bst_root;
        }

        // called by main, call rec_inorder_print()
        void inorder_print() {
            rec_inorder_print(user_bst_root);
        }
        void rec_inorder_print(UserNode *root) {
            if (root != NULL)
            {
                rec_inorder_print(root->left);
                root->print_data();
                rec_inorder_print(root->right);
            }
        }

        void insert_user_st_t(UserNode* user) {
            if (!user_bst_root)
            {
                // Insert the first node, if root is NULL.
                user_bst_root = user;
                return;
            }
            UserNode *prev = NULL;
            UserNode *temp = user_bst_root;
            while (temp)
            {
                if (temp->acc_start_time > user->acc_start_time)
                {
                    prev = temp;
                    temp = temp->left;
                }
                else if (temp->acc_start_time < user->acc_start_time)
                {
                    prev = temp;
                    temp = temp->right;
                }
                else {
                    while(temp->right && temp->right->acc_start_time == user->acc_start_time) {
                        temp = temp->right;
                    }
                    user->right = temp->right;
                    temp->right = user;
                    return;
                }
            }
            if (prev->acc_start_time > user->acc_start_time)
            {
                prev->left = user;
            }
            else
            {
                prev->right = user;
            }
        }

        void insert_user_us_id(UserNode* user) {
            if (!user_bst_root)
            {
                // Insert the first node, if root is NULL.
                user_bst_root = user;
                return;
            }
            UserNode *prev = NULL;
            UserNode *temp = user_bst_root;
            while (temp)
            {
                if (temp->user_id_int > user->user_id_int)
                {
                    prev = temp;
                    temp = temp->left;
                }
                else if (temp->user_id_int < user->user_id_int)
                {
                    prev = temp;
                    temp = temp->right;
                }
                else {
                    while(temp->right && temp->right->user_id_int == user->user_id_int) {
                        temp = temp->right;
                    }
                    user->right = temp->right;
                    temp->right = user;
                    return;
                }
            }
            if (prev->user_id_int > user->user_id_int)
            {
                prev->left = user;
            }
            else
            {
                prev->right = user;
            }
        }

        // UserNode* search_user_byid(int u_id)
        // {
        //     Stack<UserNode*> s;
        //     UserNode *curr = user_bst_root;
        
        //     while (curr != NULL || s.isEmpty() == 0)
        //     {
        //         /* Reach the left most Node of the
        //         curr Node */
        //         while (curr !=  NULL)
        //         {
        //             /* place pointer to a tree node on
        //             the stack before traversing
        //             the node's left subtree */
        //             s.push(curr);
        //             curr = curr->left;
        //         }
        
        //         /* Current must be NULL at this point */
        //         curr = s.topElement();
        //         s.pop();
        
        //         if(curr->bike_type_int == b_ty_int) {
        //             return curr;
        //         }
        
        //         /* we have visited the node and its
        //         left subtree.  Now, it's right
        //         subtree's turn */
        //         curr = curr->right;
        //     }

        //     //not found
        //     return NULL;
        // }

};  

class UserInorderIterator {
    private:
        Stack<UserNode*> traversal;
    
    public:
        UserInorderIterator(UserNode* root)
        {
            moveLeft(root);
        }
    
        void moveLeft(UserNode* current)
        {
            while (current) {
                traversal.push(current);
                current = current->left;
            }
        }
    
        bool hasNext()
        {
            return !traversal.isEmpty();
        }
    
        UserNode* next()
        {
            if (!hasNext())
                return NULL;
    
            UserNode* current = traversal.topElement();
            traversal.pop();
    
            if (current->right)
                moveLeft(current->right);
    
            return current;
        }
};


// transfer_log


void basic(string selectedCase) {
// int main() {
    std::cout << "starting basic..." << endl;
    // // insert your code here
    // cout << "start your basic version of data structure final from here!" << endl;

    float TOTAL_REVENUE = 0;

    // MAP
    //  Read from the text file
    int total_edge = 0;
    int MAP[STATION_MAX][STATION_MAX] = {0};
    int max = 0;

    ifstream FILE_map("./testcases/"+selectedCase+"/map.txt");
    if (!FILE_map.is_open())
    {
        cerr << "map.txt not found" << endl;
        exit(0);
    }
    string src_station;
    string dest_station;
    string distance_str;
    while (FILE_map.good())
    {
        // read line
        FILE_map >> src_station >> dest_station >> distance_str;

        // convert to int
        string temp1;
        for (int i = 1; i < src_station.length(); i++)
        {
            temp1.push_back(src_station[i]);
        }
        int src_station_num = stoi(temp1);

        string temp2;
        for (int i = 1; i < dest_station.length(); i++)
        {
            temp2.push_back(dest_station[i]);
        }
        int dest_station_num = stoi(temp2);

        int distance_int = stoi(distance_str);

        // write to MAP
        MAP[src_station_num][dest_station_num] = distance_int;
        MAP[dest_station_num][src_station_num] = distance_int;

        if (max < src_station_num)
            max = src_station_num;
        if (max < dest_station_num)
            max = dest_station_num;
    }

    FILE_map.close();
    std::cout << "MAP is done." << endl;

    // cout<<"max: "<<max<<endl;
    // Check map.txt
    // for(int i=0;i<=max;i++){
    //     for(int j=0;j<=max;j++){
    //         cout<<MAP[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    int **sp_table = new int *[max + 1]; // spt_table used to store the shortest path from one station to another stations
    for (int i = 0; i <= max; i++)
    {
        sp_table[i] = new int[max + 1];
    }

    for (int i = 0; i <= max; i++)
    {
        sp_table[i] = dijkstra(MAP, i, max + 1);
    }
    std::cout << "SP_TABLE is done." << endl;
    // auto stop = high_resolution_clock::now();

    /*
        to check if SP_table is the shortest
    */
    // for(int i=0; i<=max;i++){
    //     for(int j=0;j<=max;j++){
    //         cout<<sp_table[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    // initialize StationBST
    StationBST StationTree(NULL);

    // BIKE
    ifstream FILE_bike("./testcases/"+selectedCase+"/bike.txt");
    if (!FILE_bike.is_open())
    {
        cerr << "bike.txt not found." << endl;
        exit(0);
    }


    string bike_type_str;
    int bike_type_int;
    string bike_id_str;
    int bike_id_int;
    string station_id_str;
    int station_id_int;
    string rental_price_str;
    float rental_price_flt;
    string rental_count_str;
    int rental_count_int;
    string last_bike_id_str;
    StationNode* inserted_station = NULL;
    BikeNode* inserted_bike = NULL;

    int bike_type_max = 0;

    while (FILE_bike.good())
    {
        // read line
        FILE_bike >> bike_type_str >> bike_id_str >> station_id_str >> rental_price_str >> rental_count_str;

        if(bike_id_str == last_bike_id_str) break;

        // convert to int
        string temp1;
        for(int i = 1; i < bike_type_str.length(); i++) {
            temp1.push_back(bike_type_str[i]);
        }
        bike_type_int = stoi(temp1);
        if(bike_type_int > bike_type_max) {
            bike_type_max = bike_type_int;
        }

        bike_id_int = stoi(bike_id_str);

        string temp2;
        for (int i = 1; i < station_id_str.length(); i++)
        {
            temp2.push_back(station_id_str[i]);
        }
        station_id_int = stoi(temp2);

        rental_price_flt = stof(rental_price_str);

        rental_count_int = stoi(rental_count_str);

        // initialize and insert StationNode to StationBST
        inserted_station = new StationNode(station_id_str);
        StationTree.insert_station(inserted_station);

        // initialize and insert BikeNode according to its station_id
        inserted_bike = new BikeNode(bike_type_str, bike_id_int, rental_price_flt, rental_count_int);

        StationNode *curr_station;
        curr_station = StationTree.search_station(station_id_int);
        curr_station->insert_bike(inserted_bike);

        last_bike_id_str = bike_id_str;
    }
    // StationTree.inorder_print();

    FILE_bike.close();
    std::cout << "BIKE is done." << endl;





    bike_initial_price = new float[bike_type_max];

    // BIKE INFO
    ifstream FILE_bike_info("./testcases/"+selectedCase+"/bike_info.txt");
    if (!FILE_bike_info.is_open())
    {
        cerr << "bike_info.txt not found." << endl;
        exit(0);
    }
    else
    {
        string disc_prc_str;
        string rent_cnt_lim_str;
        if(FILE_bike_info.good()) {
            FILE_bike_info >> disc_prc_str;
            disc_prc = stof(disc_prc_str);
        }
        if(FILE_bike_info.good()) {
            FILE_bike_info >> rent_cnt_lim_str;
            rent_cnt_lim = stoi(rent_cnt_lim_str);
        }
        string bike_type_str;
        int bike_type_int;
        string initial_price_str;
        int initial_price_flt;
        while (FILE_bike_info.good())
        {
            // read line
            FILE_bike_info >> bike_type_str >> initial_price_str;

            //convert to int
            string temp;
            for(int i = 1; i < bike_type_str.length(); i++) {
                temp.push_back(bike_type_str[i]);
            }
            bike_type_int = stoi(temp);

            initial_price_flt = stof(initial_price_str);

            bike_initial_price[bike_type_int] = initial_price_flt;
            // std::cout << bike_type_int << " " << initial_price_int << endl;

        }
    }
    // std::cout << disc_prc << " " << rent_cnt_lim;


    FILE_bike_info.close();
    std::cout << "BIKE INFO is done." << endl;





    // USER
    ifstream FILE_user("./testcases/"+selectedCase+"/user.txt");
    if (!FILE_user.is_open())
    {
        cerr << "user.txt not found." << endl;
        exit(0);
    }
    else
    {   
        string user_id_str;
        int user_id_int;
        string acc_bike_type_str;
        ListNode<int>* all_acc_bike;
        string acc_start_time_str;
        int acc_start_time_int;
        string acc_end_time_str;
        int acc_end_time_int;
        string start_point_str;
        int start_point_int;
        string end_point_str;
        int end_point_int;
        string last_user_id_str;

        UserBST ST_UserTree(NULL);

        while (FILE_user.good())
        {
            // read line
            FILE_user >> user_id_str >> acc_bike_type_str >> acc_start_time_str >> acc_end_time_str
            >> start_point_str >> end_point_str;

            if(user_id_str == last_user_id_str) break;
            last_user_id_str = user_id_str;
            // cout << user_id_str << " " << acc_bike_type_str << " " << acc_start_time_str << " " << acc_end_time_str <<
            // " " << start_point_str << " " << end_point_str << endl;

            //convert to int
            string temp;
            for(int i = 1; i < user_id_str.length(); i++) {
                temp.push_back(user_id_str[i]);
            }
            user_id_int = stoi(temp);

            //acc_bike_type can be more than 1!!
            string all_acc_bike_str[1000] = {};
            int acc_bike_num = 1;

            string delim = ","; // delimiter
            size_t pos = 0;
            string token; // define a string variable

            // use find() function to get the position of the delimiters
            while ((pos = acc_bike_type_str.find (delim)) != std::string::npos)
            {
                token = acc_bike_type_str.substr(0, pos); // store the substring
                all_acc_bike_str[acc_bike_num - 1] = token;
                acc_bike_type_str.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
                acc_bike_num++;
            }
            all_acc_bike_str[acc_bike_num - 1] = acc_bike_type_str; // it print last token of the string.
            
            //convert to int
            LinkedList<int> AccBikeList(NULL);
            ListNode<int>* inserted_node;
            temp = "";
            for(int i = 0; i < acc_bike_num; i++) {
                temp = "";
                 for(int j = 1; j < all_acc_bike_str[i].length(); j++) {
                    temp.push_back(all_acc_bike_str[i][j]);
                 }
                 inserted_node = new ListNode<int>(stoi(temp));
                 AccBikeList.insert_node(inserted_node);
            }
            // check input
            // for(int i = 0; i < acc_bike_num; i++) {
            //     std::cout << all_acc_bike_str[i] << " ";
            // }
            // AccBikeList.print_list();
            // std::cout << endl;

            acc_start_time_int = stoi(acc_start_time_str);
            acc_end_time_int = stoi(acc_end_time_str);

            temp = "";
            for(int i = 1; i < start_point_str.length(); i++) {
                temp.push_back(start_point_str[i]);
            }
            start_point_int = stoi(temp);

            temp = "";
            for(int i = 1; i < end_point_str.length(); i++) {
                temp.push_back(end_point_str[i]);
            }
            end_point_int = stoi(temp);

            // std::cout << user_id_int << " " << 0 << " " << acc_start_time_int << " "
            // << acc_end_time_int << " " << start_point_int << " " << end_point_int << endl;

            UserNode* insertedNode = new UserNode(user_id_str, -1, -1, -1,
            -1, -1);
            insertedNode->set_st_end_point(start_point_int, end_point_int);
            insertedNode->set_all_acc_bike(AccBikeList.get_head());
            insertedNode->set_acc_st_time(acc_start_time_int);
            insertedNode->set_acc_end_time(acc_end_time_int);
            ST_UserTree.insert_user_st_t(insertedNode);
            // cout << user_id_str << " " << 0 <<  " " << acc_start_time_int << " " << acc_end_time_int 
            // << " " << start_point_int << " "  << end_point_int << endl;
        }

        // ST_UserTree.inorder_print();

        FILE_user.close();
        std::cout << "READ USER is done." << endl;


        // // CHECK ITERATOR
        // LinkedListIterator<int> list_iterator(ST_UserTree.get_root()->right->all_acc_bike);
        // cout << ST_UserTree.get_root()->right->user_id_str << endl;
        // ListNode<int>* iter_data = list_iterator.next();
        // // BikeInorderIterator bike_iterator(StationTree.search_station(0)->bike_bst_root);
        // // BikeNode* first_iter_bike = bike_iterator.next();
        // // BikeNode* iter_bike = first_iter_bike;

        // while(iter_data != NULL) {
        //     cout << iter_data->data << " ";
        //     // iter_bike = first_iter_bike;
        //     // while(iter_bike != NULL) {
        //     //     cout << iter_bike->bike_type << " " << iter_bike->bike_id << " ";
        //     //     iter_bike = bike_iterator.next();
        //     // }
        //     iter_data = list_iterator.next();
        // }
        // std::cout << endl;




        //process according to inorder sequence

        UserInorderIterator user_iterator1(ST_UserTree.get_root());
        UserNode* current_user1 = user_iterator1.next();

        UserBST ID_UserTree(NULL);
        while (current_user1 != NULL)
        {
            // copy data from current_user
            user_id_str = current_user1->user_id_str;
            user_id_int = current_user1->user_id_int;
            all_acc_bike = current_user1->all_acc_bike;
            acc_start_time_int = current_user1->acc_start_time;
            acc_end_time_int = current_user1->acc_end_time;
            start_point_int = current_user1->start_point_int;
            end_point_int = current_user1->end_point_int;
            

            int distance = sp_table[start_point_int][end_point_int];

            // std::cout << user_id_str << " " << 0 << " " << acc_start_time_int << " "
            // << acc_end_time_int << " " << start_point_int << " " << end_point_int << endl;
            LinkedList<int> AllAccBike(all_acc_bike);
            // AllAccBike.print_list();
            // cout << endl;


            //get station
            StationNode* user_start_station = StationTree.search_station(start_point_int);
            StationNode* user_end_station = StationTree.search_station(end_point_int);
            
            //check if there is accepted bike in user_start_station
            
            // BikeNode* all_avail_bike[1000];
            LinkedList<BikeNode*> all_avail_bike(NULL);
            int avail_bike_num = 0;
            BikeNode* curr_bike = NULL;
            BikeNode* user_bike = NULL; //selected bike
            LinkedListIterator<int> list_iterator(all_acc_bike);
            ListNode<int>* iter_data = list_iterator.next();

            while(iter_data != NULL) {
                BikeInorderIterator bike_iterator(user_start_station->bike_bst_root);
                // BikeInorderIterator bike_iterator(StationTree.search_station(0)->bike_bst_root);
                BikeNode* iter_bike = bike_iterator.next();
                while(iter_bike != NULL) {
                    // cout << iter_bike->bike_type << " " << iter_bike->bike_id << " ";
                    if(iter_bike->bike_type_int == iter_data->data && iter_bike->rental_count < rent_cnt_lim) {
                        curr_bike = iter_bike;
                        // check
                        // std::cout << "Unfiltered: " << curr_bike->bike_type << " " << curr_bike->bike_id << " " << curr_bike->bike_end_time << " ";
                        
                        //user arrive first
                        if(acc_start_time_int < curr_bike->bike_end_time) {
                            curr_bike = NULL; //since user dont wait for bikes
                        }
                        //bike arrive first
                        else {
                            //arrive at or after acc_end_time
                            if(acc_start_time_int + distance >= acc_end_time_int) {
                                curr_bike = NULL;
                            }
                            //arrive before acc_end_time
                            else if(acc_start_time_int + distance < acc_end_time_int){
                                // std::cout << "Filtered: " << curr_bike->bike_type << " " << curr_bike->bike_id << " " << curr_bike->bike_end_time << " ";
                                // add to all_avail_bike array
                                ListNode<BikeNode*>* inserted_node = new ListNode<BikeNode*>(curr_bike);
                                all_avail_bike.insert_node(inserted_node);
                                avail_bike_num++;
                            }
                        }
                    }

                    iter_bike = bike_iterator.next();
                }
                
                iter_data = list_iterator.next();
            }
            // std::cout << endl;



            //if 1 or more bike is available
            if(avail_bike_num > 0) {
                //select user_bike with the highest rental price in all_avail_bike array
                ListNode<BikeNode*>* curr = all_avail_bike.get_head();
                user_bike = curr->data;
                float highest_rental_price = user_bike->rental_price;
                int highest_bike_id = user_bike->bike_id;
                while(curr != NULL) {
                    // if(acc_start_time_int < 100) {
                    //     cout << curr->data->bike_type << " id:" << curr->data->bike_id << " prc:" << curr->data->rental_price << ", ";
                    // }
                    if(curr->data->rental_price > highest_rental_price) {
                        user_bike = curr->data; //error when this is included
                        highest_rental_price = user_bike->rental_price;
                        highest_bike_id = user_bike->bike_id;
                    }
                    else if(curr->data->rental_price == highest_rental_price) {
                        if(curr->data->bike_id < highest_bike_id) {
                            user_bike = curr->data;
                            highest_bike_id = curr->data->bike_id;
                        }
                    }
                    curr = curr->next;
                }
                
            } 
            else {
                user_bike = NULL;
            }

            //check
            // if(user_bike != NULL && acc_start_time_int < 100) {
            //     cout << endl << "Highest: " << user_bike->bike_type << " " << user_bike->rental_price << endl;
            // }
            // else cout << endl;

            UserNode* inserted_user;
            //suitable bike not found
            if(user_bike == NULL) {
                inserted_user = new UserNode(user_id_str, 0, 0, 0, 0, 0);
                ID_UserTree.insert_user_us_id(inserted_user);
            }
            //suitable bike is found
            else {
                int user_revenue = floor(user_bike->rental_price * distance);//round down to integer
                inserted_user = new UserNode(user_id_str, 1, user_bike->bike_id, acc_start_time_int, 
                acc_start_time_int + distance, user_revenue);
                inserted_user->start_point_int = start_point_int;
                inserted_user->end_point_int = end_point_int;
                ID_UserTree.insert_user_us_id(inserted_user);


                //update everything

                //update revenue
                TOTAL_REVENUE += user_revenue;
                
                //update user_bike

                user_bike->bike_end_time = acc_start_time_int + distance;
                //rental count
                user_bike->rental_count++;
                //rental price
                user_bike->rental_price = round((bike_initial_price[user_bike->bike_type_int] - disc_prc * user_bike->rental_count) * 10 ) / 10; //round to 1 decimal place

                
                //copy user_bike data before removing it
                BikeNode *save = new BikeNode(user_bike->bike_type, user_bike->bike_id, user_bike->rental_price, user_bike->rental_count);
                save->bike_type_int = user_bike->bike_type_int;
                save->bike_start_time = user_bike->bike_start_time;
                save->bike_end_time = user_bike->bike_end_time;


                user_start_station->remove_bike(user_bike->bike_id);

                user_bike = save; 

                user_end_station->insert_bike(user_bike);
                
            }



            current_user1 = user_iterator1.next();
        }
        std::cout << "PROCESS USER is done." << endl;




        //user_resut file
        ofstream myfile2;
        myfile2.open("./result/"+selectedCase+"/user_result.txt");

        UserInorderIterator user_iterator2(ID_UserTree.get_root());
        UserNode* current_user2 = user_iterator2.next();
        while(current_user2) {
            // user_result
            myfile2 << current_user2->user_id_str << " " << current_user2->decision << " " 
            << current_user2->bike_id << " " << current_user2->ride_start_time << " " <<
            current_user2->ride_end_time << " " << current_user2->revenue << endl;

            current_user2 = user_iterator2.next();
        }
        std::cout << "USER_RESULT is done." << endl;
        myfile2.close();



        //transfer_log file
        ofstream myfile3;
        myfile3.open("./result/"+selectedCase+"/transfer_log.txt");

        UserInorderIterator user_iterator3(ID_UserTree.get_root());
        UserNode* current_user3 = user_iterator3.next();
        while(current_user3) {
            // transfer_log
            myfile3 << current_user3->bike_id << " S" << current_user3->start_point_int << " S" << current_user3->end_point_int << " " <<
            current_user3->ride_start_time <<  " " << current_user3->ride_end_time << " " << current_user3->user_id_str << endl;


            current_user3 = user_iterator3.next();
        }
        std::cout << "TRANSFER_LOG is done." << endl;
        myfile3.close();

    }


    ofstream myfile4;
    myfile4.open("./result/"+selectedCase+"/station_status.txt");
    StationTree.inorder_print(myfile4);
    myfile4.close();
    std::cout << "STATION_STATUS is done." << endl;


    std::cout << "ALL DONE." << endl;

}