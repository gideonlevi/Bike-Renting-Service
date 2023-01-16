#include "./nthu_bike.h"
#include <iostream>
#include <fstream>
#include <math.h>

#define MAX_INT 999999
#define BIKE_MAX 10000
#define STATION_MAX 1000

using namespace std;


//global variable
float disc_prc2;
int rent_cnt_lim2;
float* bike_initial_price2;


int min_distance2(int dist[], bool visited[], int n)
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

int *dijkstra2(int graph[STATION_MAX][STATION_MAX], int src, int n)
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
        int u = min_distance2(dist, visited, n);
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
class StackNode2 {
    private:
    public:
        T data;
        StackNode2<T>* next;
        
        StackNode2(T n) {
            data = n;
            next = NULL;
        }
};

//Stack2 class
template <class T> 
class Stack2 {
    // Public access modifier
    public:
        // Empty constructor
        Stack2() {
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

            StackNode2<T>* temp = new StackNode2<T>(k);
            // Incrementing the top by unity as element
            // is to be inserted
            temp->next = top;
        
            // Now, adding element to stack
            top = temp;
        };
    
        void pop() {
            StackNode2<T>* temp;
            
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
        StackNode2<T>* top;
};

template <class T>
class ListNode2 {
    private:
    public:
        ListNode2<T>* next; 
        T data;
        ListNode2(T data) {
            this->data = data;
            next = NULL;
        }
};

template <class T>
class LinkedList2 {
    private:
    public:
        ListNode2<T> *head;
        ListNode2<T> *tail;
        int len;
        LinkedList2(ListNode2<T>* root) {
            head = root;
            tail = root;
            if(root == NULL) {
                len = 0;
            }
            else {
                len = 1;;
            }
        }

        void insert_node(ListNode2<T>* newNode) {
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

        ListNode2<T>* get_head() {
            return head;
        }

        void print_list() {
            ListNode2<T>* curr = head;
            while(curr) {
                std::cout << curr->data << " ";
                curr = curr->next;
            }
        }
};

template <class T>
class LinkedListIterator2 {
    private:
        ListNode2<T>* current;
    public:
        LinkedListIterator2(ListNode2<T>* head) {
            current = head;
        }

        bool hasNext() {
            if(current->next == NULL) return false;
            else return true;
        }

        ListNode2<T>* next() {
            if(current == NULL) return NULL;

            ListNode2<T>* temp = current;
            current = current->next;

            return temp;     
        }
};


class BikeNode2
{
    friend class StationNode2;
    friend class BikeInorderIterator2;
    // friend StationBST2
private:

public:
    BikeNode2 *left;
    BikeNode2 *right;
    string bike_type;
    int bike_type_int;
    int bike_id;
    float rental_price; // dollars per minute
    int rental_count;
    int bike_start_time;
    int bike_end_time;

    BikeNode2(string b_ty, int b_id, float rent_p, int rent_c)
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

class BikeInorderIterator2 {
    private:
        Stack2<BikeNode2*> traversal;
    
    public:
        BikeInorderIterator2(BikeNode2* root)
        {
            moveLeft(root);
        }
    
        void moveLeft(BikeNode2* current)
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
    
        BikeNode2* next()
        {
            if (!hasNext())
                return NULL;
    
            BikeNode2* current = traversal.topElement();
            traversal.pop();
    
            if (current->right)
                moveLeft(current->right);
    
            return current;
        }
};

class StationNode2 {
    friend class StationBST2;
    friend class StationInorderIterator2;

    private:
        string station_id;  // ex: s11
        int station_id_num; // ex: 11
        StationNode2 *left;
        StationNode2 *right;

