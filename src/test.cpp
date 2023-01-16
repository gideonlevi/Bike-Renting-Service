// #include <iostream>
// #include <fstream>

// using namespace std;

// int main() {
//     cout << "anjay" << endl;
//     ifstream FILE_map("../testcases/case1/map.txt");
//     if(!FILE_map.is_open()) {
//         cerr << "map.txt not found" << endl;
//         exit(0);
//     }
//     string src_station;
//     string dest_station;
//     string distance_str;
//     while(FILE_map.good()){
//         //read line
//         FILE_map >> src_station >> dest_station >> distance_str;
//         cout << src_station << " " << dest_station << " " << distance_str << endl;
//         string temp1;
//         for(int i = 1; i < src_station.length(); i++) {
//             temp1[i-1] = src_station[i];
//         }
//         int src_station_num = stoi(temp1);

//         string temp2;
//         for(int i = 1; i < dest_station.length(); i++) {
//             temp2[i-1] = dest_station[i];
//         }
//         int dest_station_num = stoi(temp2);

//         int distance_int = stoi(distance_str);
//         cout << src_station_num << " " << dest_station_num << " " << distance_int << endl;
//     }


//     // BIKE
//     std::cout << "BIKE SEKARANG" << endl;
//     ifstream FILE_bike("../testcases/case1/bike.txt");
//     if (!FILE_bike.is_open())
//     {
//         cerr << "bike.txt not found." << endl;
//         exit(0);
//     }

//     string bike_type;
//     string bike_id_str;
//     string station_id_str;
//     string rental_price_str;
//     string rental_count_str;
//     string last_bike_id_str;
//     int count = 0;
//     while (FILE_bike.good())
//     {   
//         count++;
//         // read line

//         FILE_bike >> bike_type >> bike_id_str >> station_id_str >> rental_price_str >> rental_count_str;
        
//         if(bike_id_str == last_bike_id_str) {
//             break;
//         }

//         // convert to int
//          string temp1;
//          for(int i = 1; i < bike_type.length(); i++) {
//              temp1[i-1] = bike_type[i];
//          }
//          int bike_type_num = stoi(temp1);

//         int bike_id_int = stoi(bike_id_str);

//         // int station_id_int = stoi(station_id_str);

//         string temp2;
//         for (int i = 1; i < station_id_str.length(); i++)
//         {
//             temp2[i - 1] = station_id_str[i];
//         }
//         int station_id_int = stoi(temp2);

//         float rental_price_flt = stof(rental_price_str);

//         int rental_count_int = stoi(rental_count_str);

//         std::cout << bike_type_num << " " << bike_id_int << " " << station_id_int << " " << rental_price_flt << " " << rental_count_int << endl;

//         last_bike_id_str = bike_id_str;
//     }
//     std::cout << "BIKE is done." << count << endl;

//     return 0;
// }