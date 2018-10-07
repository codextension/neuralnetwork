//
// Created by elie on 07.03.18.
//

#ifndef NEURALNETWORK_UTILITIES_H
#define NEURALNETWORK_UTILITIES_H

#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

namespace cx {

    enum value_type {
        INPUT,
        OUTPUT
    };

    enum method_type {
        SGD,
        BATCH,
        MINI_BATCH
    };

    double sigmoid(const double &value) {
        return 1.0f / (1 + exp(-value));
    }

    double derivativeSigmoid(const double &value) {
        double sigmoid = cx::sigmoid(value);
        return sigmoid * (1.0 - sigmoid);
    }

    vector<map<value_type, vector<int>>> readFile(const string &file_path) {
        ifstream input_file(file_path);
        vector<map<value_type, vector<int>>> output;
        for (string line; getline(input_file, line);) {
            istringstream ss(line);
            map<value_type, vector<int>> results;
            int x = 1;
            while (ss.good()) {
                string s;
                getline(ss, s, ';');
                vector<int> input;
                unsigned long n = s.length();
                char char_array[n];
                strcpy(char_array, s.c_str());
                for (int i = 0; i < n; i++)
                    input.push_back(char_array[i] - '0');

                if (x == 1) {
                    results.insert(pair<value_type, vector<int>>(OUTPUT, input));
                    x++;
                } else {
                    results.insert(pair<value_type, vector<int>>(INPUT, input));
                    x--;
                }
            }
            output.push_back(results);
        }
        return output;
    };

    map<string, string> read_startup_attributes(const string &properties_file) {
        ifstream input_file(properties_file);
        map<string, string> output;
        for (string line; getline(input_file, line);) {
            vector<std::string> strs;
            boost::split(strs, line, boost::is_any_of("="));
            output.insert(pair<string, string>(strs[0], strs[1]));
        }

        return output;
    }

    class data_holder {
    public:
        void add_input(vector<int> &inputs);

        map<string, double> weights;
        map<string, int> values;
        vector<int> expected_outputs;
        vector<int> prev_outputs;
    };

    void data_holder::add_input(vector<int> &inputs) {
        for (int i = 1; i <= inputs.size(); i++) {
            int input = inputs.at(static_cast<unsigned long>(i - 1));
            string node_name = "N1." + to_string(i);
            this->values.insert(pair<string, int>(node_name, input));
        }
    }
}
#endif //NEURALNETWORK_UTILITIES_H
