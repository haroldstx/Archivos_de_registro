
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::string;
using std::vector;
using std::setw;
using std::setfill;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;

using namespace std;

struct Product {
    int id;
    string name;
    int category;
    float price;
    int aisle;
    int bin;
};

vector<Product> read_csv(string filename) {
    vector<Product> products;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        Product product;

        getline(ss, token, ',');
        product.id = stoi(token);

        getline(ss, product.name, ',');

        getline(ss, token, ',');
        product.category = stoi(token);

        getline(ss, token, ',');
        product.price = stof(token);

        getline(ss, token, ',');
        product.aisle = stoi(token);

        getline(ss, token, ',');
        product.bin = stoi(token);

        products.push_back(product);
    }

    file.close();
    return products;
}

void write_json(vector<Product> products, string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }

    file << "[";
    for (size_t i = 0; i < products.size(); i++) {
        file << "{";
        file << "\"id\":" << products[i].id << ",";
        file << "\"name\":\"" << products[i].name << "\",";
        file << "\"category\":" << products[i].category << ",";
        file << "\"price\":" << fixed << setprecision(2) << products[i].price << ",";
        file << "\"aisle\":" << products[i].aisle << ",";
        file << "\"bin\":" << products[i].bin;
        file << "}";
        if (i != products.size() - 1) {
            file << ",";
        }
    }
    file << "]";

    file.close();
}

void write_fixed(vector<Product> products, string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }

    for (size_t i = 0; i < products.size(); i++) {
        file << setw(5) << setfill('0') << products[i].id;
        file << setw(30) << setfill(' ') << left << products[i].name.substr(0, 30);
        file << setw(2) << setfill('0') << products[i].category;
        file << setw(7) << setfill(' ') << right << fixed << setprecision(2) << products[i].price;
        file << setw(3) << setfill('0') << products[i].aisle;
        file << setw(3) << setfill('0') << products[i].bin << endl;
    }
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <archivo_csv> <-json|-fixed>" << endl;
        exit(1);
    }

    string filename = argv[1];
    string flag = argv[2];

    vector<Product> products = read_csv(filename);

    if (flag == "-json") {
        write_json(products, "data.json");
        cout << "Archivo JSON generado exitosamente." << endl;
    }
    else if (flag == "-fixed") {
        write_fixed(products, "data.txt");
        cout << "Archivo de registros con campos de longitud fija generado exitosamente." << endl;
    }
    else {
        cout << "La bandera " << flag << " no es válida. Las banderas válidas son -json y -fixed." << endl;
        exit(1);
    }

    return 0;
}
    

