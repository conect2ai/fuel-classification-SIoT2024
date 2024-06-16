#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "classifier.h"
// #include "model.h"
// #include "eloquent_tensorflow32.h"

using namespace std;

// to compile: g++ -std=c++11 -o main main.cpp

// #define ARENA_SIZE 50
// #define NUM_OPS 1

// using Eloquent::Esp32::TensorFlow;
// TensorFlow<NUM_OPS, ARENA_SIZE> tf;

// PID_POLLING_INFO obdData[]= {
//   {PID_LONG_TERM_FUEL_TRIM_1, 1},
//   {PID_INTAKE_TEMP, 1},
//   {PID_BAROMETRIC, 1},
//   {PID_CATALYST_TEMP_B1S1, 1},
//   {PID_CONTROL_MODULE_VOLTAGE, 1},
//   {PID_ENGINE_LOAD, 1},
// };

Eloquent::ML::Port::RandomForestClassifier classifier;

float X[15] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float means_values[6] = {-3.992668, 37.716719, 14.538872, 623.953239, 14.081866, 40.563002};
float std_dev_values[6] = {4.397492, 5.985187, 0.065725, 34.173427, 0.183305, 16.813886};

int main() {

    bool skip = true;
    int count = 0;
    int outlier_detection = 0;
    std::string filename = "ValidDataset.csv"; // Nome do seu arquivo CSV
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::vector<std::vector<double>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<double> values;

        while (std::getline(iss, token, ',')) {
            // if (!skip){
            //     try {
            //         double value = std::stod(token);
            //         values.push_back(value);
            //     } catch (const std::exception& e) {
            //         std::cerr << "Erro ao converter valor: " << token << std::endl;
            //     }
            // }
            // skip = false;
            try {
                double value = std::stod(token);
                values.push_back(value);
            } catch (const std::exception& e) {
                std::cerr << "Erro ao converter valor: " << token << std::endl;
            }
        }
        
        if (!values.empty()) {
            data.push_back(values);
        }
    }

    file.close();

    // print len of data
    std::cout << "Data size: " << data.size() << std::endl;

    
    // iterate over the data
    for (auto& values : data) {

        X[0] = values[0];
        X[1] = values[1];
        X[2] = values[2];
        X[3] = values[3];
        X[4] = values[4];
        X[5] = values[5];
        X[6] = values[6];
        X[7] = values[7];
        X[8] = values[8];
        X[9] = values[9];
        X[10] = values[10];
        X[11] = values[11];
        X[12] = values[12];
        X[13] = values[13];
        X[14] = values[14]; 
        

        //Normalize the data
        //for (int i = 0; i < 5; i++) {
        //    X[i] = (X[i] - means_values[i]) / std_dev_values[i];
        //}

        // Predict the class
        int prediction = classifier.predict(X);

        // create a new file with the prediction
        std::ofstream output_file;
        output_file.open("output_test.csv", std::ios_base::app);
        output_file << prediction << std::endl;
        output_file.close();
        
    }

    return 0;
}