    public:
        BikeNode2 *bike_bst_root;
        StationNode2(string st_id)
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
        void insert_bike(BikeNode2 * const bike)
        {
            if (!bike_bst_root)
            {
                // Insert the first node, if root is NULL.
                bike_bst_root = bike;
                return;
            }
            BikeNode2 *prev = NULL;
            BikeNode2 *temp = bike_bst_root;
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
    BikeNode2* search_bike_byid(int b_id)
    {
        BikeNode2 *curr = bike_bst_root;
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
    BikeNode2* search_bike_byty(int b_ty_int) {
        Stack2<BikeNode2*> s;
        BikeNode2 *curr = bike_bst_root;
    
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
    BikeNode2* min_value_node(BikeNode2 *node)
    {
        BikeNode2 *current = node;

        // loop down to find the leftmost leaf
        while (current && current->left != NULL) {
            current = current->left;
        }

        return current;
    }
    // called by remove_bike()
    BikeNode2* rec_remove_bike(BikeNode2 *root, int key)
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
                BikeNode2 *temp = root->right;
                root->right = NULL;
                // free(root);
                return temp;
            }
            else if (root->right == NULL)
            {
                BikeNode2 *temp = root->left;
                root->left = NULL;
                // free(root);
                return temp;
            }

            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
            BikeNode2 *temp = min_value_node(root->right);

            // BikeNode2 *save = new BikeNode2(root->bike_type, root->bike_id, root->rental_price, root->rental_count);
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
    void rec_inorder_print(BikeNode2 *root, std::ofstream& dumFile)
    {
        if (root != NULL)
        {
            rec_inorder_print(root->left, dumFile);
            dumFile << station_id << " " << root->bike_id << " " << root->bike_type << " " << root->rental_price << " " << root->rental_count<< endl;
            rec_inorder_print(root->right, dumFile);
        }
    }
};

class StationBST2
{
friend class StationInorderIterator2;
private:
    StationNode2 *station_bst_root;

public:
    StationBST2(StationNode2 *root)
    {
        station_bst_root = root;
    };

    // insert station with station_bst_root as the root
    void insert_station(StationNode2 *station)
    {
        if (!station_bst_root)
        {
            // Insert the first node, if root is NULL.
            station_bst_root = station;
            return;
        }
        StationNode2 *prev = NULL;
        StationNode2 *temp = station_bst_root;
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

    StationNode2* search_station(int s_id_num)
    {
        StationNode2 *curr = station_bst_root;
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
    void rec_inorder_print(StationNode2 *root, std::ofstream& dumFile)
    {
        if (root != NULL)
        {
            rec_inorder_print(root->left, dumFile);
            root->inorder_print(dumFile);
            rec_inorder_print(root->right, dumFile);
        }
    }
};

class StationInorderIterator2 {
    private:
        Stack2<StationNode2*> traversal;

    public:
        StationInorderIterator2(StationNode2* root)
        {
            moveLeft(root);
        }
    
        void moveLeft(StationNode2* current)
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
    
        StationNode2* next()
        {
            if (!hasNext())
                return NULL;
    
            StationNode2* current = traversal.topElement();
            traversal.pop();
    
            if (current->right)
                moveLeft(current->right);
    
            return current;
        }

};

//to store status of all requests
class UserNode2 {
    // friend class UserBST2;
    // friend class UserInorderIterator2;
    // private:
    public:
        string user_id_str;
        int user_id_int;
        int decision;
        ListNode2<int>* all_acc_bike;
        int bike_id;
        int ride_start_time;
        int acc_start_time;
        int acc_end_time;
        int ride_end_time;
        int revenue;
        int start_point_int;
        int end_point_int;
        UserNode2* left;
        UserNode2* right;
        UserNode2(string u_id_str, int deci, int b_id, int r_str_t, int r_end_t, int rev) {
            user_id_str = u_id_str;

            if(user_id_str == "-1") {
                user_id_int = -1;
            }
            else {
                string temp;
                for(int i = 1; i < user_id_str.length(); i++) {
                    temp.push_back(user_id_str[i]);
                }
                user_id_int = stoi(temp);
            }
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

        void set_all_acc_bike(ListNode2<int>* all_acc_b) {
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

//UserNode2 BST
class UserBST2 {
    private:
        UserNode2* user_bst_root;
        
    public:
        UserBST2(UserNode2* root) {
            user_bst_root = root;
        }

        UserNode2* get_root() {
            return user_bst_root;
        }

        // called by main, call rec_inorder_print()
        void inorder_print() {
            rec_inorder_print(user_bst_root);
        }
        void rec_inorder_print(UserNode2 *root) {
            if (root != NULL)
            {
                rec_inorder_print(root->left);
                root->print_data();
                rec_inorder_print(root->right);
            }
        }

        void insert_user_st_t(UserNode2* user) {
            if (!user_bst_root)
            {
                // Insert the first node, if root is NULL.
                user_bst_root = user;
                return;
            }
            UserNode2 *prev = NULL;
            UserNode2 *temp = user_bst_root;
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

        void insert_user_us_id(UserNode2* user) {
            if (!user_bst_root)
            {
                // Insert the first node, if root is NULL.
                user_bst_root = user;
                return;
            }
            UserNode2 *prev = NULL;
            UserNode2 *temp = user_bst_root;
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

        // UserNode2* search_user_byid(int u_id)
        // {
        //     Stack2<UserNode2*> s;
        //     UserNode2 *curr = user_bst_root;
        
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

class UserInorderIterator2 {
    private:
        Stack2<UserNode2*> traversal;
    
    public:
        UserInorderIterator2(UserNode2* root)
        {
            moveLeft(root);
        }
    
        void moveLeft(UserNode2* current)
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
    
        UserNode2* next()
        {
            if (!hasNext())
                return NULL;
    
            UserNode2* current = traversal.topElement();
            traversal.pop();
    
            if (current->right)
                moveLeft(current->right);
    
            return current;
        }
};


// transfer_log


void advanced(string selectedCase){
    // insert your code here
    // cout << "start your advanced version of data structure final from here!" << endl;
    std::cout << "starting advance..." << endl;

    float TOTAL_REVENUE = 0;

    // MAP
    //  Read from the text file
    int total_edge = 0;
    int MAP[STATION_MAX][STATION_MAX] = {0};
    int max_station = 0;

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

        if (max_station < src_station_num)
            max_station = src_station_num;
        if (max_station < dest_station_num)
            max_station = dest_station_num;
    }

    FILE_map.close();
    std::cout << "MAP is done." << endl;

    // cout<<"max_station: "<<max_station<<endl;
    // Check map.txt
    // for(int i=0;i<=max_station;i++){
    //     for(int j=0;j<=max_station;j++){
    //         cout<<MAP[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    int **sp_table = new int *[max_station + 1]; // spt_table used to store the shortest path from one station to another stations
    for (int i = 0; i <= max_station; i++)
    {
        sp_table[i] = new int[max_station + 1];
    }

    for (int i = 0; i <= max_station; i++)
    {
        sp_table[i] = dijkstra2(MAP, i, max_station + 1);
    }
    std::cout << "SP_TABLE is done." << endl;
    // auto stop = high_resolution_clock::now();

    /*
        to check if SP_table is the shortest
    */
    // for(int i=0; i<=max_station;i++){
    //     for(int j=0;j<=max_station;j++){
    //         cout<<sp_table[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    // initialize StationBST2
    StationBST2 StationTree(NULL);

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
    StationNode2* inserted_station = NULL;
    BikeNode2* inserted_bike = NULL;

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

        // initialize and insert StationNode2 to StationBST2
        inserted_station = new StationNode2(station_id_str);
        StationTree.insert_station(inserted_station);

        // initialize and insert BikeNode2 according to its station_id
        inserted_bike = new BikeNode2(bike_type_str, bike_id_int, rental_price_flt, rental_count_int);

        StationNode2 *curr_station;
        curr_station = StationTree.search_station(station_id_int);
        curr_station->insert_bike(inserted_bike);

        last_bike_id_str = bike_id_str;
    }
    // StationTree.inorder_print();

    FILE_bike.close();
    std::cout << "BIKE is done." << endl;





    bike_initial_price2 = new float[bike_type_max];

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
        string rent_cnt_lim2_str;
        if(FILE_bike_info.good()) {
            FILE_bike_info >> disc_prc_str;
            disc_prc2 = stof(disc_prc_str);
        }
        if(FILE_bike_info.good()) {
            FILE_bike_info >> rent_cnt_lim2_str;
            rent_cnt_lim2 = stoi(rent_cnt_lim2_str);
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

            bike_initial_price2[bike_type_int] = initial_price_flt;
            // std::cout << bike_type_int << " " << initial_price_int << endl;

        }
    }
    // std::cout << disc_prc2 << " " << rent_cnt_lim2;


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
        ListNode2<int>* all_acc_bike;
        string acc_start_time_str;
        int acc_start_time_int;
        string acc_end_time_str;
        int acc_end_time_int;
        string start_point_str;
        int start_point_int;
        string end_point_str;
        int end_point_int;
        string last_user_id_str;

        UserBST2 ST_UserTree(NULL);

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
            LinkedList2<int> AccBikeList(NULL);
            ListNode2<int>* inserted_node;
            temp = "";
            for(int i = 0; i < acc_bike_num; i++) {
                temp = "";
                 for(int j = 1; j < all_acc_bike_str[i].length(); j++) {
                    temp.push_back(all_acc_bike_str[i][j]);
                 }
                 inserted_node = new ListNode2<int>(stoi(temp));
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

            UserNode2* insertedNode = new UserNode2(user_id_str, -1, -1, -1,
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



        UserInorderIterator2 user_iterator1(ST_UserTree.get_root());
        UserNode2* current_user1 = user_iterator1.next();

        UserBST2 ID_UserTree(NULL);
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
            LinkedList2<int> AllAccBike(all_acc_bike);
            // AllAccBike.print_list();
            // cout << endl;


            //get station
            StationNode2* user_start_station = StationTree.search_station(start_point_int);
            StationNode2* user_end_station = StationTree.search_station(end_point_int);
            

            //check if there is accepted bike in user_start_station
            
            LinkedList2<BikeNode2*> all_avail_bike(NULL);
            int avail_bike_num = 0;
            BikeNode2* curr_bike = NULL;
            BikeNode2* user_bike = NULL; //selected bike
            LinkedListIterator2<int> list_iterator(all_acc_bike);
            ListNode2<int>* iter_data = list_iterator.next();

            while(iter_data != NULL) {
                BikeInorderIterator2 bike_iterator(user_start_station->bike_bst_root);
                // BikeInorderIterator2 bike_iterator(StationTree.search_station(0)->bike_bst_root);
                BikeNode2* iter_bike = bike_iterator.next();
                while(iter_bike != NULL) {
                    // cout << iter_bike->bike_type << " " << iter_bike->bike_id << " ";
                    if(iter_bike->bike_type_int == iter_data->data && iter_bike->rental_count < rent_cnt_lim2) {
                        curr_bike = iter_bike;
                        // check
                        // std::cout << "Unfiltered: " << curr_bike->bike_type << " " << curr_bike->bike_id << " " << curr_bike->bike_end_time << " ";
                        
                        //user arrive first
                        if(acc_start_time_int < curr_bike->bike_end_time) {
                            // curr_bike = NULL; //in basic user dont wait for bikes
                            if(curr_bike->bike_end_time + distance >= acc_end_time_int) {
                                curr_bike = NULL;
                            }
                            else {
                                ListNode2<BikeNode2*>* inserted_node = new ListNode2<BikeNode2*>(curr_bike);
                                all_avail_bike.insert_node(inserted_node);
                                avail_bike_num++;
                            }
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
                                ListNode2<BikeNode2*>* inserted_node = new ListNode2<BikeNode2*>(curr_bike);
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
                ListNode2<BikeNode2*>* curr = all_avail_bike.get_head();
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

            UserNode2* inserted_user;

            //suitable bike not found
            //use free bike transfer to move bike
            if(user_bike == NULL) {
                //find closest station
                int closest_st;
                int closest_dist = MAX_INT;
                int visit[max_station];
                for(int i = 0; i < max_station; i++) visit[i] = 0; //set visit to 0

                //while might still 來得及
                while(true) {
                    closest_dist = MAX_INT;
                    closest_st = -1;
                    for(int i = 0; i < max_station; i++) {
                        if(sp_table[start_point_int][i] < closest_dist && !visit[i]) {
                            closest_st = i;
                            closest_dist = sp_table[start_point_int][i];
                        }
                    }  
                    //一定來不及
                    if(closest_st == -1 || closest_dist + distance >= acc_end_time_int) {
                        //reject request
                        inserted_user = new UserNode2(user_id_str, 0, 0, 0, 0, 0);
                        ID_UserTree.insert_user_us_id(inserted_user);
                        break;
                    }
                    visit[closest_st] = 1; //mark as visited
                    StationNode2* closest_station = StationTree.search_station(closest_st);

                    //check if there is accepted bike in user_start_station
                    LinkedListIterator2<int> list_iterator2(all_acc_bike);
                    iter_data = list_iterator2.next();

                    while(iter_data != NULL) {
                        BikeInorderIterator2 bike_iterator(closest_station->bike_bst_root);
                        BikeNode2* iter_bike = bike_iterator.next();
                        while(iter_bike != NULL) {
                            // cout << iter_bike->bike_type << " " << iter_bike->bike_id << " ";
                            if(iter_bike->bike_type_int == iter_data->data && iter_bike->rental_count < rent_cnt_lim2) {
                                curr_bike = iter_bike;
                                
                                //user arrive first, then the bike transfer
                                if(acc_start_time_int < curr_bike->bike_end_time + closest_dist) {
                                    // curr_bike = NULL; //in basic user dont wait for bikes
                                    if(curr_bike->bike_end_time + distance + closest_dist >= acc_end_time_int) {
                                        curr_bike = NULL;
                                    }
                                    else {
                                        ListNode2<BikeNode2*>* inserted_node = new ListNode2<BikeNode2*>(curr_bike);
                                        all_avail_bike.insert_node(inserted_node);
                                        avail_bike_num++;
                                    }
                                }
                                //bike transfer arrive first
                                else {
                                    //arrive at or after acc_end_time
                                    if(acc_start_time_int + distance + closest_dist >= acc_end_time_int) {
                                        curr_bike = NULL;
                                    }
                                    //arrive before acc_end_time
                                    else if(acc_start_time_int + distance + closest_dist < acc_end_time_int){
                                        // std::cout << "Filtered: " << curr_bike->bike_type << " " << curr_bike->bike_id << " " << curr_bike->bike_end_time << " ";
                                        // add to all_avail_bike array
                                        ListNode2<BikeNode2*>* inserted_node = new ListNode2<BikeNode2*>(curr_bike);
                                        all_avail_bike.insert_node(inserted_node);
                                        avail_bike_num++;
                                    }
                                }
                            }

                            iter_bike = bike_iterator.next();
                        }
                        
                        iter_data = list_iterator.next();
                    }



                    //if 1 or more bike is available
                    if(avail_bike_num > 0) {
                        //select user_bike with the highest rental price in all_avail_bike array
                        ListNode2<BikeNode2*>* curr = all_avail_bike.get_head();
                        user_bike = curr->data;
                        float highest_rental_price = user_bike->rental_price;
                        int highest_bike_id = user_bike->bike_id;
                        while(curr != NULL) {
                            if(curr->data->rental_price > highest_rental_price) {
                                user_bike = curr->data;
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
                    

                    if(user_bike == NULL) {
                        //continue with the loop
                    }
                    else { //suitable user_bike exist
                        UserNode2* inserted_driver;
                        int rent_start_time;
                        //user arrive first, then the bike transfer
                        if(acc_start_time_int < user_bike->bike_end_time + closest_dist) {
                            rent_start_time = user_bike->bike_end_time + closest_dist;

                        }
                        //bike transfer arrive first
                        else {
                            rent_start_time = acc_start_time_int;

                        }

                        //bike transfer
                        inserted_driver = new UserNode2("-1", 1, user_bike->bike_id, user_bike->bike_end_time,
                        user_bike->bike_end_time + closest_dist, 0);
                        inserted_driver->start_point_int = closest_st;
                        inserted_driver->end_point_int = start_point_int;
                        ID_UserTree.insert_user_us_id(inserted_driver);

                        //copy user_bike data
                        BikeNode2 *save1 = new BikeNode2(user_bike->bike_type, user_bike->bike_id, user_bike->rental_price, user_bike->rental_count);
                        save1->bike_type_int = user_bike->bike_type_int;
                        save1->bike_start_time = user_bike->bike_start_time;
                        save1->bike_end_time = user_bike->bike_end_time;

                        closest_station->remove_bike(user_bike->bike_id);

                        user_bike = save1; 

                        user_start_station->insert_bike(user_bike);



                        //rent bike
                        int user_revenue = floor(user_bike->rental_price * distance);//round down to integer
                        inserted_user = new UserNode2(user_id_str, 1, user_bike->bike_id, rent_start_time, 
                        rent_start_time + distance, user_revenue);
                        inserted_user->start_point_int = start_point_int;
                        inserted_user->end_point_int = end_point_int;
                        ID_UserTree.insert_user_us_id(inserted_user);
                        

                        //update everything

                        //update revenue
                        TOTAL_REVENUE += user_revenue;
                        
                        //update user_bike

                        user_bike->bike_end_time = rent_start_time + distance;
                        //rental count
                        user_bike->rental_count++;
                        //rental price
                        user_bike->rental_price = round((bike_initial_price2[user_bike->bike_type_int] - disc_prc2 * user_bike->rental_count) * 10) / 10; //round to 1 decimal place


                        //copy user_bike data
                        BikeNode2 *save = new BikeNode2(user_bike->bike_type, user_bike->bike_id, user_bike->rental_price, user_bike->rental_count);
                        save->bike_type_int = user_bike->bike_type_int;
                        save->bike_start_time = user_bike->bike_start_time;
                        save->bike_end_time = user_bike->bike_end_time;

                        user_start_station->remove_bike(user_bike->bike_id);

                        user_bike = save; 

                        user_end_station->insert_bike(user_bike);



                        break;
                    }
     
                }
  
            }   
            //suitable bike is found
            else {
                int rent_start_time;
                //user arrive first
                if(acc_start_time_int < user_bike->bike_end_time) {
                    rent_start_time = user_bike->bike_end_time;

                }
                //bike arrive first
                else {
                    rent_start_time = acc_start_time_int;
   
                }

                //rent bike
                int user_revenue = floor(user_bike->rental_price * distance);//round down to integer
                inserted_user = new UserNode2(user_id_str, 1, user_bike->bike_id, rent_start_time, 
                rent_start_time + distance, user_revenue);
                inserted_user->start_point_int = start_point_int;
                inserted_user->end_point_int = end_point_int;
                ID_UserTree.insert_user_us_id(inserted_user);
                

                //update everything

                //update revenue
                TOTAL_REVENUE += user_revenue;
                
                //update user_bike

                user_bike->bike_end_time = rent_start_time + distance;
                //rental count
                user_bike->rental_count++;
                //rental price
                user_bike->rental_price = round((bike_initial_price2[user_bike->bike_type_int] - disc_prc2 * user_bike->rental_count) * 10) / 10; //round to 1 decimal place


                //copy user_bike data
                BikeNode2 *save = new BikeNode2(user_bike->bike_type, user_bike->bike_id, user_bike->rental_price, user_bike->rental_count);
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
        myfile2.open ("./result/"+selectedCase+"/user_result.txt");

        UserInorderIterator2 user_iterator2(ID_UserTree.get_root());
        UserNode2* current_user2 = user_iterator2.next();
        while(current_user2) {
            // user_result
            if(current_user2->user_id_int != -1) {
                myfile2 << current_user2->user_id_str << " " << current_user2->decision << " " 
                << current_user2->bike_id << " " << current_user2->ride_start_time << " " <<
                current_user2->ride_end_time << " " << current_user2->revenue << endl;
            }

            current_user2 = user_iterator2.next();
        }
        std::cout << "USER_RESULT is done." << endl;
        myfile2.close();



        //transfer_log file
        ofstream myfile3;
        myfile3.open ("./result/"+selectedCase+"/transfer_log.txt");

        UserInorderIterator2 user_iterator3(ID_UserTree.get_root());
        UserNode2* current_user3 = user_iterator3.next();
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