//#include <QCoreApplication>

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();
//}
//###########################################################################
#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <vector>
//  std::vector<unsigned long long> list_of_synapses
// Function to write a vector to a file
void writeVectorToFile(const std::vector<int>& vec, const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << "Could not open file for writing:" << filename;
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0); // Use Qt 5.0 or other version depending on your Qt version
    out << static_cast<qint32>(vec.size());
    for (int value : vec) {
        out << value;
    }

    file.close();
}

// Function to read a vector from a file
std::vector<int> readVectorFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Could not open file for reading:" << filename;
        return {};
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0); // Use Qt 5.0 or other version depending on your Qt version
    qint32 size;
    in >> size;

    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        in >> vec[i];
    }

    file.close();
    return vec;
}

// Function to compare two vectors
bool compareVectors(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    return vec1 == vec2;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Example vector
    std::vector<int> originalVector = {1, 2, 3, 4, 5};
    QString filename = "/home/viktor/my_projects_qt_2/zapisy_chtenie_vectora_v_file/vector.dat";

    // Write vector to file
    writeVectorToFile(originalVector, filename);

    // Read vector from file
    std::vector<int> readVector = readVectorFromFile(filename);

    // Verify correctness
    if (compareVectors(originalVector, readVector)) {
        qDebug() << "The vector was written and read correctly.";
    } else {
        qDebug() << "The vector was NOT written and read correctly.";
    }

    return a.exec();
}
